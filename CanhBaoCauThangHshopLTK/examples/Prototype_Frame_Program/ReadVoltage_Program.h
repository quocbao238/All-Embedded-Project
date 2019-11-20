#ifndef _READ_VOLTAGE_PROGRAM_H_H_
#define _READ_VOLTAGE_PROGRAM_H_H_
#include "Program_Adaptor.h"
#include "Sensor_Program.h"
#define numReadings 20

class ReadVoltage_Class: public Program_Adaptor_Class{
  public:
    ReadVoltage_Class(){};
    void setup();
    void loop();
    void checkVoltage();
};

extern ReadVoltage_Class ReadVoltage_Program;

extern int readings[numReadings]; // the readings from the analog input
extern unsigned char readIndex; // the index of the current reading
extern unsigned char tem_readIdex;
extern int total; // the running total
extern float average; // the average
extern float last_Volt;
extern unsigned long timer_VoltRaw_max;
extern unsigned long timer_VoltRaw;
extern int statusVoice;

#endif
