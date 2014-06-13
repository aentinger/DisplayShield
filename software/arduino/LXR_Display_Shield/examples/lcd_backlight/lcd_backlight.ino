/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this sketch demonstrates how to control the backlight of the LCD of the LXRobotics Display Shield using the LXR_Display_Shield Library
 * @file lcd_backlight.ino
 */

#include "LXR_Display_Shield.h"
#include <Wire.h> /// dont forget this

void setup() {
  // init the library
  LXR_Display_Shield::begin();
}

void loop() {
  LXR_Display_Shield::turn_backlight(ON);
  delay(500);  
  LXR_Display_Shield::turn_backlight(OFF);
  delay(500);
}
