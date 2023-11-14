/*
for Keyestudio Turtle Robot V3.1 :

tests both drive motors, servo, and ultrasonic sensor (sent to serial monitor)
*/

#include <Servo.h>
Servo servo;

#define ultrasonicTrigPin 12
#define ultrasonicEchoPin 13
#define ultrasonicServoPin A3

#define motorA_direction 9     //direction control pin of A motor / L
#define motorA_PWM 2   //PWM control pin of A motor
#define motorB_direction 4    //direction control pin of B motor
#define motorB_PWM 5   //PWM control pin of B motor / R

float distance_cm;

void getDistance(){
  digitalWrite(ultrasonicTrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin,LOW);
  duration = pulseIn(ultrasonicEchoPin,HIGH);
  distance_cm = (34/duration)/2; //2*distance = (speed/time)
  Serial.println(distance_cm);
}

void setup(){
  pinMode(ultrasonicTrigPin,OUTPUT);
  pinMode(ultrasonicEchoPin,OUTPUT);
  pinMode(motorA_direction,OUTPUT);
  pinMode(motorA_PWM,OUTPUT);
  pinMode(motorB_direction,OUTPUT);
  pinMode(motorB_PWM,OUTPUT);
  pinMode(ultrasonicServoPin,OUTPUT);
  servo.attach(ultrasonicServoPin);

  Serial.begin(9600);
}
void loop(){
  //servo.write(150);
  digitalWrite(motorA_direction,HIGH);
  analogWrite(motorA_PWM,220);
  digitalWrite(motorB_direction,HIGH);
  analogWrite(motorB_PWM,220);

  getDistance();
}
