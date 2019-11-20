#ifndef _DFPLAYER_PROGRAM_H_H_
#define _DFPLAYER_PROGRAM_H_H_
#include "Program_Adaptor.h"
#include "SoftwareSerial.h"
#include "DFPlayer_Mini_Mp3.h"
#include "Sensor_Program.h"

class DFPlayer_Class: public Program_Adaptor_Class{
  public:
    bool flag_volume;
    DFPlayer_Class(){};
    void getValue();
    void setup();
    void loop();
};

extern DFPlayer_Class DFPlayer_Program;
#endif
