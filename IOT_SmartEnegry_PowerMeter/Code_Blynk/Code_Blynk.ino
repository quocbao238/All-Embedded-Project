#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PZEM004T.h> //https://github.com/olehs/PZEM004T
PZEM004T pzem(&Serial);                                        /// use Serial
IPAddress ip(192,168,1,1);

float voltage_blynk=0;
float current_blynk=0;
float power_blynk=0;
float energy_blynk=0;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "8911113ba5cf493390b4624e28cd7f4d";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Mach_Dien_Tu";
char pass[] = "Hshopvn123";


unsigned long lastMillis = 0;


///http://pdacontrolen.com/meter-pzem-004-esp8266-platform-iot-blynk-app/


void setup()
{
  //No  Debug console      
 /// Serial.begin(9600);              // Note : Do not use Serial0 port, for serial debugging!

   pzem.setAddress(ip);
  Blynk.begin(auth, ssid, pass);
 
}

void loop()
{
  Blynk.run();
  
/// Read meter PZEM 
    float v = pzem.voltage(ip);          
   if(v >= 0.0){   voltage_blynk =v; } //V
  
    float i = pzem.current(ip);
    if(i >= 0.001){ current_blynk=i;    }  //A                                                                                                                      
    
    float p = pzem.power(ip);
    if(p >= 0.0){power_blynk=p;       } //kW
    
    float e = pzem.energy(ip);          
    if(e >= 0.0){  energy_blynk =e;  } ///kWh
delay(1000);

      //Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
          if (millis() - lastMillis > 10000) {
            lastMillis = millis();
            
            Blynk.virtualWrite(V1, voltage_blynk);
            Blynk.virtualWrite(V2, current_blynk  );            
            Blynk.virtualWrite(V3, power_blynk);
            Blynk.virtualWrite(V4, energy_blynk  );
            Blynk.virtualWrite(V5, lastMillis  );      

          }         
  
}
