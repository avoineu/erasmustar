
const int trigPin = 14;  // D14 correspond à A0
const int echoPin = 15;  // D15 correspond à A1

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Envoyer une impulsion de 10µs sur Trigger
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Lire la durée du retour de l'impulsion Echo
  long duration = pulseIn(echoPin, HIGH);
  
  // Calcule la distance en cm
  float distance = (duration * 0.0343) / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print("temps: ");
  Serial.println(duration);

  // Pause avant la prochaine mesure
  delay(500);
}