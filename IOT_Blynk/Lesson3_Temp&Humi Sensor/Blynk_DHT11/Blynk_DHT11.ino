/*
   Read Sensor DHT11 NodeMCU send to Blynk App
   Auth: QuocBao
   Source code with Blynk
   Tutorial: https://www.makerlab.vn/iot-with-blynk-bai-3-doc-du-lieu-dht11/
*/

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "YourAuthToken"; // Nhập AuthToken
char ssid[] = "YourNetworkName"; // Nhập tên WiFi
char pass[] = "YourPassword";   // Nhập password WiFi

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Serial.print("Nhiet do: " + String(t));
  Serial.println("  Do am: " + String(h));
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "makerblynk.ddns.net", 8080);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
