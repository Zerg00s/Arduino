void setup() {
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);//D3 same as GPIO0
  pinMode(2, INPUT_PULLUP); //D4  same as GPIO2
  pinMode(14, INPUT_PULLUP); //D5 same as GPIO14
}

void loop() {
  int sensorVal0 = digitalRead(0);
  Serial.println(sensorVal0);
  
  int sensorVal2 = digitalRead(2);
  Serial.println(sensorVal2);

  int sensorVal14 = digitalRead(14);
  Serial.println(sensorVal14);
}
