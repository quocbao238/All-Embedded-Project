#include "Batmintion_Button.h"
#include "Arduino.h"
#include "BatmintionIO.h"

void btnClickLevelSet() {
  Serial.println("btnClickLevelSet");
  statusSet += 1;
  clearLCD = 0;
  statusButton = 1;
}


void btnClickLevelHard() {
  Serial.println("btnClickLevelHard");
  statusHard += 1;
  clearLCD = 0;
  statusButton = 1;
}

void btnClick_Trainning() {
  statusButton = 1;
  clearLCD = 0;
  trainning = 1;
  Serial.println("btnClick_Trainning");
}

void btn_DobleClickBackSet() {
  clearLCD = 0;
  statusSet = 0;
  statusButton = 1;
  Serial.println("btn_DobleClickBackSet");
}

void btn_DobleClickBackHard() {
  clearLCD = 0;
  statusHard = 0;
  statusButton = 1;
  Serial.println("btn_DobleClickBackHard");

}
void btn_ClickOut() {
  clearLCD = 0;
  statusSet = 0;
  statusHard = 0;
  trainning = 0;
  Serial.println("btn_ClickOut");
}

void btn_OutRun() {
  times_counter = 0 ;
  Serial.println("btn_OutRun");
}
