#define RL1 16
#define RL2 14
#define RL3 12
#define Btn1 13
#define Btn2 5
#define Btn3 4
#define SHT_XANH 0
#define SHT_VANG 2
int value,lasttemp,lasthumi;
float temp;float humidity;
int rdTemp,rdHumi;
int tmpstateTemp,tmpstateHumi,DifHumi,DifTemp;

String stateTemp,stateHumi;
int statusTemp =0 ,statusHumi = 0; /// status = 1 when on , status = 0 when off;
#include <SimpleTimer.h>
#include <SHT1x.h>
#include "OneButton.h"
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define PATH "/Controller"
#define FIREBASE_HOST "humitemp-5fa8e.firebaseio.com" //Thay bằng địa chỉ firebase của bạn
#define FIREBASE_AUTH ""   //Không dùng xác thực nên không đổi
#define WIFI_SSID "Mach_Dien_Tu"   //Thay wifi và mật khẩu
#define WIFI_PASSWORD "Hshopvn123"
OneButton button1(Btn1, true);
OneButton button2(Btn2, true);
OneButton button3(Btn3, true);
SHT1x sht1x(SHT_VANG, SHT_XANH);
SimpleTimer srd_Timer;
