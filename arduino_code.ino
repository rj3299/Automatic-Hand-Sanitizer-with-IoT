// This is the servo library we must include
#include <Servo.h>
// HC-SR04 Echo Pin & Trigger Pin connect to the Arduino Uno Digital Pins
#define echo_pin 2
#define trigger_pin 3

// Servo PWM
#define servo_pin 5

Servo servo_motor;
int pos1=0;

void setup() {
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.begin(9600);

  servo_motor.attach(servo_pin);
  servo_motor.write(180);
}

void loop() {
//  Write a pulse to the HC-SR04
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

//  Measure the response from the HC-SR04 Echo Pin
  float duration = pulseIn(echo_pin, HIGH); 
//  Here we are calculating the distance of the object from the sensor, the duration which we get is the round trip time, so we divide by 2 and then multiply by the speed of sound=343m/s or 0.0343cm/microsec
  float distance = (duration/2) * 0.0343;

  Serial.print("Distance =");
//   If the distance read by the sensor is less than 10 cm and more than the minimum 3 cm, then it is assumed that there is a hand under the sanitizer
  if ((distance > 3) && (distance < 15)) {
    Serial.print(distance);
    Serial.println(" cm");
//    The next two loops is regarding the motion of our servo motor. First, is Clockwise and then Anticlockwise to have a armature like movement
    for(pos1=0;pos1<60;pos1+=1){
      servo_motor.write(0);
      delay(10);
    }
    for(pos1=60;pos1>=1;pos1-=1){
      servo_motor.write(180);
      delay(10);
    }
  }
  else{
    Serial.println("Out of range");
  }
  servo_motor.write(90);
  delay(500);
}
