/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this sketch implements the firmware stored on the ATMEGA328P microprocessor of the LXRobotics Displayshield and allows an I2C Control of the 4 line lcd screen
 * @file displayshield_v1_firmware.ino
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

/* INCLUDE SECTION */
#include <LiquidCrystal.h>
#include <Wire.h>

#include "lcd.h"
#include "joystick.h"

/* I2C SLAVE PROPERTIES */
static int const I2C_SLAVE_ADDRESS = 40;
/* VERSION PROPERTIES */
static byte const HW_VERSION = 1;
static byte const SW_VERSION = 1;

/* FUNCTION SECTION */

void setup() {
  // init lcd
  lcd::begin();
  // init joystick
  joystick::begin();  
  // init i2c library
  Wire.onReceive(i2c_data_received_callback);
  Wire.onRequest(i2c_data_request_callback);
  Wire.begin(I2C_SLAVE_ADDRESS);
}

void loop() {
  // update display
  lcd::update();
  // update the joystick data
  joystick::update();
}

/* I2C INTERFACE */
// I2C Register Description
// READ
// REG 0 R -> HW Version (Upper 4 Bit), Software Version (Lower 4 Bit)
// REG 1 R -> Joystick Horizontal
// REG 2 R -> Joystick Vertical
// REG 3 R -> Bit 0 = 1 => Button pressed since last readout
//       R -> Bit 1 = 0 => Button not pressed since last readout
// WRITE
// REG 0 W -> Bit 0 = 1 => Backlight activated
//       W -> Bit 0 = 0 => Backlight deactivated
// REG 1 W -> LCD LINE 1
// REG 2 W -> LCD LINE 2
// REG 3 W -> LCD LINE 3
// REG 4 W -> LCD LINE 4

void i2c_data_received_callback(int number_of_bytes) {

  // parse the data
  for(int i=0; i<number_of_bytes; i++) {
    parse_i2c(Wire.read()); 
  }
}

void parse_i2c(char const data) {

  typedef enum {
    E_REG_ADDR, E_DATA, E_ERROR  } 
  E_PARSE_STATE;
  static E_PARSE_STATE state = E_REG_ADDR;
  static byte reg_addr = 0xFF;
  static char row_buf[21];
  static byte row_buf_cnt = 0;

  switch(state) {
  case E_REG_ADDR: 
    {
      reg_addr = data;
      state = E_DATA;
    } 
    break;
  case E_DATA: 
    {
      switch(reg_addr) {
      case 0x00: 
        {
          if(data == 0x01) lcd::set_backlight(lcd::BACKLIGHT_ON);
          else if(data == 0x00) lcd::set_backlight(lcd::BACKLIGHT_OFF);
          state = E_REG_ADDR;
        } 
        break;
      case 0x01: 
      case 0x02:
      case 0x03:
      case 0x04:
        {
          row_buf[row_buf_cnt] = data; 
          row_buf_cnt++;
          if(data == 0x00) {
            lcd::print(reg_addr-1, row_buf);
            row_buf_cnt = 0;
            state = E_REG_ADDR;
          }
        } break;
      default: 
        {
          state = E_ERROR;
        } 
        break;
      }
    } 
    break;
  case E_ERROR: 
    {
      for(;;) {
        lcd::set_backlight(lcd::BACKLIGHT_TOOGLE);
        delay(100);
      }
    } 
    break;
  default: 
    {
      state = E_ERROR;
    } 
    break;
  }
}

void i2c_data_request_callback() {
    byte tx_buf[4] = {0};
    joystick::s_data const joy_data = joystick::get_data();
    // version
    tx_buf[0] = (HW_VERSION<<4) + SW_VERSION;
    // joystick hor
    tx_buf[1] = joy_data.x;
    // joystick ver
    tx_buf[2] = joy_data.y;  
    // button state
    joy_data.button_was_pressed ? tx_buf[3] = 1 : tx_buf[3] = 0;
    // send answer
    Wire.write(tx_buf, 4);
}

