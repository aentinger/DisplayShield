/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module encapsulates the control of the joystick attached to the LXRobotics Display Shield
 * @file joystick.cpp
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

/* INCLUDE SECTION */

#include "joystick.h"

/* DEFINE SECTION */

// BUTTON = PC2
#define BUTTON_DDR     DDRC
#define BUTTON_PORT    PORTC
#define BUTTON_PIN     PINC
#define BUTTON         (1<<2)

/* CONSTANT SECTION */

static int const JOY_X_PIN = 1; // A1
static int const JOY_Y_PIN = 0; // A0

/* GLOBAL VARIABLE SECTION */
static joystick::s_data data = {0,0,false};

/* CODE SECTION */

/**
 * @brief initializes the module
 */
void joystick::begin() {
  DIDR0 &= ~(1<<ADC2D);
  BUTTON_DDR &= ~(1<<BUTTON); 
  BUTTON_PORT |= (1<<BUTTON);
}

/**
 * @brief reads the latest values and stores them in the module
 */
void joystick::update() {
  data.x = (byte)(analogRead(JOY_X_PIN) >> 2);
  data.y = (byte)(analogRead(JOY_Y_PIN) >> 2);
  if((BUTTON_PIN & BUTTON) == 0) {
    data.button_was_pressed = true;
  }    
}

/**
 * @brief returns the data and sets button_was_pressed back to false
 */
joystick::s_data joystick::get_data() {
  s_data const tmp = data;
  data.button_was_pressed = false;
  return tmp;
}
