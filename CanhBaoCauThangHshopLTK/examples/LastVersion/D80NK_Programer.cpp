#include "D80NK_Program.h"
#include "Program_Gpio.h"
// #include "OneButton.h"
// State program
enum{
  SENSOR_READ = 0,
  SENSOR_OFF,
  STATE_IDE
};

int couterUp = 0;
int couterDown = 0;
int statesUp, statesDown;
int lastcouterUp,lastcouterDown;
int voice;

OneButton SensorUp(SENSOR_ONE_PIN, true);
OneButton SensorDown(SENSOR_ONE_TWO, true);

void D80NK_Class::setup()
{
  Serial.begin(115200);
  while (!Serial)
  { 
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  SensorUp.setPressTicks(50);
  SensorDown.setPressTicks(50);
}

void D80NK_Class::loop()
{
  if (ui_stateProgram == SENSOR_OFF)
  {
    checkStatus();
    ul_timeRepeat = 0;
    ui_stateProgram = SENSOR_READ;
  }
  else if (ui_stateProgram == SENSOR_READ)
  {
    getValue();
    ul_timeRepeat = 0;
    ui_stateProgram = SENSOR_OFF;
  }
  else;
}

void D80NK_Class::checkStatus()
{
  if ((couterUp == 0) && (couterDown == 0))
  {
    SensorUp.attachPress(SensorUp_Up);
    SensorDown.attachPress(SensorDown_Up);
    SensorUp.tick();
    SensorDown.tick();
    if ((statesUp == 1) && (statesDown == 0))
    {
      Serial.println("Waiting....");
      Serial.print("Send Up   ");
      statesUp = 0;
      voice = 1;
      Serial.println(voice);
    }
    else if ((statesDown == 1) && (statesUp == 0))
    {
      Serial.println("Waiting....");
      Serial.println("Send Down");
      statesDown = 0;
      voice =2;
      Serial.println(voice);
    }
  }
}

void D80NK_Class::getValue()
{
  if (couterUp == 1 && couterUp > couterDown){
    SensorDown.attachPress(SensorUp_Down);
    SensorDown.tick();  
    if(couterUp == 0){
      statesUp = 1;
      statesDown = 0;
    }
  }else if(couterDown ==1 ){
    SensorUp.attachPress(SensorDown_Down);
    SensorUp.tick();
    statesUp = 0;
    statesDown = 1;
  }
}



void SensorUp_Up()
{
  couterUp++;
  Serial.println("Couter Up = " + String(couterUp));
}

void SensorUp_Down()
{
  couterUp=0;
  Serial.println("Couter Up = " + String(couterUp));
}

void SensorDown_Up()
{
  couterDown++;
  Serial.println("Couter Down = " + String(couterDown));
}

void SensorDown_Down()
{
  couterDown=0;
  Serial.println("Couter Down = " + String(couterDown));
}

D80NK_Class D80NK_Program;
