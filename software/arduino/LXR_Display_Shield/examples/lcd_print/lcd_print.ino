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
  // write to the display
  LXR_Display_Shield::print(0,"LXRobotics");
  LXR_Display_Shield::print(1,"Empowering people!");
  LXR_Display_Shield::print(2,"Display Shield v1");
  char buf[21];
  byte vhw = 0, vsw = 0;
  LXR_Display_Shield::get_version(&vhw, &vsw);
  sprintf(buf, "HW: V %d, SW: V %d", vhw, vsw);
  LXR_Display_Shield::print(3,buf);
}

void loop() {

}
