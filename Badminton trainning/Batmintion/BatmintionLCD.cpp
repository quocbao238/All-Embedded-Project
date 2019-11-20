#include "BatmintionLCD.h"
#include "BatmintionIO.h"

//void setTrainning(){
//  if (clearLCD == 0) {
//    lcd.clear();
//    clearLCD = 1;
//  } else if (clearLCD == 1) {
//    lcd.setCursor(3, 0);
//    lcd.print("Badmintion");
//    lcd.setCursor(1, 1);
//    lcd.print("Trainning.......");
//  }
//}

void b_begin() {
  if (clearLCD == 0) {
    lcd.clear();
    clearLCD = 1;
  } else if (clearLCD == 1) {
    lcd.setCursor(3, 0);
    lcd.print("Badmintion");
    lcd.setCursor(1, 1);
    lcd.print("Trainning Leds");
  }
}

void setLevel() {
  if (clearLCD == 0) {
    lcd.clear();
    clearLCD = 1;
  } else if (clearLCD == 1) {
    lcd.setCursor(0, 1);
    lcd.print("Set Level --> ");
    lcd.print(statusSet);
    lcd.setCursor(0, 0);
    lcd.print("Time Change ");
    if(statusSet == 1){
      lcd.print(StrLedEasy);
    }else if(statusSet == 2){
       lcd.print(StrLedNormal);
    }else if(statusSet == 3){
       lcd.print(StrLedHard);
    }
  }
}
void setHard() {
  if (clearLCD == 0) {
    lcd.clear();
    clearLCD = 1;
  } else if (clearLCD == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Level-> ");
    lcd.print(statusSet);
    lcd.setCursor(0, 1);
    lcd.print("Difficult");
    lcd.setCursor(10, 1);
    if (statusHard == 1) {
      lcd.print("Easy");
      lcd.setCursor(12, 0);
      lcd.print(StrTimeEasy);
    } else if (statusHard == 2) {
      lcd.print("Normal");
      lcd.setCursor(12, 0);
      lcd.print(StrTimeNormal);
    } else   if (statusHard == 3) {
      lcd.print("Hard");
      lcd.setCursor(12, 0);
      lcd.print(StrTimeHard);
    }
  }

}
