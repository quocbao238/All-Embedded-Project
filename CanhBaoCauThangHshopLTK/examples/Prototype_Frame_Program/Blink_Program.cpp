#include "Blink_Program.h"
#include "Program_Gpio.h"

// State program
enum{
  STATE_ON = 0,
  STATE_OFF,
  STATE_IDE
};

#define ACTIVE      (HIGH)

void Blink_Class::setup()
{
  pinMode(LED_PIN, OUTPUT);
  // tat led
  digitalWrite(LED_PIN, !ACTIVE);

}

void Blink_Class::loop()
{
  if (ui_stateProgram == STATE_ON)
  {
    digitalWrite(LED_PIN, ACTIVE);
    ul_timeRepeat = 100;
    ui_stateProgram = STATE_OFF;

  }
  else if (ui_stateProgram == STATE_OFF)
  {
    digitalWrite(LED_PIN, !ACTIVE);
    ul_timeRepeat = 2000;
    ui_stateProgram = STATE_ON;
  }else;
  
}

Blink_Class Blink_Program;
