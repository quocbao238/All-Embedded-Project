
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
SSD1306  display(0x3c, 4, 5);
void setup() {
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void displayTempHumid() {
  int h = 70, t = 50, f = 120;
  display.clear();
  display.drawString(0, 0, "Humidity: " + String(h) + "%\t");
  display.drawString(0, 16, "Temp: " + String(t) + "C");
  display.drawString(0, 32, "Temp: " + String(f) + "F");
  display.drawString(0, 48, "Humidity: " + String(h) + "%\t");
}
void loop() {
  displayTempHumid();
  display.display();
  delay(2000);
}
