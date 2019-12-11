/* 
 * Controller LED NodeMCU with Blynk App
 * Auth: QuocBao
 * Source code with Blynk
 * Tutorial: https://www.makerlab.vn/iot-with-blynk-bai-1-bat-tat-den-tu-xa/
 */

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "YourAuthToken"; // Nhập AuthToken
char ssid[] = "YourNetworkName"; // Nhập tên WiFi
char pass[] = "YourPassword";   // Nhập password WiFi

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "makerblynk.ddns.net", 8080);
}

void loop()
{
  Blynk.run();
}
