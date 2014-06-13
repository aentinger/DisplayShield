/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief Arduino Library for interfacing the LXRobotics Display Shield
 * @file LXR_Display_Shield.cpp
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include "LXR_Display_Shield.h"
#include <Wire.h>

static int const I2C_SLAVE_ADDRESS = 40;

/**
 * @brief initializes the module
 */
void LXR_Display_Shield::begin() {
  Wire.begin(); 
  delay(250); // give the shield some time to startup
}

/**
 * @brief writes the content of 'content' to the row 'row' (0 <= row <= 3)
 */
void LXR_Display_Shield::print(byte const row, char *content) {
  if(row > 3) return;
  
  Wire.beginTransmission(I2C_SLAVE_ADDRESS);
  Wire.write(row + 1);
  Wire.write(content);
  Wire.write(0x00);
  Wire.endTransmission(); 
}

/**
 * @brief turns the lcd backlight on and off
 */
void LXR_Display_Shield::turn_backlight(E_BACKLIGHT const stat) {
  Wire.beginTransmission(I2C_SLAVE_ADDRESS);
  Wire.write(0x00);
  Wire.write((byte)(stat));
  Wire.endTransmission(); 
}

/**
 * @brief returns the joystick data
 */
LXR_Display_Shield::s_data LXR_Display_Shield::get_data() {
  Wire.requestFrom(I2C_SLAVE_ADDRESS, 4);
  delay(20);
  byte buf[4];
  for(int b=0; b<4; b++) {
    while(Wire.available() == 0) { }
    buf[b] = Wire.read();
  }
  LXR_Display_Shield::s_data data;
  data.x = buf[1];
  data.y = buf[2];
  if(buf[3] == 0x01) data.button_was_pressed = true;
  else data.button_was_pressed = false;
  return data;
}

/**
 * @brief retrieve hard and software version of the shield
 */
void LXR_Display_Shield::get_version(byte *hw, byte *sw) {
  Wire.requestFrom(I2C_SLAVE_ADDRESS, 4);
  delay(20);
  byte buf[4];
  for(int b=0; b<4; b++) {
    while(Wire.available() == 0) { }
    buf[b] = Wire.read();
  }
  *hw = (buf[0] >> 4);
  *sw = buf[0] & 0x0F;
}
