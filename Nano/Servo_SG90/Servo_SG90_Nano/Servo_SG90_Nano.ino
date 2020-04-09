#include <Servo.h>

/*
    Full Tutorial
    https://steemit.com/utopian-io/@jbeguna04/simulating-servo-motors-in-arduino-nano-step-by-step-tutorial-how-to-program-arduino-nano-for-servo-motor
    Servo can rotate approximately 180 degrees (90 in each direction)
*/
Servo servo_top_pin_2;
Servo servo_bottom_pin_3;
void setup()
{
  /* https://www.arduino.cc/en/Reference/ServoAttach */
  servo_top_pin_2.attach(2,530,2600);
  servo_bottom_pin_3.attach(3,530,2600);
  //servo_pin_2.attach(2);
}
void loop()
{
  delay( 500 );
  servo_bottom_pin_3.write( -90 ); // Rotate bottom servo clockwise 90 degrees
  servo_top_pin_2.write( -90 ); // Rotate servo clockwise 90 degrees
  delay( 500 );
  servo_bottom_pin_3.write( 110 ); // Rotate bottom servo counterclockwise 90 degrees
  servo_top_pin_2.write( 110 ); // Rotate top servo counterclockwise 90 degrees
  delay( 1000 );
}
