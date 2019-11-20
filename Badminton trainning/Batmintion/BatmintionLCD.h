#ifndef _BATMINTION_LCD_H
#define _BATMINTION_LCD_H

#include "Arduino.h"


extern void b_begin();
extern void setLevel();
extern void setHard();
//extern void setTrainning();


extern uint8_t statusSet;
extern uint8_t statusHard;
extern uint8_t clearLCD;

#endif
