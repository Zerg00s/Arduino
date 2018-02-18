// NodeMCU wires setup:
// GROUND TO GROUND
// VCC to VCC
// SCL to D1
// SDA TO D2

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>

#define USE_SERIAL Serial


char* ssid2 = "Denis-wifi";
char* password2 = "welcomehome";
//char* ssid1 = "PAI-Mobile";
//char* password1 = "Suite 500";

char* ssid1 = "Site 3";
char* password1 = "makestuff";

String totalPriceAsString = "";
long rssi;

void setup() {
    USE_SERIAL.begin(9600);
    

    

    bool connected = ConnectToWifi(ssid1, password1, 5000);
    if (!connected){      
       connected = ConnectToWifi(ssid2, password2, 5000);
    }
       
    if (!connected) {
      Serial.print("Going DeepSleep");
      DisplayMessage("Failed to connect" , "Sleeping for", "100 seconds...");
      ESP.deepSleep(100000); // go deepsleep for 100 sec and try all over again
    }
}

bool ConnectToWifi(char* ssid, char* password, int timeout){
    Serial.println();
    Serial.print("Connecting");
    Serial.println(ssid);
    DisplayMessage("Connecting", ssid);    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);  
    
    int mseconds = 0;
    while (WiFi.status() != WL_CONNECTED){
      delay(200);
      mseconds+=200;
      if (mseconds>timeout){
        return false;
      }      
    }
  return true;
}
    
void LogToIoTHub(String  readingValue)
{
  DisplayMessage("Calling REST API", "https://api.thingspeak.com");  
  HTTPClient http;
  USE_SERIAL.print("[HTTP] begin...\n");
  //String currencyRateEndPoint = "http://api.thingspeak.com/update?api_key=SBJMODH0V303YHKE&field1=" + readingValue;
  String currencyRateEndPoint = "https://api.thingspeak.com/update?api_key=SBJMODH0V303YHKE&field1=" + readingValue;
  http.begin(currencyRateEndPoint,"78 60 18 44 81 35 bf df 77 84 d4 0a 22 0d 9b 4e 6c dc 57 2c"); 
  
  USE_SERIAL.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  if(httpCode > 0) { 
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
  
      // file found at server
      if(httpCode == HTTP_CODE_OK) {
          USE_SERIAL.println("-------------");
      }
  } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
}

void loop() {   

    rssi = WiFi.RSSI();  // eg. -63
    
    LogToIoTHub(String(rssi));
    DisplayMessage("Signal",String(rssi));
    delay(16000);
}


float GetCryptoPrice(String rates, String symbol, float amount)
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(rates);
  String symbolRate = root[symbol];
  Serial.println("Symbol: " + symbol);
  Serial.println("SymbolRate: "+ symbolRate);
  if (symbolRate.toFloat() == 0){
    return 1;
  }
  else{
    float packagePrice =  amount * (1/symbolRate.toFloat());
    Serial.println(packagePrice);
    return packagePrice;  
  }
}


String floatToString(float number)
{
   char result[10];
   Serial.println(number);
   dtostrf(number, 6, 2, result); 
   return result;
}
    

void DisplayMessage(String line1){
  DisplayMessage(line1, "", "");
}

void DisplayMessage(String line1, String line2){
 DisplayMessage(line1, line2, "");
}
void DisplayMessage(String line1, String line2, String line3){
  //Width=128, Height=64
  Serial.println("Showing stuff... " + line1 +" " + line2);
  Adafruit_SSD1306 display(-1); // NodeMCU | !IMPORTANT
  // Adafruit_SSD1306 display(4); // NANO
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  if(line1.length() > 10) {
    display.setTextSize(1);  
  }else{
     display.setTextSize(2);  
  }

  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println(line1);

  if(line2.length() > 10) {
    display.setTextSize(1);  
  }else{
     display.setTextSize(2);  
  }
  display.setCursor(0,20);
  display.println(line2);

  if(line3.length() > 10) {
    display.setTextSize(1);  
  }else{
     display.setTextSize(2);  
  }
  
  display.setCursor(0,40);
  display.println(line3);
  
  display.display();
  delay(1); 
}



