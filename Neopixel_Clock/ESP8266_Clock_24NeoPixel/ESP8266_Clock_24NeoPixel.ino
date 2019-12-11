#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "TimeClient.h"

#define PIN D4
long lastUpdate = millis();
long lastSecond = millis();
long lastRainbow = millis();

String hours, minutes, seconds;
int currentSecond, currentMinute, currentHour;

char ssid[] = "MakerLab";  //  your network SSID (name)
char pass[] = "makerlab03050709";       // your network password

const float UTC_OFFSET = 7;
TimeClient timeClient(UTC_OFFSET);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN);

int r, g, b;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  strip.begin();
  strip.setBrightness(10);
  strip.show();

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    //    delay(500);
    Serial.print(".");
    runStart(5);
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  timeClient.updateTime();
  updateTime() ;
  lastUpdate = millis();
  lastSecond = millis();
  runStart(50);
  clearstrip();
}

void loop()
{
  autoConnect();

  if ((millis() - lastUpdate) > 1800000) updateTime();

  if ((millis() - lastSecond) > 1000)
  {
    r = random(0, 255);
    g = random(0, 255);
    b = random(0, 255);
    strip.setPixelColor(currentSecond / 2.5, 0, 0, 0);
    strip.setPixelColor(currentMinute / 2.5, 0, 0, 0);
    strip.setPixelColor(currentHour * 2, 0, 0, 0);
    strip.show();
    lastSecond = millis();
    currentSecond++;
    if (currentSecond > 59)
    { currentSecond = 0;
      currentMinute++;
      if (currentMinute > 59) {
        currentMinute = 0;
        currentHour++;
        if (currentHour > 12) currentHour = 0;
      }
    }
    String currentTime = String(currentHour) + ':' + String(currentMinute) + ':' + String(currentSecond);
    Serial.println(currentTime);
    //    strip.setPixelColor(currentSecond / 2.5, 0, 0, 255);
    strip.setPixelColor(currentSecond / 2.5, r, g, b);
    strip.setPixelColor(currentMinute / 2.5, 0, 255, 0);
    strip.setPixelColor(currentHour * 2, 255, 0, 0);
    strip.show();
  }
}

void runStart(int count) {
  for (int i = 0; i < count ; i++)
  {
    for (int i = 0; i < 24; i++) {
      int r = random(0, 255);
      int g = random(0, 255);
      int b = random(0, 255);
      strip.setPixelColor(i, strip.Color(r, g, b));
      strip.show();
      delay(5);
    }
  }
}

void clearstrip() {
  for (int i = 24; i >= 0; i--) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(2);
  }
}

void autoConnect() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Lost WiFi Connection! Restarting...");
    ESP.restart();
  }
}

void updateTime()
{
  hours = timeClient.getHours();
  minutes = timeClient.getMinutes();
  seconds = timeClient.getSeconds();
  currentHour = hours.toInt();
  if (currentHour > 12) currentHour = currentHour - 12;
  currentMinute = minutes.toInt();
  currentSecond = seconds.toInt();
  lastUpdate = millis();
}
