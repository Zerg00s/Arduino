#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

// Connect NANO::
// SDA - A4
// SCL - A5
volatile byte interruptPin = 2;
// connect the display to A4 and A5:
// http://www.instructables.com/id/Arduino-Interrupts/

const char longText[] PROGMEM = {"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque ante nibh, sodales eget pharetra quis, tempor id lacus.\r\n Cras a vulputate magna.\r\nInteger suscipit lacus ligula, non blandit nulla mattis sed.\r\n Mauris varius scelerisque ipsum.\r\n Quisque rhoncus, felis sit amet pretium dignissim,\r\n\0"};

void setup()   {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT);

  DisplayMessage("hello", "World");
  printMessage((char*)pgm_read_word(&(longText)));    
}

volatile byte pressed = false;

void button_pressed() {
  if (pressed == true) {
    return;
  }
  Serial.println('pressed');
  pressed = true;
 
}

void loop() {
  byte val = digitalRead(interruptPin);
  if (val) {
    Serial.println("woo hoo!");
    button_pressed();
  }
}
void DisplayMessage(String line1, String line2, String line3) {
  Serial.println("Showing stuff... " + line1 + " " + line2);
  //Adafruit_SSD1306 display(-1); // NodeMCU | !IMPORTANT
  Adafruit_SSD1306 display(4); // NANO
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.clearDisplay();
  display.println(line1);

  if (line2.length() < 8 & line3.length() == 0) {
    display.setTextSize(2);
  } else {
    display.setTextSize(1);
  }
  display.setCursor(15, 10);
  display.println(line2);

  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println(line3);

  display.display();
  delay(1);
}


void DisplayMessage(String line1) {
  DisplayMessage(line1, "", "");
}

void DisplayMessage(String line1, String line2) {
  DisplayMessage(line1, line2, "");
}



void printMessage(char * message) {
  int counter = 0;
  int myChar=0;
  
  do {
    myChar =  pgm_read_byte_near(message + counter); 
    if (myChar != 0){
      Serial.print((char) myChar);
    }
    counter++;
  } 
  while (myChar != 0);
}
