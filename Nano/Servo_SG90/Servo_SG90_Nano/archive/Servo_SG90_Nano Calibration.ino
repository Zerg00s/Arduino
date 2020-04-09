#include <Servo.h>

/* 
 *  Full Tutorial 
 *  https://steemit.com/utopian-io/@jbeguna04/simulating-servo-motors-in-arduino-nano-step-by-step-tutorial-how-to-program-arduino-nano-for-servo-motor
 *  Servo can rotate approximately 180 degrees (90 in each direction)
 */


Servo servo_pin_2;
void setup()
{
  /* https://www.arduino.cc/en/Reference/ServoAttach */
  // servo_pin_2.attach(2,530,2600);
  servo_pin_2.attach(2);
}
void loop()
{ 
  servo_pin_2.writeMicroseconds(530);
  delay( 1000 );
  servo_pin_2.writeMicroseconds(1500);
  delay( 1000 );
  servo_pin_2.writeMicroseconds(2400);
  delay( 1000 );
  /*
  delay( 500 );
  servo_pin_2.write( -30 );
  delay( 500 );
  servo_pin_2.write( 0 );
  delay( 500 );
  servo_pin_2.write( 30 );
  delay( 500 );
  servo_pin_2.write( 60 );
  delay( 500 );
  servo_pin_2.write( 90 );
  delay( 1000 );
    */
}
