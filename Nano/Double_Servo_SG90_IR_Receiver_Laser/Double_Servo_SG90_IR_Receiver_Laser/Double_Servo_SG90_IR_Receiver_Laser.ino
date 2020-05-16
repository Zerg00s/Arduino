#include <Servo.h>
#include <IRremote.h>
/*
    Full Tutorial
    https://steemit.com/utopian-io/@jbeguna04/simulating-servo-motors-in-arduino-nano-step-by-step-tutorial-how-to-program-arduino-nano-for-servo-motor
    Servo can rotate approximately 180 degrees (90 in each direction)
*/
Servo servo_top_pin_2;
Servo servo_bottom_pin_3;

int topServoAngle = 90;
int bottomServoAngle = 90;

const int angleIncrement = 30;

const int irReceiverPin = 4; //ir receiver module attach to pin4 D
IRrecv irrecv(irReceiverPin); //Creates a variable of type IRrecv
decode_results results;


void setup()
{
  irrecv.enableIRIn(); //enable ir receiver module
  Serial.begin(9600);      // open the serial port at 9600 bps:
  Serial.print("SETUP SUCCESSFUL"); //print"irCode: "

  rotateServos(90, 250);
}

void rotateTopServoClockwise()
{

  if (topServoAngle < angleIncrement) {
    return;
  }
  topServoAngle -= angleIncrement;
  rotateTopServo(topServoAngle, 250);
}

void rotateTopServoCounterClockwise()
{

  if (topServoAngle >= 180) {
    return;
  }
  topServoAngle += angleIncrement;
  rotateTopServo(topServoAngle, 250);
}

void rotateBottomServoClockwise()
{

  if (bottomServoAngle < angleIncrement) {
    return;
  }
  bottomServoAngle -= angleIncrement;
  rotateBottomServo(bottomServoAngle, 250);
}

void rotateBottomServoCounterClockwise()
{

  if (bottomServoAngle >= 180) {
    return;
  }
  bottomServoAngle += angleIncrement;
  rotateBottomServo(bottomServoAngle, 250);
}

void rotateTopServo(int angle, int delayMs)
{
  servo_top_pin_2.attach(2, 530, 2600);
  servo_top_pin_2.write(angle ); // Rotate servo clockwise 90 degrees

  topServoAngle = angle;
  delay(delayMs);
  servo_top_pin_2.detach();
}

void rotateBottomServo(int angle, int delayMs)
{
  servo_bottom_pin_3.attach(3, 530, 2600);
  servo_bottom_pin_3.write(angle ); // Rotate servo clockwise 90 degrees

  bottomServoAngle = angle;

  delay(delayMs);
  servo_bottom_pin_3.detach();
}

void rotateBothServos(int newTopAngle, int newBottomAngle, int delayMs)
{
  float topStepSize = (topServoAngle - newTopAngle) / 10;
  float bottomStepSize = (bottomServoAngle - newBottomAngle) / 10;

  Serial.println("------------");
  Serial.println(topServoAngle);
  Serial.println(bottomServoAngle);
  Serial.println("------------");
  Serial.println(newTopAngle);
  Serial.println(newBottomAngle);
  Serial.println("------------");
  Serial.println(topStepSize);
  Serial.println(bottomStepSize);
  Serial.println("------------");

  servo_top_pin_2.attach(2, 530, 2600);
  servo_bottom_pin_3.attach(3, 530, 2600);

  float tempTopServoAngle = topServoAngle;
  float tempBottomServoAngle = bottomServoAngle;
  for (int i = 0; i < 10; i++)
  {
    tempTopServoAngle -= topStepSize;
    tempBottomServoAngle -= bottomStepSize;
    Serial.println(tempTopServoAngle);
    Serial.println(tempBottomServoAngle);
    servo_top_pin_2.write(round(tempTopServoAngle) ); // Rotate servo clockwise 90 degrees
    servo_bottom_pin_3.write(round(tempBottomServoAngle) ); // Rotate servo clockwise 90 degrees
    delay(100);
  }

  topServoAngle = round(tempTopServoAngle);
  bottomServoAngle = round(tempBottomServoAngle);

  Serial.println("---Resulting angles---------");
  Serial.println(topServoAngle);
  Serial.println(bottomServoAngle);

  delay(delayMs);
  servo_top_pin_2.detach();
  servo_bottom_pin_3.detach();
}


void rotateServos(int angle, int delayMs)
{
  /* https://www.arduino.cc/en/Reference/ServoAttach */
  servo_top_pin_2.attach(2, 530, 2600);
  servo_bottom_pin_3.attach(3, 530, 2600);

  Serial.print("rotateServos, angle: ");
  Serial.print(angle); //print the value in hexdecimal

  servo_bottom_pin_3.write(angle ); // Rotate bottom servo clockwise 90 degrees
  servo_top_pin_2.write(angle ); // Rotate servo clockwise 90 degrees

  delay(delayMs);
  servo_top_pin_2.detach();
  servo_bottom_pin_3.detach();
}


void rotateServosRandomly(int delay) {
  int topServoAngle = random(25, 80);
  int bottomServoAngle = random(0, 180);
  Serial.println("rotateBothServos");
  rotateBothServos(topServoAngle, bottomServoAngle, delay); ,,
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
      // rotate left
      rotateServos(0, 500);
    }

    else if (results.value == 16718055) { // 2
      // rotate mid point
      rotateServos(90, 500);
    }
    else if (results.value == 16743045) { // 3
      // rotate right
      rotateServos(180, 500);
    }
    else if (results.value == 16743045) { // 3


    }
    else if (results.value == 16716015) { // 4
      // top servo, counterclockwise
      rotateTopServoCounterClockwise();
    }

    else if (results.value == 16726215) { // 5
      // top servo, clockwise
      rotateTopServoClockwise();
    }

    else if (results.value == 16734885) { // 6

    }

    else if (results.value == 16728765) { // 7
      // Bottom servo, counterclockwise
      rotateBottomServoCounterClockwise();
    }

    else if (results.value == 16730805) { // 8
      // Bottom servo, clockwise
      rotateBottomServoClockwise();
    }

    else if (results.value == 16732845) { // 9

    }

    else if (results.value == 16750695) { // shuffle button
      int delay = 1000;
      // delay = random(350, 2500);
      // rotateServosRandomly(delay);

      for (int i = 0; i < 10000; i++) {
        delay = random(350, 2500);
        rotateServosRandomly(delay);
      }
    }

    delay(100);
    irrecv.resume(); // Receive the next value

  }

}
