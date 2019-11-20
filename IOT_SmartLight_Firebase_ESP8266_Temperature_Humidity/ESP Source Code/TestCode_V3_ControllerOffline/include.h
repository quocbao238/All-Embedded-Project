
/*
    Khai báo thư viện
*/

#include <SimpleTimer.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "DHT.h"

#define RL1 16              // Chân Relay 1
#define RL2 14
#define RL3 12
#define RL4 13
#define DHTPIN 5            // Chân của cảm biến nhiệt độ độ ẩm
#define DHTTYPE DHT11       
#define PATH "/Controller"

#define FIREBASE_HOST "doandtb.firebaseio.com" //Thay bằng địa chỉ firebase 
#define FIREBASE_AUTH ""   //  Chỉ dùng khi nào cần bảo mật

/*
    Id wifi và password
*/
#define WIFI_SSID "dongta123"    
#define WIFI_PASSWORD "taydocne123"

DHT dht(DHTPIN, DHTTYPE);       // Constructor

extern int value;
extern int rdTemp, rdHumi;
extern unsigned long timeReadSensor;
