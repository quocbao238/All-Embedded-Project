#ifndef _PROGRAM_GPIO_H_H_
#define _PROGRAM_GPIO_H_H_

#define LED_PIN     D4       //(D3)

#define SENSOR_ONE_PIN    (D1)  //3
#define SENSOR_ONE_TWO    (D2)  //2
#define RX_DF_PLAYER      (D6)  // - NodeMCU 8
#define TX_DF_PLAYER      (D5)  //- NodeMCU 9

#define R_GND 103          //9.70 //10k
#define R_RAW (220 + 1652) // //10k
#define R_CALCULATE (R_GND / (R_GND + R_RAW))
#define V_REF 1.0       //3.31//5.0   //V
#define V_RAW_WARN 3700 // mV
#define inputPin A0

#define sayHello 1
#define sayGoobye 2
#define sayLowPower 3

#define runVoice 1
#define runBat 0

#endif
