/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module encapsulates the control of the joystick attached to the LXRobotics Display Shield
 * @file joystick.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "Arduino.h"

class joystick {
public:
  /**
   * @brief initializes the module
   */
   static void begin();
   
   /**
    * @brief reads the latest values and stores them in the module
    */
   static void update();  
   
   typedef struct {
     byte x;
     byte y;
     boolean button_was_pressed;
   } s_data;
   
   /**
    * @brief returns the data and sets button_was_pressed back to false
    */
   static s_data get_data();
};

#endif
