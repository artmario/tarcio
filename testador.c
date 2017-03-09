/* 
* Autor: Larbaco and Artmario
* Battery Capacity Checker
* Uses adafruit ADS1115
* Uses 0.8 Ohm power resister as shunt - Load can be any suitable resister or lamp
* 
* 
* Required Library - Adafruit_ADS1015.h - https://github.com/soligen2010/Adafruit_ADS1X15
*/
#include <Adafruit_ADS1015.h>
#include "U8g2lib.h"
#include "images.h"
#include <stdlib.h>

Adafruit_ADS1115 ads(0x48);


U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 10, /* data=*/ 11, /* reset=*/ 8);

int interval = 5000;  	      //Interval (ms) between measurements 
float mAh = 0.0;  		      // Battery Capacity
float Rshunt = 0.8;  	      // In Ohms - Shunt resistor resistance
float MaxVolt = 4.2; 	      // Full charged
float MinVolt = 3.0; 	      // Full discharged 
float current = 0.0;	         // Current 
float battVolt = 0.0; 	      // Instant Voltage
float shuntVolt = 0.0;	      // Voltage Drop
float extVolt = 0.0;      // extra measure

char buff[10];

boolean finished = false;

unsigned long timestamp = 0;
unsigned long previousMillis = 0;
unsigned long millisPassed = 0;

boolean debug = false;
 
void setup() { 
	Serial.begin(9600);
	ads.begin(); 
   u8g2.begin();
   u8g2.drawXBMP(31,0,64,64,Boobs);
   u8g2.sendBuffer();
	delay(8000);
   Serial.println("Starting");
	Serial.println("Battery Checker v0.8");
	Serial.println("time   battVolt   current     mAh");	
   u8g2.drawXBMP(0,0,128,64,Empty); 
   u8g2.drawFrame(0,0,127,63);
   u8g2.drawXBMP(2,2,17,10,Battery);
   u8g2.drawXBMP(27,2,17,10,Thunder);
   u8g2.sendBuffer();
   u8g2.setFont(u8g2_font_baby_tr);  
}
 
 
void loop() { 
   int16_t adc0;  // ADC raw read fist value
   int16_t adc1;  // ADC raw read second value
   int16_t adc2;  // ADC raw read third value

   adc0 = ads.readADC_SingleEnded(0);
   adc1 = ads.readADC_SingleEnded(1);  
   adc2 = ads.readADC_SingleEnded(2); 
   extVolt = (adc2 * 0.1875)/1000; 
   battVolt = (adc0 * 0.1875)/1000;
   shuntVolt = (adc1 * 0.1875)/1000;
   current = (battVolt - shuntVolt) / Rshunt;
   
   int x;
   u8g2.clearBuffer();
   u8g2.drawFrame(0,0,127,63);
   u8g2.drawXBMP(2,2,17,10,Battery);
   u8g2.drawXBMP(27,2,17,10,Thunder);
   u8g2.sendBuffer();
   x = u8g2.drawStr(2, 23,dtostrf(battVolt,3,2,buff));
   x = u8g2.drawStr(27, 23,dtostrf(current,3,2,buff));
   u8g2.sendBuffer();
   if(debug){
      interval = 100;
      Serial.print("StV ");
      Serial.print(shuntVolt);
      Serial.print("\tBatV ");
      Serial.print(battVolt);
      Serial.print("\tCurr ");
      Serial.print(current);
      Serial.print("\tCap ");
      Serial.print(mAh);
      Serial.print("\tExt ");
      Serial.println(extVolt);
   }
	if(battVolt >= MinVolt && finished == false){		
      millisPassed = millis() - previousMillis;
      previousMillis = millis();      
      if(current > 0){
         timestamp = timestamp + 5;
         mAh = mAh + (current * 1000.0) * (millisPassed / 3600000.0);
         Serial.print(timestamp);
         Serial.print("\t");
         Serial.print(battVolt);
         Serial.print("\t");
         Serial.print(current);
         Serial.print("\t");
         Serial.println(mAh);
      }else{
         Serial.print("Waiting for Charge ");
         Serial.print(battVolt,3);
         Serial.println();
         mAh = 0.0;
      }
      delay(interval);	
	}else{
      if(battVolt < MinVolt && battVolt > 1){
         previousMillis = millis();
         finished = true;
         Serial.print("Finished");
         Serial.print("\t");
         Serial.print(battVolt,3);
         Serial.println();
      }else{
         Serial.print("Waiting for Batery ");
         Serial.print(battVolt,3);
         Serial.println();
         mAh = 0.0;
         millisPassed = 0;
         delay(interval);
      }
	}
  

}