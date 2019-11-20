#ifndef _PROGRAME_MANAGER_H_H_
#define _PROGRAME_MANAGER_H_H_
#include "Program_Adaptor.h"

enum{
  HELLOWORLD_PROGRAM_ID = 0, // THE FIRST MUST BE 0!
  DFPLAYER_MINI_PROGRAM_ID,
  LAST_PROGRAM_ID
};

extern Program_Adaptor_Class * p_ListProgram[LAST_PROGRAM_ID];

extern void programManager_setup();
extern void programManager_loop();
#endif
