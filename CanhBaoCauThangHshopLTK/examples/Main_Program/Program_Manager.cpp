#include "Program_Manager.h"
#include "helloWorld_Program.h"
#include "DFPlayerMini_Program.h"

Program_Adaptor_Class * p_ListProgram[LAST_PROGRAM_ID] = {
                                                            &HelloWorld_Program,
                                                            &Dfplayer_Program
                                                         };

void programManager_setup(){
  for(int cf = 0; cf < LAST_PROGRAM_ID; cf++){
      p_ListProgram[cf]->setup();
  }
}

void programManager_loop(){
  ul_currentMililis = millis();
  for(int cf = 0; cf < LAST_PROGRAM_ID; cf++){
    if(ul_currentMililis - p_ListProgram[cf]->ul_lastMillis >= p_ListProgram[cf]->ul_timeRepeat){
      p_ListProgram[cf]->ul_lastMillis = ul_currentMililis;
      p_ListProgram[cf]->loop();
    }
  }
}

