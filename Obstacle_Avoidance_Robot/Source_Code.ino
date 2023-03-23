#include <Servo.h> //Servo motor library. This is standard library

//our L298N control pins
//in3  in4
const int LeftMotorForward = 4;
const int LeftMotorBackward = 5; 
//in1  in2
const int RightMotorForward = 6;   
const int RightMotorBackward = 7;


//sensor pins
#define triggerPin A0 //analog input 0 //TX// Green
#define echoPin A1 //analog input 1 //RX// Orange

float distance = 0;

Servo servo_motor; //our servo name

void setup(){
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  servo_motor.attach(10); //our servo pin
  servo_motor.write(76);

  //sensor pins
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  distance = get_distance();
  //delay(100);
  //distance = get_distance();
} 
void loop(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 35){
    moveStop();
    delay(200);
    distanceRight = lookRight();
    delay(200);
    distanceLeft = lookLeft();
    delay(200);
    if (distanceRight <= 35){                   
      if (distanceLeft <= 35)                   
      {                                         
        //rotate 180                            
        turnLeft();
        delay(500);
        moveStop();
      }
      else
      {
        turnLeft();
        moveStop();
      }
    }
    else{
      turnRight();
      moveStop();
    }
  }
  else{
    moveForward();
  }
  distance = get_distance();
}

int lookRight(){
  servo_motor.write(146);
  delay(400);
  int distance = get_distance();
  servo_motor.write(76);
  return distance;
} 

int lookLeft(){
  servo_motor.write(6);
  delay(400);
  int distance = get_distance();
  servo_motor.write(76);
  return distance;
} 

void moveStop(){
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
} 
void moveForward(){
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
 
void moveBackward(){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
} 
void turnRight(){
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(400);
} 
void turnLeft(){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  delay(400);
}
float get_distance(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  //clearing the trigger
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // capturing the time duration for sound wave to travel in microseconds
  unsigned long duration = pulseIn(echoPin, HIGH);
  distance = 0.01715 * duration;
  return distance;
  delay(5);
}
