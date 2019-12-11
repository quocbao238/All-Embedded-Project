#include "Offical_IO.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(RX_SW, TX_SW); // (Rx,Tx  > Tx,Rx)

int lastValue;
char incomingByte;
String inputString;

void setup() {
  Serial.begin(9600);
  Serial.println("Start Setting");
  mySerial.begin(9600);
  pinModes(); 
  readStatusRL();
  delay(10000);
  setup_readSim800L();
  Serial.println("Setting OK");
}

void loop() {
  Sim800L_Buffer();
}

//void boot_sim() {
//  mySerial.println("AT+CMGF=1"); // Set the Mode as Text Mode
//  delay(150);
//  mySerial.println("AT+CMGS=\"+84" + NumberPhone + "\"");
//  delay(150);
//  mySerial.print("Da khoi dong Module SIM thanh cong trang thai hien tai...  "); // Enter the custom message
//  if (digitalRead(RELAY) == 1) {
//    mySerial.print("----ON!---- From GSM SIM"); // Enter the custom message
//  } else {
//    mySerial.print("----OFF!---- From GSM SIM"); // Enter the custom message
//  }
//  delay(150);
//  mySerial.write((byte)0x1A); // End of message character 0x1A : Equivalent to Ctrl+z
//  delay(50);
//  mySerial.println();
//}

void send_SMS() 
{
  mySerial.println("AT+CMGS=\"+84" + NumberPhone + "\"");
  delay(150);
  if (digitalRead(RELAY) == 1) {
    mySerial.print("----ON!---- From GSM SIM"); // Enter the custom message
  }
  if (digitalRead(RELAY) == 0) {
    mySerial.print("----OFF!---- From GSM SIM"); // Enter the custom message
  }
  delay(100);
  mySerial.write((byte)0x1A); // End of message character 0x1A : Equivalent to Ctrl+z
  delay(150);
  mySerial.println();
  Serial.println("Sending: " + String(digitalRead(RELAY)));
}

void pinModes() {
  pinMode(RELAY, OUTPUT);
}

void writeONStatusRL() {
  digitalWrite(RELAY, ON);
  delay(100);
}

void writeOFFStatusRL() {
  digitalWrite(RELAY, OFF);
  delay(100);
}

void readStatusRL() {
  lastValue = EEPROM.read(add_value);
  digitalWrite(RELAY, lastValue);
}

void setup_readSim800L() {
  while (!mySerial.available()) {
    mySerial.println("AT");
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected!");
  mySerial.println("AT+CMGF=1");  //Set SMS to Text Mode
  delay(1000);
  mySerial.println("AT+CNMI=1,2,0,0,0");  //Procedure to handle newly arrived messages(command name in text: new message indications to TE)
  delay(1000);
  mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read Unread Messages
}

void Sim800L_Buffer() {
  if (mySerial.available()) {
    delay(100);
    // Serial Buffer
    while (mySerial.available()) {
      incomingByte = mySerial.read();
      inputString += incomingByte;
    }
    delay(10);
    Serial.println(inputString);
    inputString.toUpperCase(); //
    if (inputString.indexOf("ON") > -1) {
      writeONStatusRL();
      Serial.println("Relay ON");
      send_SMS();
    }

    if (inputString.indexOf("OFF") > -1) {
      writeOFFStatusRL();
      Serial.println("Relay OFF");
      send_SMS();
    }
    delay(50);
    if (inputString.indexOf("OK") == -1) {
      mySerial.println("AT+CMGDA=\"DEL ALL\"");
      delay(1000);
      Serial.println("DELETE ALL !!!");
      EEPROM.write(add_value, digitalRead(RELAY));
    }
    inputString = "";
  }
}
