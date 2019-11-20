#ifndef _PROGRAME_MANAGER_H_H_
#define _PROGRAME_MANAGER_H_H_
#include "Program_Adaptor.h"

enum
{
  BLINK_PROGRAM_ID = 0,
  SENSOR_PROGRAM_ID,
  HELLO_PROGRAM_ID,
  DFPLAYER_PROGRAM_ID,
  CHECKVOLTAGE_PROGRAM_ID,
      LAST_PROGRAM_ID
};

extern Program_Adaptor_Class * p_ListProgram[LAST_PROGRAM_ID];

extern void programManager_setup();
extern void programManager_loop();
#endif
