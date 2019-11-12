#include "include.h"

// unsigned long
int rdTemp, rdHumi,value;
unsigned long timeReadSensor = 0;

// Vòng này chỉ chạy 1 lần
void setup() {
  setPinModes();
  setupWiFi();
  getValue();
  dht.begin();  // Hàm khởi chạy cảm biến ! 
}

// Vòng chạy luân hồi
void loop() {
  rsdSensor();
  readEvent();  
  // debug();
  Serial.println(millis());
  yield();
}


void debug() {
  Serial.println("Nhiệt độ = " + String(rdTemp) + 
                 + "--Dộ ẩm = " + String(rdHumi));
  yield();
}
void getValue() {

  /*
    Lấy dữ liệu từ cơ sở dữ liệu về
  */ 

  //Value of Controller

  FirebaseObject getControlelrObject = Firebase.get("Controller/Button/");


  /* Set trạng thái 
    1 : ON
    0 : OFF 
    RL1 , Lấy giá trị từ database -> "0" -> Ép kiểu về interger !
  */
  digitalWrite(RL1, (getControlelrObject.getString("Btn1").toInt())); 
  digitalWrite(RL2, (getControlelrObject.getString("Btn2").toInt()));
  digitalWrite(RL3, (getControlelrObject.getString("Btn3").toInt()));
  digitalWrite(RL3, (getControlelrObject.getString("Btn4").toInt()));
  /* Tương đương delay(0) */
  yield();
}

void setupWiFi() {
  Serial.begin(115200); // Chạy debug
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Hàm khởi tạo WiFi
  Serial.print("connecting");
  /*
    Trong lúc WF chưa kết nối thì sẽ chạy hàm này
  */
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  /*
    Show IP Address
  */
  Serial.println(WiFi.localIP());

  /*
      Hàm kết nối cơ sử dữ liệu
  */
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream(PATH);
}

void setPinModes() {
  /*
      Đọc tín hiệu thì là INPUT --> pinMode(RL1,INPUT);
      Điều khiển chân là OUTPUT --> pinMode(RL2,OUTPUT);
  */
  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);
  pinMode(RL3, OUTPUT);
  pinMode(RL4, OUTPUT);
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
      // Ví dụ path = btn1 , data  = "0"
      handingeventbtn(path, data);
    }
  }
}

void handingeventbtn(String path, String data) {
  /*
     path = /Button/Btn1;
     data = 0
  */
  Serial.println(path + "=" + data);

  value = data.toInt();


  // Do board mạch thiết kế on Relay ở mức 0
  // Relay chạy khi digitalWrite(RL1, 1) --> Đèn tắt
  // Relay chạy khi digitalWrite(RL1, 0) --> Đèn bật

  if (path == "/Button/Btn1")
  {
    digitalWrite(RL1, !value);
    // Khi data = 0 -> value = 0 , !value = 1 
  } else if (path == "/Button/Btn2")
  {
    digitalWrite(RL2, !value);
  }
  else if (path == "/Button/Btn3")
  {
    digitalWrite(RL3, !value);
  }
  else if (path == "/Button/Btn4")
  {
    digitalWrite(RL4, !value);
  } 
}

void rsdSensor() {
    /*
      millis() là hàm lấy giá trị thời gian hiện tại theo milis 
      1000 mililis --> 1s
      Khi thời gian hiện tại trừ đi thời gian đọc sensor > 10s
      10s đọc 1 lần 
    */

    // Không dùng delay vì delay làm đứng chương trình , làm chậm đi quá trình điều khiển 
    // float humidity = dht.readHumidity();
    // float temp = dht.readTemperature();
    // delay(10000);

    if (millis() - timeReadSensor > 10000)
    {

      float humidity = dht.readHumidity();
      float temp = dht.readTemperature();

      // Hàm hiển thị trong Monitor
      Serial.print("Temperature: ");
      Serial.println(String(temp) + " *C");
      Serial.println("Humidity: " + String(humidity) + "%");

      if (temp <= 0 || humidity <= 0)
      {
        Firebase.setString("Controller/Sensor/Humi", "erro Humi");
        Firebase.setString("Controller/Sensor/Temp", "erro Temp");
      }
      else
      {
        Firebase.setString("Controller/Sensor/Humi", String(humidity));
        Firebase.setString("Controller/Sensor/Temp", String(temp));
      }
      timeReadSensor = millis();
  }
  // timeReadSensor = millis();

  // Lần 1 : mililis = 11s - timereadSensor(0s) > 10 --> dọc sensor
        +timeReadSensor  =  11s 
  // Lần 2 khi : millis = 22s - .....
}
