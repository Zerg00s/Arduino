/***********************************************
  name:Infrared-Receiver
  function:press the Power key of a remote control,
  and both the LED attached and that connected to pin 13 on the SunFounder Uno board will light up.
  Then press any other key, and the LEDs will go out.
**********************************************/
//Email: support@sunfounder.com
//Website: www.sunfounder.com

#include <IRremote.h>

// Display dependencies:
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Kuman 0.96 inch I2c Serial LCD Display:
// SDA - A4
// SCL - A5

const int irReceiverPin = 2; //ir receiver module attach to pin2
// D2 pin
const int ledPin = 13; //pin 13 built-in led

IRrecv irrecv(irReceiverPin); //Creates a variable of type IRrecv
decode_results results;

void setup()
{
  pinMode(ledPin, OUTPUT); //set ledpin as OUTPUT
  Serial.begin(9600); //initialize serial monitor
  irrecv.enableIRIn(); //enable ir receiver module
}

void loop()
{
  if (irrecv.decode(&results)) //if the ir receiver module receiver data
  {
    Serial.print("irCode: "); //print"irCode: "
    Serial.print(results.value); //print the value in hexdecimal
    Serial.print(", bits: "); //print" , bits: "
    Serial.println(results.bits); //print the bits
    
    if (results.value == 16753245) { // Power button
      ShowCard("Power");
    }

    else if (results.value == 16738455) { // 0
      ShowCard("Hi! :)");
      
    }

    else if (results.value == 16724175) { // 1
      ShowCard("You are cute! :)");
    }

    else if (results.value == 16718055) { // 2
      ShowCard("What's up?");
    }

    else if (results.value == 16743045) { // 3
      ShowCard("Get off!");
    }

    else if (results.value == 16716015) { // 4
      ShowCard("Cool car");
    }

    else if (results.value == 16726215) { // 5
      ShowCard("Give me your number");
    }

    else if (results.value == 16734885) { // 6
      ShowCard("Weather is good");
    }

//    else if (results.value == 16728765) { // 7
//      ShowCard("Shit happens");
//    }

//    else if (results.value == 16730805) { // 8
//      ShowCard("Dang!");
//    }

//    else if (results.value == 16732845) { // 9
//      ShowCard("Damn, girl!");
//    }
//    else {
//      ShowCard((String)results.value);
//    }
    delay(100);
    irrecv.resume(); // Receive the next value

  }
 delay(100);
}


void ShowCard(String card) {
  //Adafruit_SSD1306 display(-1); // NodeMCU | !IMPORTANT
  Adafruit_SSD1306 display(4); // NANO
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.println(card);

  // Output the index of the deck as a debug message:
  display.setTextSize(1);
  display.setCursor(116, 25); //Width=128(real = 116), Height=64(real=25)
  //display.print(CurrentDeck);

  display.display();
  delay(1);
}


