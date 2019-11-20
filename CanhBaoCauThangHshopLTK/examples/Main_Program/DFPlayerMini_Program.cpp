#include "DFPlayerMini_Program.h"
#include "Program_Gpiocrrrr.h"

enum{
  STATE_HELLO = 1,
  STATE_GOODBYE,
  STATE_LOW_POWER,
  STATE_IDE
};

SoftwareSerial mySerial(TX_DF_PLAYER, RX_DF_PLAYER, false, 256); // RX, TX

void Dfplayer_Class::setup(){
  mySerial.begin (9600);
	mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
	mp3_set_volume (30);
}

void Dfplayer_Class::loop(){
  if(ui_stateProgram == STATE_HELLO){
    Serial.println("loop Hello world " + String(ul_currentMililis));
    mp3_play (STATE_HELLO);
    ul_timeRepeat = 10000;
    ui_stateProgram = STATE_IDE;
  }else if(ui_stateProgram == STATE_GOODBYE){
    Serial.println("loop goodbye world " + String(ul_currentMililis));
    mp3_play (STATE_GOODBYE);
    ul_timeRepeat = 10000;
    ui_stateProgram = STATE_IDE;
  }else if(ui_stateProgram == STATE_LOW_POWER){
    mp3_play (STATE_LOW_POWER);
    ul_timeRepeat = 10000;
    ui_stateProgram = STATE_IDE;
  }else;
  
}

Dfplayer_Class Dfplayer_Program;
