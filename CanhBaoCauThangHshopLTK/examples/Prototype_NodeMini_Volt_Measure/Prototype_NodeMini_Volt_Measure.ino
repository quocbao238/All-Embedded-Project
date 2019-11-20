/*
  Tham khao: https://arduinodiy.wordpress.com/2016/12/25/monitoring-lipo-battery-voltage-with-wemos-d1-minibattery-shield-and-thingspeak/

  Wiring:
  GND-----R100K----A0-------R220K----R1652K------Vmeasure.
  
*/

#define R_GND  103//9.70 //10k
#define R_RAW  (220+1652)// //10k
#define R_CALCULATE   (R_GND/(R_GND+R_RAW)) 
#define V_REF   1.0//3.31//5.0   //V
#define V_RAW_WARN  3700   // mV

const int numReadings = 20;

int readings[numReadings];      // the readings from the analog input
unsigned char readIndex = 0;              // the index of the current reading
unsigned char tem_readIdex = 0;
int total = 0;                  // the running total
float average = 0;                // the average
float last_Volt = 0;

int inputPin = A0;

unsigned long timer_VoltRaw_max = 100, timer_VoltRaw = 0;
void setup()
{
  pinMode(inputPin, INPUT);   // sets the pin as output
  Serial.begin(115200);
  Serial.println("Start");
  
}

void loop()
{
  checkVoltRaw();
}

void checkVoltRaw(){
  if(millis() - timer_VoltRaw >= timer_VoltRaw_max){
    float val = 0;
    timer_VoltRaw = millis();
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = analogRead(inputPin);
    Serial.print(readings[readIndex]);
    Serial.print("\t");
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
    tem_readIdex++;
  
    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
    if (tem_readIdex >= numReadings) {
      tem_readIdex = numReadings;
    }
  
    // calculate the average:
    average = total / tem_readIdex;
    
    last_Volt = average/1023*18.56;
    
    Serial.print(average);
    Serial.print("\t");
    Serial.println(last_Volt);
  }
}
