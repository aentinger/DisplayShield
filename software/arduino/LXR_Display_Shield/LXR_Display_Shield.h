/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief Arduino Library for interfacing the LXRobotics Display Shield
 * @file LXR_Display_Shield.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef LXR_DISPLAY_SHIELD_H_
#define LXR_DISPLAY_SHIELD_H_

#include "Arduino.h"

typedef enum {
  OFF = 0, ON = 1} 
E_BACKLIGHT;

class LXR_Display_Shield {
public:
  /**
   * @brief initializes the module
   */
  static void begin();

  /**
   * @brief writes the content of 'content' to the row 'row' (0 <= row <= 3)
   */
  static void print(byte const row, char *content);

  /**
   * @brief turns the lcd backlight on and off
   */
  static void turn_backlight(E_BACKLIGHT const stat);

  typedef struct {
    byte x;
    byte y;
    boolean button_was_pressed;
  } 
  s_data;

  /**
   * @brief returns the joystick data
   */
  static s_data get_data();
  
  /**
   * @brief retrieve hard and software version of the shield
   */
  static void get_version(byte *hw, byte *sw);
};

#endif

