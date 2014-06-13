/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module encapsulates the control of the lcd attached to the LXRobotics Display Shield
 * @file lcd.cpp
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

/* INCLUDE SECTION */

#include "lcd.h"
#include <LiquidCrystal.h>

/* DEFINE SECTION */

/* LCD BACKLIGHT */
// LCD_LED = PC3 = A3
#define LCD_LED_DDR     DDRC
#define LCD_LED_PORT    PORTC
#define LCD_LED         (1<<3)

/* CONSTANT SECTION */

/* LCD PROPERTIES */
// RS = PB2 = 10
static int const rs = 10;
// RW = PB1 = 9
static int const rw = 9;
// enable = PB0 = 8
static int const enable = 8;
// d0 = PD7 = 7
static int const d0 = 7;
static int const d1 = 6;
static int const d2 = 5;
static int const d3 = 4;
static int const d4 = 3;
static int const d5 = 2;
static int const d6 = 1;
// d7 = PD0 = 0
static int const d7 = 0;
// number of rows and cols of the lcd display
static int const LCD_COLS = 20;
static int const LCD_ROWS = 4;

/* GLOBAL VARIABLE SECTION */

LiquidCrystal my_lcd(rs,rw,enable,d0,d1,d2,d3,d4,d5,d6,d7);
static char display_content[LCD_ROWS][LCD_COLS];

/* CODE SECTION */

/**
 * @brief initializes the module
 */
void lcd::begin() {
  my_lcd.begin(LCD_COLS, LCD_ROWS);
  for(int r=0; r<LCD_ROWS; r++)
    for(int c=0; c<LCD_COLS; c++) display_content[r][c] = ' ';
  lcd::update();
  
  // set backlight to output and turn it off  
  LCD_LED_DDR |= LCD_LED;
  lcd::set_backlight(BACKLIGHT_OFF);
}

/**
 * @brief writes the content of line_content into the display buffer for row 'row'
 */
void lcd::print(unsigned int const row, char *line_content) {
  if(row > (LCD_ROWS-1)) return;
  int const length = strlen(line_content);
  for(int c=0; c<LCD_COLS; c++) {
    if(c < length)
      display_content[row][c] = line_content[c];
    else
      display_content[row][c] = ' ';
  }
}

/**
 * @brief writes any changes done by the write function onto the display
 */
void lcd::update() {
  for(int r=0; r<LCD_ROWS; r++) {
    my_lcd.setCursor(0,r);
    for(int c=0; c<LCD_COLS; c++) my_lcd.write(display_content[r][c]);
  }
}

/**
 * @brief control the lcd backlight
 */
void lcd::set_backlight(E_BACKLIGHT_STATUS const stat) {
  switch(stat) {
   case BACKLIGHT_ON: LCD_LED_PORT &= ~LCD_LED; break;
   case BACKLIGHT_OFF: LCD_LED_PORT |= LCD_LED; break;
   case BACKLIGHT_TOOGLE: LCD_LED_PORT ^= LCD_LED; break;
   default: break; 
  }
}


