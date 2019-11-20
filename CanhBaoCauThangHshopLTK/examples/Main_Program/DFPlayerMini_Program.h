#ifndef _DFPLAYER_MINI_PROGRAM_H_H_
#define _DFPLAYER_MINI_PROGRAM_H_H_
#include "Program_Adaptor.h"

#include <SoftwareSerial.h>
#include "DFPlayer_Mini_Mp3.h"

class Dfplayer_Class: public Program_Adaptor_Class{
  public:
  Dfplayer_Class(){};
  virtual ~Dfplayer_Class(){};
  void setup();
  void loop();
};

extern SoftwareSerial mySerial;
extern Dfplayer_Class Dfplayer_Program;

extern void mp3_set_serial (SoftwareSerial*);
extern void mp3_set_volume (uint16_t);
extern void mp3_play(uint16_t);

#endif
