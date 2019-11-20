#include "include.h"

void setup() {
  button1.attachClick(click1);
  button2.attachClick(click2);
  button3.attachClick(click3);
  setPinModes();
  setupWiFi();
}

void loop() {
  button1.tick();
  button2.tick();
  button3.tick();
  readEvent();
  //  sendSensor();
  yield();
}

void setupWiFi() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream(PATH);
}

void setPinModes() {
  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);
  pinMode(RL3, OUTPUT);
  digitalWrite(RL2, value);
  digitalWrite(RL1, value);
  digitalWrite(RL3, value);
}

void readEvent() {

  if (Firebase.failed()) {
    Serial.println(Firebase.error());
  }

  if (Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    if (event.success()) {
      // Lấy dữ liệu đã thay đổi trên firebase
      String path = event.getString("path");
      String data = event.getString("data");
      handingeventbtn(path, data);
    }
  }
}



void handingeventbtn(String path, String data) {
  /*
     path = /Button/Btn1;
     data = 20
  */
  Serial.println(path + "=" + data);

  value = data.toInt();
  if (path == "/Button/Btn1")
  {
    digitalWrite(RL1, value);
  } else if (path == "/Button/Btn2")
  {
    digitalWrite(RL2, value);
  }
  else if (path == "/Button/Btn3")
  {
    digitalWrite(RL3, value);
  }
}

void sendSensor() {
  temp = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
  Serial.print("Temperature: ");
  Serial.println(String(temp) + "oC");
  Serial.println("Humidity: " + String(humidity) + "%");
  delay(2000);
}

void click1() {
  digitalWrite(RL1, !digitalRead(RL1));
  String data = String(digitalRead(RL1));
  Firebase.setString("Controller/Button/Btn1", data);
}

void click2() {
  digitalWrite(RL2, !digitalRead(RL2));
  String data = String(digitalRead(RL2));
  Firebase.setString("Controller/Button/Btn2", data);
}

void click3() {
  digitalWrite(RL3, !digitalRead(RL3));
  String data = String(digitalRead(RL3));
  Firebase.setString("Controller/Button/Btn3", data);
}
