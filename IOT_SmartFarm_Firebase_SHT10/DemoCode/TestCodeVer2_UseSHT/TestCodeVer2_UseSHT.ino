#include "include.h"

void setup() {
  setPinModes();
  button1.attachClick(click1);
  button2.attachClick(click2);
  button3.attachClick(click3);
  setupWiFi();
  getValue();
}


void loop() {
  for (int i = 0; i < 100000; i++) {
    btnClick();
    readEvent();
    StabilityTempHumi();
    yield();
  }
  rsdSensor();
}


void debug() {
  Serial.println("Trạng thái Temp= " + String(statusTemp) + "--Trạng thái Humi= " + String(statusHumi));
  Serial.println("Nhiệt độ= " + String(temp) + "--Cài đặt nhiệt độ= " + tmpstateTemp
                 + "--Dộ ẩm= " + String(humidity) + "--Cài đặt độ ẩm= " + tmpstateHumi);
  yield();
}
void getValue() {

  FirebaseObject getValueObject = Firebase.get("Controller/Stability/");
  //Value of Stability
  stateTemp = getValueObject.getString("Temp");
  stateHumi = getValueObject.getString("Humi");
  yield();
  //Value of Dif
  FirebaseObject getDifObject = Firebase.get("Controller/Dif/");
  DifHumi = (getDifObject.getString("Humi").toInt());
  DifTemp = (getDifObject.getString("Temp").toInt());
  yield();
  //Value of Controller
  FirebaseObject getControlelrObject = Firebase.get("Controller/Button/");
  digitalWrite(RL1, (getControlelrObject.getString("Btn1").toInt()));
  digitalWrite(RL2, (getControlelrObject.getString("Btn2").toInt()));
  digitalWrite(RL3, (getControlelrObject.getString("Btn3").toInt()));
  yield();
}
void btnClick() {
  button1.tick();
  button2.tick();
  button3.tick();
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
  digitalWrite(RL2, 1);
  digitalWrite(RL1, 1);
  digitalWrite(RL3, 1);
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
      //      blinkCheck();
    }
  }
}

void StabilityTempHumi() {
  tmpstateTemp = stateTemp.toInt();
  tmpstateHumi = stateHumi.toInt();

  /*
     Nhiệt độ set = 30 , dif = 5 -> Chênh lệch 5
     Ví dụ nhiệt độ  > cài đặt set ->> ON;
     Ví dụ độ ẩm > Cài đặt set+ Def -> OFF
     Ví dụ 35 >= 30 --> ON
     Ví dụ 25 <= 25 --> OFF
  */

  if (temp >= tmpstateTemp && temp > 0 && statusTemp == 0) {
    /*
        On Relay Temp -> status Temp = 1;
    */
    digitalWrite(RL2, 0);
    Firebase.setString("Controller/Button/Btn2", "0");
    statusTemp = 1;
  } else if (temp <= (tmpstateTemp - DifTemp) && temp && statusTemp == 1) {
    /*
        Off Relay Temp -> status Temp = 0;
    */
    digitalWrite(RL2, 1);
    Firebase.setString("Controller/Button/Btn2", "1");
    statusTemp = 0;
  }
  /*
     Độ ẩm thì ngược lại Set 70 -> Dif =5 -> Chênh lệch 5
     Độ ẩm = 50
     Ví dụ độ ẩm < Cài đặt set -> ON
     Ví dụ độ ẩm > Cài đặt set+ Def -> OFF
     Ví dụ 50 <= 70 --> ON
     Ví dụ 75 >= 75 --> OFF
  */
  if (humidity <= tmpstateHumi && humidity > 0 && statusHumi == 0) {
    /*
      ON Relay Humi -> status Humi = 1;
    */
    digitalWrite(RL3, 0);
    Firebase.setString("Controller/Button/Btn3", "0");
    statusHumi = 1;
  } else if (humidity >= (tmpstateHumi + DifHumi) && humidity > 0 && statusHumi == 1 ) {
    /*
      OFF Relay Humi -> status Humi = 0;
    */
    digitalWrite(RL3, 1);
    Firebase.setString("Controller/Button/Btn3", "1");
    statusHumi = 0;
  }
}

void handingeventbtn(String path, String data) {
  /*
     path = /Button/Btn1;
     data = 20
  */
  Serial.println(path + "=" + data);

  value = data.toInt();

  if (path == "/Button/Btn1") {
    digitalWrite(RL1, value);
  } else if (path == "/Button/Btn2") {
    digitalWrite(RL2, value);
  } else if (path == "/Button/Btn3") {
    digitalWrite(RL3, value);
  } else if (path == "/Stability/Humi") {
    stateHumi = String(value);
  } else if (path == "/Stability/Temp") {
    stateTemp = String(value);
  } else if (path == "/Dif/Humi") {
    DifHumi = value;
  } else if (path == "/Dif/Temp") {
    DifTemp = value;
  }
}

void rsdSensor() {
  lasttemp = sht1x.readTemperatureC();
  lasthumi = sht1x.readHumidity();
  
  if (lasttemp > 0 && lasthumi > 0) {
    temp = lasttemp;
    humidity = lasthumi;
  }
  Serial.print("Temperature: ");
  Serial.println(String(temp) + "oC");
  Serial.println("Humidity: " + String(humidity) + "%");

  if (temp <= 0 || humidity <= 0) {
    Firebase.setString("Controller/Sensor/Humi", "erro Humi");
    Firebase.setString("Controller/Sensor/Temp", "erro Temp");
  } else {
    Firebase.setString("Controller/Sensor/Humi", String(humidity));
    Firebase.setString("Controller/Sensor/Temp", String(temp));
  }
  yield();
  debug();

}

void click1() {
  digitalWrite(RL1, !digitalRead(RL1));
  String data = String(digitalRead(RL1));
  Firebase.setString("Controller/Button/Btn1", data);
}

void click2() {
  //  String data = String(digitalRead(RL2));
  String data;
  if (digitalRead(RL2) == 0) {
    statusTemp = 1;
    data = "1";
    digitalWrite(RL2, !digitalRead(RL2));
  } else if (digitalRead(RL2) == 1) {
    statusTemp = 0;
    data = "0";
    digitalWrite(RL2, !digitalRead(RL2));
  }
  Firebase.setString("Controller/Button/Btn2", data);
}

void click3() {
  //  digitalWrite(RL3, !digitalRead(RL3));
  //  String data = String(digitalRead(RL3));
  String data;
  if (digitalRead(RL3) == 0) {
    statusHumi = 1;
    data = "1";
    digitalWrite(RL3, !digitalRead(RL3));
  } else if (digitalRead(RL3) == 1) {
    statusHumi = 0;
    data = "0";
    digitalWrite(RL3, !digitalRead(RL3));
  }
  Firebase.setString("Controller/Button/Btn3", data);
}

void blinkCheck() {
  digitalWrite(RL1, LOW);
  delay(500);
  digitalWrite(RL1, HIGH);
  delay(500);
}
