/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module encapsulates the control of the lcd attached to the LXRobotics Display Shield
 * @file lcd.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
#ifndef LCD_H_
#define LCD_H_

#include "Arduino.h"

class lcd {
public:
  /**
   * @brief initializes the module
   */
  static void begin();
  
  /**
   * @brief writes the content of line_content into the display buffer for row 'row'
   */
  static void print(unsigned int const row, char *line_content);
  
  /**
   * @brief writes any changes done by the write function onto the display
   */
  static void update();
  
  typedef enum {BACKLIGHT_ON = 0, BACKLIGHT_OFF = 1, BACKLIGHT_TOOGLE = 2} E_BACKLIGHT_STATUS;
  /**
   * @brief control the lcd backlight
   */
  static void set_backlight(E_BACKLIGHT_STATUS const stat);
};

#endif
