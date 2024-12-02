
const int trigPin = 14;  
const int echoPin = 15;  
const float SPEED_OF_SOUND_CM_PER_US = 0.0343; // sound speed in cm/µs
 
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  long duration = pulseIn(echoPin, HIGH);
 
  float distance = (duration *  SPEED_OF_SOUND_CM_PER_US) / 2;
 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print("temps: ");
  Serial.println(duration);
 
  delay(500);
