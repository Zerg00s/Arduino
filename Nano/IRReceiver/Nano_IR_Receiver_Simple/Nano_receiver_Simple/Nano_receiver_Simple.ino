#include <IRremote.h>

const int irReceiverPin = 4; //ir receiver module attach to pin4 D4

IRrecv irrecv(irReceiverPin); //Creates a variable of type IRrecv
decode_results results;

void setup()
{
  irrecv.enableIRIn(); //enable ir receiver module
  Serial.begin(9600);      // open the serial port at 9600 bps:    
  Serial.print("SETUP SUCCESSFUL"); //print"irCode: "
}

void loop()
{
  if (irrecv.decode(&results)) //if the ir receiver module receives data
  {
    Serial.print("irCode: "); //print"irCode: "
    Serial.print(results.value); //print the value in hexdecimal
    Serial.print(", bits: "); //print" , bits: "
    Serial.println(results.bits); //print the bits
    
    if (results.value == 16753245) { // Power button
      
    }

    else if (results.value == 16738455) { // 0
      
      
    }

    else if (results.value == 16724175) { // 1
      
    }

    else if (results.value == 16718055) { // 2
      
    }

    else if (results.value == 16743045) { // 3
      
    }

    else if (results.value == 16716015) { // 4
      
    }

    else if (results.value == 16726215) { // 5
      
    }

    else if (results.value == 16734885) { // 6
      
    }

    else if (results.value == 16728765) { // 7
      
    }

    else if (results.value == 16730805) { // 8
     
    }

    else if (results.value == 16732845) { // 9
     
    }
    else {
     
    }
    delay(100);
    irrecv.resume(); // Receive the next value

  }
 delay(100);
}
