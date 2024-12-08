#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Ultrasound sensor pins
const int trigPin = 14;  
const int echoPin = 15;  
const float SPEED_OF_SOUND_CM_PER_US = 0.0343; // sound speed in cm/µs

// Infrared sensor pin and variables
int irSensor = 3;
bool isObjectDetected = HIGH;

// Motor setup
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);  // connected to M2
Adafruit_DCMotor *motorRight = AFMS.getMotor(2); // connected to M1

void setup() {

  AFMS.begin(); 

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irSensor, INPUT);
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

bool checkInfraredSensor() {
  bool isObjectDetected = digitalRead(irSensor) == LOW;
  Serial.println(isObjectDetected);
  if (isObjectDetected) {
    Serial.println("Object is detected"); // not on black line
  } else {
    Serial.println("Object not detected"); // on black line
  }
  return isObjectDetected;
}

float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * SPEED_OF_SOUND_CM_PER_US) / 2;
  Serial.println("Distance: " + String(distance) + " cm temps: " + String(duration));

  return distance;
}

void loop() {
  // Ultrasound sensor measurement
  float distance = measureDistance();

  // Infrared sensor measurement
  bool objectDetected = checkInfraredSensor();
  Serial.println(objectDetected);

  // Motor control logic
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

  delay(500);
}