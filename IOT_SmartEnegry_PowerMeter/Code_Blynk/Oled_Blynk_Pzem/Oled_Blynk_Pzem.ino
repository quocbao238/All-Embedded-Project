#include <Hshop_led_blink.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PZEM004T.h> //https://github.com/olehs/PZEM004T
PZEM004T pzem(&Serial);                                        /// use Serial
IPAddress ip(192, 168, 1, 1);
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
SSD1306  display(0x3c, 4, 5);
float voltage_blynk = 0;
float current_blynk = 0;
float power_blynk = 0;
float energy_blynk = 0; float cs = 0;

float is = 0;
char auth[] = "8911113ba5cf493390b4624e28cd7f4d";
char ssid[] = "Mach_Dien_Tu";
char pass[] = "Hshopvn123";
unsigned long lastMillis = 0;

Hshop_led_blink led1(2, 100);


void setup() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.clear();
  display.drawString(15, 0, "Electricity Meter");
  display.drawString(15, 16, "   PZEM 004T");
  display.drawString(0, 32, "Wait WiFi");
  display.drawString(0, 48, "    Connected........");

  display.display();
  pzem.setAddress(ip);
  Blynk.begin(auth, ssid, pass);
  led1.enable = true;

}
void dispayPZEM() {
  float v = pzem.voltage(ip);
  if (v >= 0.01) {

    voltage_blynk = v;  //V
  }
  float i = pzem.current(ip);
  if (i >= 0.01) {
    current_blynk = i;     //A
  }
  float p = pzem.power(ip);
  if (p >= 0.01) {
    power_blynk = p;        //W
  }
  float e = pzem.energy(ip);
  if (e >= 0.01) {
    energy_blynk = e;   ///Wh
  }
  cs = e / 1000;
  is = p / v;
  display.clear();
  display.drawString(0, 0, "Voltage: " + String(v) + " V\t");
  display.drawString(0, 16, "Ampe: " + String(is) + " A");
  display.drawString(0, 32, "Power: " + String(p) + " W");
  display.drawString(0, 48, "Ene: " + String(cs) + " kWh\t");
  delay(1000);
}
void loop() {
  Blynk.run();
  led1.run();
  dispayPZEM();
  display.display();
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    Blynk.virtualWrite(V1, voltage_blynk);
    Blynk.virtualWrite(V2, current_blynk  );
    Blynk.virtualWrite(V3, power_blynk);
    Blynk.virtualWrite(V4, energy_blynk  );
    Blynk.virtualWrite(V5, lastMillis  );
    Blynk.virtualWrite(V6, cs); // Ene KWh
    Blynk.virtualWrite(V7, is); // C/suat

  }
}
