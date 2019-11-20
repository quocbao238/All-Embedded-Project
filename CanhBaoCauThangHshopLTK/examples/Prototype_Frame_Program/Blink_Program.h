#ifndef _BLINK_PROGRAM_H_H_
#define _BLINK_PROGRAM_H_H_
#include "Program_Adaptor.h"

class Blink_Class: public Program_Adaptor_Class{
  public:
    Blink_Class(){};
    void setup();
    void loop();
};

extern Blink_Class Blink_Program;

#endif
