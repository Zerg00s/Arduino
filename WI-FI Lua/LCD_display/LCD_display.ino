// SAMPLE FOR ARDUINO NANO AND LUA_WIFI
// connect the display to 
// NANO: address for small Kuman display: 0x3C
// SCL to A4 
// SDA to A5 
//
// LUA: address: address for small Kuman display 0x3C
// SCL TO D1
// SDA TO D2
// http://www.instructables.com/id/Arduino-Interrupts/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
//// reset pin not used on 4-pin OLED module
//Adafruit_SSD1306 display(OLED_RESET);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

//#if (SSD1306_LCDHEIGHT != 16)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif


void setup()   {                
  Serial.begin(9600);  
}

void show_stuff(){
  Serial.println("Showing stuff...");
  Adafruit_SSD1306 display(4);  // -1 = no reset pin
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  displayText("Greetings");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("Greetings");
  display.display();
  delay(1);
 
  display.startscrollright(0x00, 0x0F);
  delay(500);
  display.stopscroll();
  delay(500);
  display.startscrollleft(0x00, 0x0F);
  delay(500);
  display.stopscroll();
  //delay(1000);    
  //display.startscrolldiagright(0x00, 0x07);
  //delay(2000);
  //display.startscrolldiagleft(0x00, 0x07);
  //delay(2000);
  //display.stopscroll();
  
  display.clearDisplay();
}

void loop() {
   Serial.println("Loop begin");
   show_stuff();  
}

void displayText(String text) {
  
}

 
