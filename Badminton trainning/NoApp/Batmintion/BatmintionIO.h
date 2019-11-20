#ifndef _BATMINTION_IO_H
#define _BATMINTION_IO_H

#include "Vietduino_I2CLCD.h"
#include "Wire.h"
#include "Vietduino_NewFunction.h"
#include "OneButton.h"

/*
   define Pin
*/
#define BUZZER        (1) //TX0
#define BUTTON_ONE      (2) //D4
#define BUTTON_TWO      (0) //D3
#define TIME_BUTTONDELAY  (50) // Time buzzer ON when click button

/*
   Time Set
   Easy   --> 1:30
   Normal --> 1:45
   Hard   --> 2:00
*/

#define StrTimeEasy     "1:15"
#define StrTimeNormal   "1:30"
#define StrTimeHard     "1:45"
#define timeEasy         (75)   // 20 lan --> 3s    on  0.75s off
#define timeNormal       (90)   // 25 lan --> 2,85s on  0.75s off
#define timeHard         (105)  // 30 lan --> 2,75s on  0.75s off

/*
   Time Difficult
   Easy   --> 5s
   Normal --> 4s
   Hard   --> 3s
*/
#define StrLedEasy       "3.00"
#define StrLedNormal     "2.85"
#define StrLedHard       "2.75"
#define LedLevel1        (3000); // Levl 1    (3s)    --> 1s on Buzzer
#define LedLevel2        (2850); // Level 2   (2s85)  --> 1s on Buzzer
#define LedLevel3        (2750); // Level 3   (2s75)  --> 1s on Buzzer
#define timesoff         (750);
#define timebuzzeron     (200);

/*
   define Value
*/
extern uint16_t times_off, times_buzzeron;
extern uint8_t times_counter;
extern uint16_t times_hard;

extern uint8_t statusSet, statusHard;
extern uint8_t level, trainning;
extern uint8_t clearLCD;
extern uint8_t timesStart;
extern byte ledPin[];
extern uint8_t pinCount;
extern uint8_t statusButton;
extern uint8_t statusButtonfinish;
/*
   define class
*/

extern OneButton btnOne;
extern OneButton btnTwo;
extern Vietduino_I2CLCD lcd;


#endif
