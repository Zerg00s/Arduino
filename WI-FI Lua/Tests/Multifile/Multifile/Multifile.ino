#include "Logger.h"
#include "FS.h"

void setup() {  
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Logger g("Denis");
  String name = g.Name;
  Serial.print(name);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  Serial.print("test");
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
