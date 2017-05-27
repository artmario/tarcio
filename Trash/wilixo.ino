/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "images.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

}

///teste afas fa
void loop() {
  
  // miniature bitmap display
  display.drawBitmap(0, 0, wilixo, 128, 64, 1);
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  // miniature bitmap display
  display.drawBitmap(0, 0, wilixo1, 128, 64, 1);
  display.display();
  // Clear the buffer.
  display.clearDisplay();
  // miniature bitmap display
  display.drawBitmap(0, 0, wilixo2, 128, 64, 1);
  display.display();
  // Clear the buffer.
  display.clearDisplay();
  // miniature bitmap display
  display.drawBitmap(0, 0, wilixo1, 128, 64, 1);
  display.display();
  // Clear the buffer.
  display.clearDisplay();
}
