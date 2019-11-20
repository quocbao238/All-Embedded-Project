#include "Batmintionled.h"
#include "BatmintionIO.h"


void b_buzzerTrainningHIGH(){
  digitalWrite(BUZZER,LOW);
}

void b_buzzerTrainningLOW(){
  digitalWrite(BUZZER,HIGH);
}

void b_onLeft() {
  digitalWrite(ledPin[0], HIGH);
  digitalWrite(ledPin[3], HIGH);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], LOW);
  digitalWrite(ledPin[4], LOW);
}

void b_onRight() {

  digitalWrite(ledPin[2], HIGH);
  digitalWrite(ledPin[4], HIGH);
  digitalWrite(ledPin[0], LOW);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[3], LOW);
}

void b_ledon() {
  for (int o = 0 ; o < pinCount; o++) {
    digitalWrite(ledPin[o], HIGH);
  }
}

void b_ledoff() {
  for (int o = 0 ; o < pinCount; o++) {
    digitalWrite(ledPin[o], LOW);
  }
}

void b_led1() {
  digitalWrite(ledPin[0], HIGH);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], LOW);
  digitalWrite(ledPin[3], LOW);
  digitalWrite(ledPin[4], LOW);
}

void b_led2() {

  digitalWrite(ledPin[0], LOW);
  digitalWrite(ledPin[1], HIGH);
  digitalWrite(ledPin[2], LOW);
  digitalWrite(ledPin[3], LOW);
  digitalWrite(ledPin[4], LOW);

}

void b_led3() {

  digitalWrite(ledPin[0], LOW);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], HIGH);
  digitalWrite(ledPin[3], LOW);
  digitalWrite(ledPin[4], LOW);
}

void b_led4() {

  digitalWrite(ledPin[0], LOW);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], LOW);
  digitalWrite(ledPin[3], HIGH);
  digitalWrite(ledPin[4], LOW);

}

void b_led5() {

  digitalWrite(ledPin[0], LOW);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], LOW);
  digitalWrite(ledPin[3], LOW);
  digitalWrite(ledPin[4], HIGH);
  
}
