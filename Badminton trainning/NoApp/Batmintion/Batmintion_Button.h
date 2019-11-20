#ifndef _BATMINTION_BUTTON_H
#define _BATMINTION_BUTTON_H

#include "Arduino.h"


extern void btnClickLevelSet();
extern void btnClickLevelHard();
extern void btnClick_Trainning();
extern void btn_DobleClickBackSet();
extern void btn_DobleClickBackHard();
extern void btnTwo_DobleClickStart();
extern void btn_ClickOut();
extern void btn_OutRun();

extern uint8_t trainning;
extern uint8_t statusSet;
extern uint8_t statusHard;
extern uint8_t clearLCD;


#endif
