// NodeMCU wires setup:
// GROUND TO GROUND
// VCC to VCC
// SCL to D1
// SDA TO D2

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;

void setup() {
    USE_SERIAL.begin(9600);
   // USE_SERIAL.setDebugOutput(true);
    USE_SERIAL.println();
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("Denis-wifi", "welcomehome");
}

String getQuote(String  baseCurrency, String  targetCurrency)
{
  HTTPClient http;
  USE_SERIAL.print("[HTTP] begin...\n");
  String currencyRateEndPoint = "https://api.fixer.io/latest?base=" + baseCurrency + "&symbols=" + targetCurrency;
  http.begin(currencyRateEndPoint, "88 12 02 70 66 a8 f4 cd 4d 36 c5 fc ba 24 76 17 a4 2c 4f 8d"); //HTTPS Ceriticate thumbnail 
  USE_SERIAL.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  if(httpCode > 0) { 
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
  
      // file found at server
      if(httpCode == HTTP_CODE_OK) {
          USE_SERIAL.println("-------------");
          String payload = http.getString();
          StaticJsonBuffer<200> jsonBuffer;
          JsonObject& root = jsonBuffer.parseObject(payload);
          USE_SERIAL.println(payload);
          String base = root["base"];
          USE_SERIAL.println(base + " to " + targetCurrency + ":");
          String targetToBaseRate = root["rates"][targetCurrency];
          USE_SERIAL.println(targetToBaseRate);
          return targetToBaseRate;
      }
  } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
}

void loop() {
    // wait for WiFi connection
    DisplayGreeting(" Connecting to ","Wi-fi...");
    if((WiFiMulti.run() == WL_CONNECTED)) {
      USE_SERIAL.println("Connected to wi-fi!");
      String rate = getQuote("USD", "CAD");
      DisplayGreeting("    USD to CAD"," " + rate);
      delay(4000);
      rate = getQuote("USD", "RUB");
      DisplayGreeting("    USD to RUB"," " + rate);
      delay(4000);
      rate = getQuote("CAD", "RUB");
      DisplayGreeting("    CAD to RUB"," " + rate);
      delay(4000);  
      rate = getQuote("EUR", "USD");    
      DisplayGreeting("    EUR to USD"," " + rate);
    }

    delay(10000);
}

void DisplayGreeting(String line1, String line2){
  Serial.println("Showing stuff...");
  Adafruit_SSD1306 display(-1); // NodeMCU | !IMPORTANT
  // Adafruit_SSD1306 display(4); // NANO
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println(line1);

  display.setTextSize(2);
  display.setCursor(15,10);
  display.println(line2);
  
  display.display();
  delay(1); 
}

