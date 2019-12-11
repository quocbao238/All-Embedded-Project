/*
   RC Servo with Blynk
   Auth: QuocBao
   Source code with Blynk
   Tutorial: https://www.makerlab.vn/iot-with-blynk-bai-4-dieu-khien-dong-corc-servo/
   */


#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char auth[] = “YourAuthToken”; // Nhập AuthToken của bạn
char ssid[] = “YourNetworkName”; // Nhập tên WiFi
char pass[] = “YourPassword”; // Nhập password WiFi

Servo servo;
int pos;

BLYNK_WRITE(V0)
{
  servo.write(param.asInt());
  if (pos < param.asInt()) {
    for (pos; pos <= param.asInt(); pos += 1) {
      servo.write(pos);
      delay(10);
    }
  } else {
    for (pos; pos >= param.asInt(); pos -= 1) {
      servo.write(pos);
      delay(10);
    }
  }
}

BLYNK_WRITE(V1)
{
  if (param.asInt() == 1) {
    left();
  }
}

BLYNK_WRITE(V2)
{
  if (param.asInt() == 1) {
   right();
  }
}


void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "makerblynk.ddns.net", 8080);
  servo.attach(D2);
}

void loop()
{
  Blynk.run();
}


void left() {
  for (pos; pos <= 180; pos += 1) {
    servo.write(pos);
    delay(10);
  }
}

void right() {
  for (pos; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(10);
  }
}
