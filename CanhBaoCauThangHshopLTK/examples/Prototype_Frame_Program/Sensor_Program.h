#ifndef _SENSOR_PROGRAM_H_H_
#define _SENSOR_PROGRAM_H_H_
#include "Program_Adaptor.h"
enum
{
  _IN_STATE_ = 0b00000010,
  _OUT_STATE_ = 0b00000001,
  _MID_STATE_ = 0b00000000,
  _IDLE_STATE_ = 0b00000011
};

class Sensor_Class: public Program_Adaptor_Class{
  public:
    Sensor_Class(){};
    void setup();
    void loop();
    void readPinState();
    void stateProcess();
};

extern Sensor_Class Sensor_Program;
extern byte byte_pinState;
extern byte byte_lastPinState;
extern int voice;
extern int lastvoice;

#endif
