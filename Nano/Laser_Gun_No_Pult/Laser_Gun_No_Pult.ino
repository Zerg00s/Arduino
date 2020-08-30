#include <Servo.h>

/*
    Full Tutorial
    https://steemit.com/utopian-io/@jbeguna04/simulating-servo-motors-in-arduino-nano-step-by-step-tutorial-how-to-program-arduino-nano-for-servo-motor
    Servo can rotate approximately 180 degrees (90 degrees in each direction)
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

void rotateBothServos(int newTopAngle, int newBottomAngle, int delayMs, int speed)
{
  int steps = 10;
  float topStepSize = (topServoAngle - newTopAngle) / steps;
  float bottomStepSize = (bottomServoAngle - newBottomAngle) / steps;

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
  for (int i = 0; i < steps; i++)
  {
    tempTopServoAngle -= topStepSize;
    tempBottomServoAngle -= bottomStepSize;
    Serial.println(tempTopServoAngle);
    Serial.println(tempBottomServoAngle);
    servo_top_pin_2.write(round(tempTopServoAngle) );
    servo_bottom_pin_3.write(round(tempBottomServoAngle) );
    delay(100/speed);
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


void rotateServosRandomly(int delay, int speed) {
  int topServoAngle = random(60, 120);
  int bottomServoAngle = random(0, 180);
  Serial.println("rotateBothServos");
  rotateBothServos(topServoAngle, bottomServoAngle, delay, speed);
}

void loop(){
  int behaviourID = random(1,4);
  int delay = 0;
  int repetitions = 0;
  Serial.println(behaviourID);
  switch (behaviourID) {
  case 1:
    // rapid movements    
    repetitions = random(10, 150);
    for(int i= 0; i < repetitions; i++){ 
      delay = random(1, 300);
      rotateServosRandomly(delay, 100);
    }
  break;
  case 2:
    // fast movements    
    repetitions = random(7, 50);
    for(int i= 0; i < repetitions; i++){ 
      delay = random(300, 1000);
      rotateServosRandomly(delay, 2);
    }
    break;
  case 3:
    // normal movements    
    repetitions = random(5, 15);
    for(int i= 0; i < repetitions; i++){ 
      delay = random(300, 2500);
      rotateServosRandomly(delay, 1);
    }
  break;
  case 4:
    // Suudden Jerk movements
    repetitions = random(5, 20);
    for(int i= 0; i < repetitions; i++){ 
      delay = random(1500, 4500);
      rotateServosRandomly(delay, 100);
    }
  break;
  default:
    
  break;
}

  
  
  
}
