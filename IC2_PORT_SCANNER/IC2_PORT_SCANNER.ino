#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
void setup()
{
  Wire.begin(); 
  Serial.begin(9600);
  while (!Serial);           
  Serial.println("\nI2C Scanner");
}

void loop()
{
  byte error, address;
  int nDevices; 
  Serial.println("Scanning..."); 
  nDevices = 0;
  for(address = 1; address < 61; address++ ) // You might want to increase it to 120!
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else{
    Serial.println("done\n");
    DisplayGreeting();
  }
  delay(1000);
}

void DisplayGreeting(){
  Serial.println("Showing stuff...");
  Adafruit_SSD1306 display(-1); // NodeMCU | !IMPORTANT
  // Adafruit_SSD1306 display(4); // NANO
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("Greetings");
  display.display();
  delay(1); 
}
