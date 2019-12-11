/*
   Controller LED NodeMCU with Button and Blynk App
   Auth: QuocBao
   Source code with Blynk
   Tutorial: https://www.makerlab.vn/iot-with-blynk-bai-2-dong-bo-nut-nhan-dieu-khien-den/
*/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BUTTON D3 // Chân nối với nút nhấn onboard
#define LED D0 // Chân nối với đèn LED onboard

char auth[] = "YourAuthToken"; // Nhập AuthToken
char ssid[] = "YourNetworkName"; // Nhập tên WiFi
char pass[] = "YourPassword"; // Nhập password WiFi

boolean checkData = false;
int lastBtnStatus;
int VIRTUAL_PIN;

BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_WRITE(V0)
{
  VIRTUAL_PIN = param.asInt();
  checkData = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Blynk.begin(auth, ssid, pass, "makerblynk.ddns.net", 8080);
  lastBtnStatus = digitalRead(BUTTON);
}

void loop() {
  Blynk.run();
  if (checkData == true) {
    digitalWrite(LED, VIRTUAL_PIN);
    checkData == false;
  }

  if (digitalRead(BUTTON) == 0)
  {
    delay(100);
    if (digitalRead(BUTTON) != 0)
    {
      VIRTUAL_PIN = !VIRTUAL_PIN;
      digitalWrite(LED, VIRTUAL_PIN);
      Blynk.virtualWrite(V0, VIRTUAL_PIN);
      Serial.println("In Here" + String(VIRTUAL_PIN));
    }
  }

}
