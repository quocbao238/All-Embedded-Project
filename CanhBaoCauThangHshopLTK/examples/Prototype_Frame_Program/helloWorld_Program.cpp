#include "helloWorld_Program.h"
#include "Sensor_Program.h"
#include "DFPlayer_Program.h"
#include "ReadVoltage_Program.h"
enum{
  STATE_HELLO = 0,
  STATE_GOODBYE,
  STATE_IDE
};

void HelloWorld_Class::setup(){
  Serial.begin(115200);
  Serial.println("Setup Hello world");
  
}

void HelloWorld_Class::loop(){
  if(ui_stateProgram == STATE_HELLO){
    Serial.println("Debug Voice= " + String(voice) +"   StatusVoice= " +String(statusVoice)
    +"   Voltage= " + String(last_Volt) +"   Lastvoice= " +String(lastvoice) );
    // Serial.println("loop Hello world ");
    ul_timeRepeat = 1000;
    ui_stateProgram = STATE_GOODBYE;
  }else if(ui_stateProgram == STATE_GOODBYE){
    // Serial.println("loop goodbye world Voice = " + String(voice));
    // Serial.println("loop Hello world ");
    ul_timeRepeat = 100;
    ui_stateProgram = STATE_HELLO;
  }else;
}


HelloWorld_Class HelloWorld_Program;
