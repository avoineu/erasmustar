int irSensor = 3;
bool isObjectDetected = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(irSensor,INPUT);
}

void loop() {
  isObjectDetected = digitalRead(irSensor);
  Serial.println(isObjectDetected);
  if(isObjectDetected == LOW){
    Serial.println("Object is detected"); //pas sur ligne noir
  }
  else{
    Serial.println("Object not detected"); //suis ligne noir
  }
  delay(200);
}
