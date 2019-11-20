#include "helloWorld_Program.h"
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
    Serial.println("loop Hello world " + String(ul_currentMililis));
    ul_timeRepeat = 1000;
    ui_stateProgram = STATE_GOODBYE;
  }else if(ui_stateProgram == STATE_GOODBYE){
    Serial.println("loop goodbye world " + String(ul_currentMililis));
    ul_timeRepeat = 500;
    ui_stateProgram = STATE_HELLO;
  }else;
  
}

HelloWorld_Class HelloWorld_Program;
