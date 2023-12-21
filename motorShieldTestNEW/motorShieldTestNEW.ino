/*
for Keyestudio Turtle Robot V3.1 :

tests both drive motors, servo, 8x8 i2c matrix, and ultrasonic sensor.

requires Adafruit_LEDBackpack and Adafruit_GFX libraries. 
LEDBackpack download : https://drive.google.com/drive/folders/1Fg4iyz1GAwLuM2Pid2zuK3o0rjIoWdiZ
GFX download : https://drive.google.com/drive/folders/1EWay8sCtzs7juY7WWuEg3I3fRTOku-HT
place downloaded library folders in "libraries" sub-folder of Arduino folder

or install using arduino IDE manage libraries tool
*/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();

#include <Servo.h>
Servo servo;

#define ultrasonicTrigPin 12
#define ultrasonicEchoPin 13
#define ultrasonicServoPin A3

#define motorA_direction 9     //direction control pin of A motor / L
#define motorA_PWM 2   //PWM control pin of A motor
#define motorB_direction 4    //direction control pin of B motor
#define motorB_PWM 5   //PWM control pin of B motor / R

//8x8 matrix : A5-SCL, A4-SDA

#define lineFollow_left 6
#define lineFollow_mid 7
#define lineFollow_right 8

float distance_cm;
long duration;

void getDistance(){
  digitalWrite(ultrasonicTrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin,LOW);
  duration = pulseIn(ultrasonicEchoPin,HIGH);
  distance_cm = (34*duration)/2; //2*distance = (speed*time)
  distance_cm /= 1000;
  if(distance_cm>0.0){Serial.println(distance_cm);}
}

void matrix_smile(){
  matrix.displaybuffer[7] = B00000000;
  matrix.displaybuffer[6] = B00100100;
  matrix.displaybuffer[5] = B00100100;
  matrix.displaybuffer[4] = B00100100;
  matrix.displaybuffer[3] = B00000000;
  matrix.displaybuffer[2] = B01000010;
  matrix.displaybuffer[1] = B01111110;
  matrix.displaybuffer[0] = B00000000;
  matrix.writeDisplay();
}

void matrix_clear(){
  matrix.displaybuffer[0] = B00000000;
  matrix.displaybuffer[1] = B00000000;
  matrix.displaybuffer[2] = B00000000;
  matrix.displaybuffer[3] = B00000000;
  matrix.displaybuffer[4] = B00000000;
  matrix.displaybuffer[5] = B00000000;
  matrix.displaybuffer[6] = B00000000;
  matrix.displaybuffer[7] = B00000000;
  matrix.writeDisplay();
}

void matrix_small_circle(){
  matrix.displaybuffer[7] = B00000000;
  matrix.displaybuffer[6] = B00000000;
  matrix.displaybuffer[5] = B00111100;
  matrix.displaybuffer[4] = B00111100;
  matrix.displaybuffer[3] = B00111100;
  matrix.displaybuffer[2] = B00111100;
  matrix.displaybuffer[1] = B00000000;
  matrix.displaybuffer[0] = B00000000;
  matrix.writeDisplay();
}

void matrix_big_circle(){
  matrix.displaybuffer[7] = B00000000;
  matrix.displaybuffer[6] = B01111110;
  matrix.displaybuffer[5] = B01111110;
  matrix.displaybuffer[4] = B01111110;
  matrix.displaybuffer[3] = B01111110;
  matrix.displaybuffer[2] = B01111110;
  matrix.displaybuffer[1] = B01111110;
  matrix.displaybuffer[0] = B00000000;
  matrix.writeDisplay();
}

void setup(){
  pinMode(ultrasonicTrigPin,OUTPUT);
  pinMode(ultrasonicEchoPin,INPUT);
  pinMode(motorA_direction,OUTPUT);
  pinMode(motorA_PWM,OUTPUT);
  pinMode(motorB_direction,OUTPUT);
  pinMode(motorB_PWM,OUTPUT);
  pinMode(ultrasonicServoPin,OUTPUT);
  pinMode(lineFollow_left,INPUT);
  pinMode(lineFollow_mid,INPUT);
  pinMode(lineFollow_right,INPUT);
  servo.attach(ultrasonicServoPin);

  Serial.begin(9600);

  matrix.begin(0x70); //default adress, can check for real adress using i2c scanner program if needed
}
void loop(){
  
  servo.write(150);
  digitalWrite(motorA_direction,HIGH);
  analogWrite(motorA_PWM,220);
  digitalWrite(motorB_direction,HIGH);
  analogWrite(motorB_PWM,220);

  getDistance();
  
  int mid_lineState = digitalRead(lineFollow_mid);
  if(mid_lineState == HIGH){
    matrix_clear();
    matrix_big_circle();
  }
  else{
    matrix_clear();
    matrix_small_circle();
  }
}
