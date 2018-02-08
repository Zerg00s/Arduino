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
#include <string.h>
#include <ArduinoJson.h>
#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;

char* ssid2 = "Denis-wifi";
char* password2 = "welcomehome";
char* ssid1 = "PAI-Mobile";
char* password1 = "Suite 500";


void setup() {
    USE_SERIAL.begin(9600);

    bool connected = ConnectToWifi(ssid1, password1, 5000);
    if (!connected){      
       connected = ConnectToWifi(ssid2, password2, 5000);
    }
       
    if (!connected) {
      Serial.print("Going DeepSleep");
      DisplayMessage("Going" , "DeepSleep", "100 sec");
      ESP.deepSleep(100000); // go deepsleep for 100 sec and try all over again
    }
}

bool ConnectToWifi(char* ssid, char* password, int timeout){
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    DisplayMessage("Connecting to", ssid);    
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
    return true;}
String getCryptoQuote(String  baseCurrency, String  targetCurrencies)
{
  HTTPClient http;
  USE_SERIAL.print("[HTTP] begin...\n");
  String currencyRateEndPoint = "https://min-api.cryptocompare.com/data/price?fsym=" + baseCurrency + "&tsyms=" + targetCurrencies;
  http.begin(currencyRateEndPoint, "61 de e9 ff bb 6b ad aa e4 9a 38 95 dc ec 74 2c 61 4b 7d 07"); //HTTPS Ceriticate thumbnail 
  
  USE_SERIAL.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  if(httpCode > 0) { 
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
  
      // file found at server
      if(httpCode == HTTP_CODE_OK) {
          USE_SERIAL.println("-------------");
          String payload = http.getString();
          return payload;

      }
  } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
}

void loop() {   
    DisplayMessage(" Calling ","API...");
    if((WiFiMulti.run() == WL_CONNECTED)) {     
      String rates = getCryptoQuote("CAD", "KCS,ETH,NEO,DENT,DRGN,PRL,DENT");      
      
      float KCSPrice = GetCryptoPrice(rates, "KCS", 51.8);
      float NEOPrice = GetCryptoPrice(rates, "NEO", 5.96); 
      float ETHPrice = GetCryptoPrice(rates, "ETH", 0.609); 
      float DRGNPrice = GetCryptoPrice(rates, "DRGN", 134.64);     
      float PRLPrice = GetCryptoPrice(rates, "PRL", 472.18);
      float DENTPrice = GetCryptoPrice(rates, "DENT", 6488); 
      float TotalPackage = KCSPrice +NEOPrice+ ETHPrice + DRGNPrice + PRLPrice + DENTPrice;
      String priceAsString = floatToString(TotalPackage); 
      DisplayMessage("Total price",priceAsString);
      delay(10000);
      
      DisplayPackagePrice("KCS", KCSPrice, 2000);     
      DisplayPackagePrice("NEO", NEOPrice, 2000);
      DisplayPackagePrice("ETH", ETHPrice, 2000);
      DisplayPackagePrice("DRGN", DRGNPrice, 2000);
      DisplayPackagePrice("PRL", PRLPrice, 2000); 
      DisplayPackagePrice("DENT", DENTPrice, 2000);   

      DisplayMessage("Total price", priceAsString);
     }

    delay(10000);
}

void DisplayPackagePrice(String symbol, float price,  int delayDuration)
{
  String priceAsString = floatToString(price); 
  USE_SERIAL.println(symbol + " package price: " + priceAsString );   
  DisplayMessage(symbol + " package: ",  priceAsString);
  delay(delayDuration);
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
  Serial.println("Showing stuff... " + line1 +" " + line2);
  Adafruit_SSD1306 display(-1); // NodeMCU | !IMPORTANT
  // Adafruit_SSD1306 display(4); // NANO
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println(line1);

  if(line2.length() < 8){
    display.setTextSize(2);  
  }else{
     display.setTextSize(1);  
  }  
  display.setCursor(15,10);
  display.println(line2);

  display.setTextSize(1);  
  display.setCursor(10,20);
  display.println(line3);
  
  display.display();
  delay(1); 
}



