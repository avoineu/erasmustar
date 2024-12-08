#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <SoftwareSerial.h>

// Ultrasound sensor pins
const int trigPin = 14;  
const int echoPin = 15;  
const float SPEED_OF_SOUND_CM_PER_US = 0.0343; // sound speed in cm/µs

// Infrared sensor pin and variables
int irSensor = 3;

// Bluetooth pins
const int bluetoothTx = 12;
const int bluetoothRx = 11;
SoftwareSerial BTSerial(bluetoothTx, bluetoothRx);

// Motor setup
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);  // connected to M2
Adafruit_DCMotor *motorRight = AFMS.getMotor(2); // connected to M1

// FSM states
enum State { IDLE, ROTATE_LEFT, ROTATE_RIGHT, STOP };
State currentState = IDLE;

// Variables for FSM
unsigned long startTime;
int changeCount = 0;
const int maxChanges = 5;
const unsigned long maxDuration = 30000; // 30 seconds

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

void softStop(int initialSpeed) {
  for (int speed = initialSpeed; speed >= 0; speed--) {
    motorLeft->setSpeed(speed);
    motorRight->setSpeed(speed);
    delay(10); 
  }
  stopMotor();
}

void stopMotor() {
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
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

void sendBluetoothMessage(String message) {
  BTSerial.println(message);
  Serial.println("Message Sent : " + message);
}

void loop() {
  float distance = measureDistance();
  bool objectDetected = (distance > 0 && distance < 10); // 10 cm == the detection threshold

  switch (currentState) {
    case IDLE:
      if (objectDetected) {
        currentState = ROTATE_LEFT;
        startTime = millis();
        changeCount = 0;
        forward(150);
        Serial.println("State: ROTATE_LEFT");
        sendBluetoothMessage("State: ROTATE_LEFT");
      }
      break;

    case ROTATE_LEFT:
      if (objectDetected) {
        currentState = ROTATE_RIGHT;
        changeCount++;
        backward(150);
        Serial.println("State: ROTATE_RIGHT");
        sendBluetoothMessage("State: ROTATE_RIGHT");
      }
      break;

    case ROTATE_RIGHT:
      if (objectDetected) {
        currentState = ROTATE_LEFT;
        changeCount++;
        forward(150);
        Serial.println("State: ROTATE_LEFT");
        sendBluetoothMessage("State: ROTATE_LEFT");
      }
      break;

    case STOP:
      stopMotor();
      Serial.println("State: STOP");
      sendBluetoothMessage("State: STOP");
      break;
  }

  if (changeCount >= maxChanges || (millis() - startTime) >= maxDuration) {
    currentState = STOP;
  }

  delay(500);
}