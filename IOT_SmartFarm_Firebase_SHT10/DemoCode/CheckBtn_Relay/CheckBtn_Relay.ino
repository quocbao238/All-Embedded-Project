/*  BQB Code Demo Test
 *  Check Relay
 *  Check Button
 *  Check Sensor
 */

#define RL1 16
#define RL2 14
#define RL3 12

#define Btn1 13
#define Btn2 5
#define Btn3 4

#define SHT_XANH 0 // CLK
#define SHT_VANG 2 // Data
SHT1x sht1x(SHT_VANG, SHT_XANH);

void setup() {
  Serial.begin(115200);
  setPinModes();
  Serial.println("Checking....!!!");
}

void loop() {
//  checkRelay();
//  checkButton();
  checkBtn_Relay();
}

void setPinModes(){
  pinMode(RL1,OUTPUT);
  pinMode(RL2,OUTPUT);
  pinMode(RL3,OUTPUT);
  
  pinMode(Btn1,INPUT);
  pinMode(Btn2,INPUT);
  pinMode(Btn3,INPUT);

  digitalWrite(RL1,HIGH);
  digitalWrite(RL2,HIGH);
  digitalWrite(RL3,HIGH);
}


void checkBtn_Relay(){
  digitalWrite(RL1,digitalRead(Btn1));
  digitalWrite(RL2,digitalRead(Btn2));
  digitalWrite(RL3,digitalRead(Btn3));
}

void checkRelay(){
  int relaySate1;
  int relaySate2;
  int relaySate3;
  
  
  digitalWrite(RL1,HIGH);
  digitalWrite(RL2,HIGH);
  digitalWrite(RL3,HIGH);
  relaySate1 = digitalRead(RL1);
  relaySate2 = digitalRead(RL2);
  relaySate3 = digitalRead(RL3);
  Serial.println( "Rl one: "+String(relaySate1)+
                 "---Rl two: "+String(relaySate2)+
                 "---Rl three: "+String(relaySate3));
  delay(1000);

  digitalWrite(RL1,LOW);
  digitalWrite(RL2,LOW);
  digitalWrite(RL3,LOW);
  relaySate1 = digitalRead(RL1);
  relaySate2 = digitalRead(RL2);
  relaySate3 = digitalRead(RL3);
  Serial.println( "Rl one: "+String(relaySate1)+
                 "---Rl two: "+String(relaySate2)+
                 "---Rl three: "+String(relaySate3));
   delay(1000);              

}

void checkButton(){
  int btnState1 = digitalRead(Btn1);
  int btnState2 = digitalRead(Btn2);
  int btnState3 = digitalRead(Btn3);
  Serial.println( "Btn one: "+String(btnState1)+
                 "---Btn two: "+String(btnState2)+
                 "---Btn three: "+String(btnState3));
}

void readSHT()
{
  float temp_c;
  float temp_f;
  float humidity;

  // Read values from the sensor
  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();

  // Print the values to the serial port
  Serial.print("Temperature: ");
  Serial.print(temp_c, DEC);
  Serial.print("C / ");
  Serial.print(temp_f, DEC);
  Serial.print("F. Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(2000);
}
