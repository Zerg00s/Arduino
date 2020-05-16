#include <Servo.h>
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

void setup()
{
  Serial.begin(9600);
  resetServos();
}

void resetServos()
{
  servo_top_pin_2.attach(2, 530, 2600);
  servo_bottom_pin_3.attach(3, 530, 2600);

  servo_top_pin_2.write(90);
  servo_bottom_pin_3.write(90);

  delay(500);
  servo_top_pin_2.detach();
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
    servo_top_pin_2.write(round(tempTopServoAngle) );
    servo_bottom_pin_3.write(round(tempBottomServoAngle) );
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


void rotateServosRandomly(int delay) {
  int topServoAngle = random(60, 120);
  int bottomServoAngle = random(0, 180);
  Serial.println("rotateBothServos");
  rotateBothServos(topServoAngle, bottomServoAngle, delay);
}

void loop()
{
  int delay = random(350, 2500);
  rotateServosRandomly(delay);
}
