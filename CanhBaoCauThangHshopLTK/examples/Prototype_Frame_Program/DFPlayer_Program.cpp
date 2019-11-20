#include "DFPlayer_Program.h"
#include "Program_Gpio.h"
#include "Sensor_Program.h"
#include "ReadVoltage_Program.h"

// State program
enum
{
  STATE_WAIT = 1,
  STATE_LOWPOWER,
  STATE_IDE
};

SoftwareSerial mySerial(TX_DF_PLAYER, RX_DF_PLAYER,false,256); // RX, TX

void DFPlayer_Class::setup()
{ 
  mySerial.begin(9600);
  mp3_set_serial(mySerial); //set softwareSerial for DFPlayer-mini mp3 module
  mp3_set_volume(30);
  flag_volume = false;
  ul_timeRepeat = 2000;
  ui_stateProgram = STATE_IDE;
}

void DFPlayer_Class::loop()
{
  if (ui_stateProgram == STATE_WAIT)
  {
    getValue();
    ul_timeRepeat = 0;
    ui_stateProgram = STATE_LOWPOWER;
  }else if(ui_stateProgram == STATE_LOWPOWER){
     ul_timeRepeat = 0;
     ui_stateProgram = STATE_WAIT;
  }else if(ui_stateProgram == STATE_IDE){
    if(!flag_volume){
      mp3_set_volume(25);
      flag_volume = true;
    }
    ul_timeRepeat = 1000;
    ui_stateProgram = STATE_WAIT;
  }else;
}

void DFPlayer_Class::getValue(){
  if(voice == 1)
  {
    Serial.println("Say Hello");
    mp3_play(sayHello);
    voice = 0;  
  }else if(voice == 2){
    Serial.println("Say Goodbye");
    mp3_play(sayGoobye);
    voice = 0;
  }else if(voice == 3){
    Serial.println("Say LowPower");
    mp3_play(sayLowPower);
    voice =0;
  }
}

DFPlayer_Class DFPlayer_Program;
