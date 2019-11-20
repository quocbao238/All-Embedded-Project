#include "Sensor_Program.h"
#include "Program_Gpio.h"
#include "ReadVoltage_Program.h"

byte byte_pinState = 0;
byte byte_lastPinState = 0;

enum
{
  SENSOR_OFF = 0,
  SENSOR_READ,
  SENSOR_WAIT,
  SENSOR_VOICEBAT,
  STATE_IDE
};

// enum
// {
//   _IN_STATE_ = 0b00000010,
//   _OUT_STATE_ = 0b00000001,
//   _MID_STATE_ = 0b00000000,
//   _IDLE_STATE_ = 0b00000011
// };

int voice,lastvoice,sendvoice;

void Sensor_Class::setup()
{
  Serial.begin(115200);
  pinMode(SENSOR_ONE_PIN, INPUT_PULLUP);
  pinMode(SENSOR_ONE_TWO, INPUT_PULLUP);
  ui_stateProgram = SENSOR_WAIT;
}

void Sensor_Class::loop()
{ 
    if (ui_stateProgram == SENSOR_READ)
    { 
      Serial.println("Có thể đọc " +String(last_Volt) + "   status: " + String(statusVoice));
      readPinState();
      if (lastvoice != 0)
      {
        lastvoice =0;
        ui_stateProgram = SENSOR_WAIT;
      }else if(lastvoice == 0 ){
        if (statusVoice == runBat)
        {
          ui_stateProgram = SENSOR_OFF;
        }else{
          ui_stateProgram = SENSOR_READ;
        }
      }
      ul_timeRepeat = 0;
    }
    else if (ui_stateProgram == SENSOR_WAIT)
    { 
      Serial.println("Đang đợi đọc");
      ul_timeRepeat = 5000;
      ui_stateProgram = SENSOR_OFF;
    }else if(ui_stateProgram == SENSOR_OFF){
      if(statusVoice == runBat)
      {  
        int stateRun = 1;
        Serial.println("Pin yếu nè");
        if(stateRun = 1){
          voice = sayLowPower;
          ui_stateProgram = SENSOR_VOICEBAT;
        }else if(stateRun = 0){
          ui_stateProgram = SENSOR_OFF;
        }
      }else if(statusVoice == runVoice){
        ui_stateProgram = SENSOR_READ;
      }
      ul_timeRepeat =0;
    }else if (ui_stateProgram == SENSOR_VOICEBAT){
      Serial.println("Đag đợi báo pin");
      ul_timeRepeat = 30000; //20s báo lại
      ui_stateProgram = SENSOR_OFF;
    }else;
}

void Sensor_Class::readPinState(){
  byte_pinState = digitalRead(SENSOR_ONE_PIN);
  byte_pinState += digitalRead(SENSOR_ONE_TWO) << 1;
  stateProcess();
}

void Sensor_Class::stateProcess(){
  switch (byte_pinState)
  {
  case _MID_STATE_:
    Serial.println("O giua");
    break;
  case _OUT_STATE_:
    //    Serial.println("cb ngoai active");

    if (byte_lastPinState == _MID_STATE_)
    {
      Serial.println("*****Da di vao*****");
      byte_lastPinState = _IDLE_STATE_;
      voice = sayHello;
      lastvoice = sayHello;
    }
    else
      ;

    break;
  case _IDLE_STATE_:
    //    Serial.println("khong co gi");
    break;
  case _IN_STATE_:
    //    Serial.println("cb trong active");

    if (byte_lastPinState == _MID_STATE_)
    {
      Serial.println("=====Da di ra=======");
      byte_lastPinState = _IDLE_STATE_;
      voice = sayGoobye;
      lastvoice = sayGoobye;
    }
    else
      ;
    break;
  }

  if ((byte_lastPinState != byte_pinState) && (byte_pinState != _IDLE_STATE_))
  {
    byte_lastPinState = byte_pinState;
  }
}

Sensor_Class Sensor_Program;
