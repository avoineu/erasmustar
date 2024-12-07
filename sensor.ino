// Ultrasound sensor pins
const int trigPin = 14;  
const int echoPin = 15;  

const float SPEED_OF_SOUND_CM_PER_US = 0.0343; // sound speed in cm/µs

// Infrared sensor pin and variables
int irSensor = 3;
bool isObjectDetected = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(irSensor, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * SPEED_OF_SOUND_CM_PER_US) / 2;
  Serial.println("Distance: " + String(distance) + " temps: " + String(duration));

  isObjectDetected = digitalRead(irSensor);
  Serial.println(isObjectDetected);
  if (isObjectDetected == LOW) {
    Serial.println("Object is detected"); // not on black line
  } else {
    Serial.println("Object not detected"); // on black line
  }

  delay(500);
}