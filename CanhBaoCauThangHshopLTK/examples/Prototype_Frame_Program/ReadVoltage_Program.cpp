#include "ReadVoltage_Program.h"
#include "Program_Gpio.h"
#include "Sensor_Program.h"

enum{
  STATE_READ = 0,
  STATE_WAIT,
  STATE_IDE
};


int readings[numReadings];   // the readings from the analog input
unsigned char readIndex = 0; // the index of the current reading
unsigned char tem_readIdex = 0;
int total = 0;     // the running total
float average = 0; // the average
float last_Volt = 0;
unsigned long timer_VoltRaw_max = 100;
unsigned long timer_VoltRaw = 0;
int statusVoice = runVoice;

void ReadVoltage_Class::setup()
{
  Serial.begin(115200);
  pinMode(inputPin, INPUT);
}

void ReadVoltage_Class::loop()
{
  if (ui_stateProgram == STATE_READ)
  {
    // Serial.println("Voltage: ");
    //  + String(voltage));
    checkVoltage();
    ul_timeRepeat = 3000;
    ui_stateProgram = STATE_WAIT;
  }
  else if (ui_stateProgram == STATE_WAIT)
  {
    if (last_Volt <= 7.6 ){
      statusVoice = runBat; 
    }else if(last_Volt >7.6){
      statusVoice = runVoice;
    }
    ul_timeRepeat = 0;
    ui_stateProgram = STATE_READ;
  }else;
  
}

void ReadVoltage_Class::checkVoltage()
{
  if (millis() - timer_VoltRaw >= timer_VoltRaw_max)
  {
    float val = 0;
    timer_VoltRaw = millis();
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = analogRead(inputPin);
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
    tem_readIdex++;
    // if we're at the end of the array...
    if (readIndex >= numReadings)
    {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
    if (tem_readIdex >= numReadings)
    {
      tem_readIdex = numReadings;
    }
    average = total / tem_readIdex;
    last_Volt = average / 1023 * 18.56;
    // Serial.println(last_Volt);
  } 
}

    ReadVoltage_Class ReadVoltage_Program;
