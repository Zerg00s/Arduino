// ADVANED EXAMPLE OF THE PORTFOLIO
// NodeMCU wires setup:
// GROUND TO GROUND
// VCC to VCC
// SCL to D1
// SDA TO D2

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>
//#include <ESP8266WiFiMulti.h>

IPAddress myIP;
char* ssid1 = "Denis-wifi";
char* password1 = "welcomehome";
char* ssid2 = "PAI-Mobile";
char* password2 = "Suite 500";
//char* ssid1 = "Site 3";
//char* password1 = "makestuff";

String totalPriceAsString = "";

void setup() {
  Serial.begin(9600);
  delay(100); // wait for Serial to initialize properly.
 
  Serial.println("STARTING");
  SPIFFS.begin();  
  loadConfig();
  
  
  if(!ConnectToWifi()){
    StartWifiAP();
    StartWebServer(); //TODO: Add TimeOut for the web server. Pass time in seconds to indicate when the server should stop.
  }

  // TODO: Physical button for StartWebServer()
}

bool ConnectToWifi(){
    bool connected = ConnectToWifi(ssid1, password1, 5000);
  if (!connected) {
    connected = ConnectToWifi(ssid2, password2, 5000);
  }

  if (!connected) {
    Serial.print("Failed to connect");
    DisplayMessage("Failed to connect" , "Sleeping for", "100 seconds...");
    //ESP.deepSleep(100000); // go deepsleep for 100 sec and try all over again
    return false;
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  DisplayMessage("IP", WiFi.localIP().toString());
  

  return true;
  
}

bool ConnectToWifi(char* ssid, char* password, int timeout) {
  Serial.println();
  Serial.print("Connecting");
  Serial.println(ssid);
  DisplayMessage("Connecting", ssid);
  //WiFi.setOutputPower(0); 
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 

  int mseconds = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    mseconds += 200;
    if (mseconds > timeout) {
      return false;
    }
  }
  return true;
}

String getCryptoQuote(String  baseCurrency, String  targetCurrencies){
  DisplayMessage("Calling REST API", "https://min-api", ".cryptocompare");
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  String currencyRateEndPoint = "https://min-api.cryptocompare.com/data/price?fsym=" + baseCurrency + "&tsyms=" + targetCurrencies;
  http.begin(currencyRateEndPoint, "61 de e9 ff bb 6b ad aa e4 9a 38 95 dc ec 74 2c 61 4b 7d 07"); //HTTPS Ceriticate thumbnail

  Serial.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      Serial.println("-------------");
      String payload = http.getString();
      return payload;

    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() {
  String rates = getCryptoQuote("CAD", "KCS,ETH,NEO,DENT,DRGN,PRL,DENT");
  float KCSPrice = GetCryptoPrice(rates, "KCS", 51.8);
  float NEOPrice = GetCryptoPrice(rates, "NEO", 5.96);
  float ETHPrice = GetCryptoPrice(rates, "ETH", 0.609);
  float DRGNPrice = GetCryptoPrice(rates, "DRGN", 134.64);
  float PRLPrice = GetCryptoPrice(rates, "PRL", 472.18);
  float DENTPrice = GetCryptoPrice(rates, "DENT", 6488);
  float TotalPackage = KCSPrice + NEOPrice + ETHPrice + DRGNPrice + PRLPrice + DENTPrice;
  totalPriceAsString = floatToString(TotalPackage);
  DisplayMessage("Total", "$" + totalPriceAsString);
  delay(10000);

  DisplayPackagePrice("KCS", KCSPrice, 2000);
  DisplayPackagePrice("NEO", NEOPrice, 2000);
  DisplayPackagePrice("ETH", ETHPrice, 2000);
  DisplayPackagePrice("DRGN", DRGNPrice, 2000);
  DisplayPackagePrice("PRL", PRLPrice, 2000);
  DisplayPackagePrice("DENT", DENTPrice, 2000);

  DisplayMessage("Total", "$" + totalPriceAsString);

  delay(10000);
}

void DisplayPackagePrice(String symbol, float price,  int delayDuration)
{
  String priceAsString = floatToString(price);
  Serial.println(symbol + " package price: " + priceAsString );
  DisplayMessage(symbol + " pack",  "$" + priceAsString, "$" + totalPriceAsString);
  delay(delayDuration);
}

float GetCryptoPrice(String rates, String symbol, float amount)
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(rates);
  String symbolRate = root[symbol];
  Serial.println("Symbol: " + symbol);
  Serial.println("SymbolRate: " + symbolRate);
  if (symbolRate.toFloat() == 0) {
    return 1;
  }
  else {
    float packagePrice =  amount * (1 / symbolRate.toFloat());
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


void DisplayMessage(String line1) {
  DisplayMessage(line1, "", "");
}

void DisplayMessage(String line1, String line2) {
  DisplayMessage(line1, line2, "");
}
void DisplayMessage(String line1, String line2, String line3) {
  //Width=128, Height=64
  Serial.println("Showing stuff... " + line1 + " " + line2);
  Adafruit_SSD1306 display(-1); // NodeMCU | !IMPORTANT
  // Adafruit_SSD1306 display(4); // NANO
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if (line1.length() > 10) {
    display.setTextSize(1);
  } else {
    display.setTextSize(2);
  }

  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.println(line1);

  if (line2.length() > 10) {
    display.setTextSize(1);
  } else {
    display.setTextSize(2);
  }
  display.setCursor(0, 20);
  display.println(line2);

  if (line3.length() > 10) {
    display.setTextSize(1);
  } else {
    display.setTextSize(2);
  }

  display.setCursor(0, 40);
  display.println(line3);

  display.display();
  delay(1);
}



