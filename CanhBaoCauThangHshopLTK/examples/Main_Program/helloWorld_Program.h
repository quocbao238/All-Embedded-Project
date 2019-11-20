#ifndef _HELLO_WORLD_PROGRAM_H_H_
#define _HELLO_WORLD_PROGRAM_H_H_
#include "Program_Adaptor.h"

class HelloWorld_Class: public Program_Adaptor_Class{
  public:
  HelloWorld_Class(){};
  void setup();
  void loop();
};

extern HelloWorld_Class HelloWorld_Program;

#endif
