#ifndef _D80NK_PROGRAM_H_H_
#define _D80NK_PROGRAM_H_H_
#include "Program_Adaptor.h"
#include "OneButton.h"

class D80NK_Class: public Program_Adaptor_Class{
  public:
    D80NK_Class(){};
    void setup();
    void loop();
    void checkStatus();
    void getValue();
    
};

extern D80NK_Class D80NK_Program;
extern int couterUp;
extern int couterDown;
extern int statesUp;
extern int statesDown;
extern int lastcouterUp;
extern int lastcouterDown;
extern int voice;

extern OneButton SensorUp;
extern OneButton SensorDown;

extern void SensorUp_Up();
extern void SensorUp_Down();
extern void SensorDown_Up();
extern void SensorDown_Down();

#endif
