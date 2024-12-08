#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor motorLeft = AFMS.getMotor(3);  // connected to M2
Adafruit_DCMotormotorRight = AFMS.getMotor(2); // connected to M1

void setup() {
  AFMS.begin(); 
  Serial.begin(9600); 
}

void forward(int speed) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(speed);
  motorRight->setSpeed(speed);
}

void backward(int speed) {
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  motorLeft->setSpeed(speed);
  motorRight->setSpeed(speed);
}

void turnLeft(int speed) {
  motorLeft->run(BACKWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(speed);
  motorRight->setSpeed(speed);
}

void turnRight(int speed) {
  motorLeft->run(FORWARD);
  motorRight->run(BACKWARD);
  motorLeft->setSpeed(speed);
  motorRight->setSpeed(speed);
}

void stop() {
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void softStop(int initialSpeed) {
  for (int speed = initialSpeed; speed >= 0; speed--) {
    motorLeft->setSpeed(speed);
    motorRight->setSpeed(speed);
    delay(10); 
  }
  stop();
}

void turnLeftWithRadius(int leftSpeed, int rightSpeed) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(leftSpeed);
  motorRight->setSpeed(rightSpeed);
}

void turnRightWithRadius(int leftSpeed, int rightSpeed) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(leftSpeed);
  motorRight->setSpeed(rightSpeed);
}

void loop() {
  forward(150);
  delay(2000);

  backward(150);
  delay(2000);

  turnLeft(150);
  delay(1000);

  turnRight(150);
  delay(1000);

  turnLeftWithRadius(50, 150);
  delay(2000);

  turnRightWithRadius(150, 50);
  delay(2000);

  stop();
  delay(2000);
}