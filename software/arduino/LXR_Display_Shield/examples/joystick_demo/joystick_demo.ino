/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this sketch demonstrates how to write to the LCD of the LXRobotics Display Shield using the LXR_Display_Shield Library
 * @file lcd_print.ino
 */

#include "LXR_Display_Shield.h"
#include <Wire.h> /// dont forget this

void setup() {
  // init the library
  LXR_Display_Shield::begin();
  // turn backlight on  
  LXR_Display_Shield::turn_backlight(ON);
}

void loop() {
  LXR_Display_Shield::s_data const joystick_data = LXR_Display_Shield::get_data();
  
  char buf[21];  

  sprintf(buf, "Joystick Values:");
  LXR_Display_Shield::print(0,buf);
  
  sprintf(buf, "X: %d", joystick_data.x);
  LXR_Display_Shield::print(1,buf);
  
  sprintf(buf, "Y: %d", joystick_data.y);
  LXR_Display_Shield::print(2,buf);
  
  if(joystick_data.button_was_pressed) LXR_Display_Shield::print(3,"Button pressed!");
  else LXR_Display_Shield::print(3,"Button not pressed!");
  
  delay(100);
}
