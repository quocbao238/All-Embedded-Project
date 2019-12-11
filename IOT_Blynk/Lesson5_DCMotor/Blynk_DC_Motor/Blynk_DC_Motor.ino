/*
   Controller/Dimmer DC Motor With Blynk
   Auth: QuocBao
   Source code with Blynk
   Tutorial: https://www.makerlab.vn/iot-with-blynk-bai-5-dieu-khien-dong-co-dc-voi-l298/
*/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define IN1 D1
#define IN2 D2


char auth[] = “YourAuthToken”; // Nhập AuthToken của bạn
char ssid[] = “YourNetworkName”; //
Nhập tên WiFi char pass[] = “YourPassword”; // Nhập password WiFi

int speeds;
boolean directions;
boolean enable;

BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_WRITE(V0)
{
  enable = param.asInt();
}

BLYNK_WRITE(V1)
{
  speeds = param.asInt() * 10.23;
}



BLYNK_WRITE(V2)
{
  directions  = param.asInt();

}

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Blynk.begin(auth, ssid, pass, "makerblynk.ddns.net", 8080);
}

void loop() {
  Blynk.run();
  Serial.println("Enable = " + String(enable));
  if (enable == 1) {
    Serial.println("Direction = " + String(directions));
    if (directions == 0) {
      backward();
    } else if (directions == 1) {
      forward();
    }
  } else {
    stops();
  }
}

void forward()
{
  analogWrite(IN1, speeds);
  analogWrite(IN2, 0);
}

void stops() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
}

void backward()
{
  analogWrite(IN1, 0);
  analogWrite(IN2, speeds);
}
