int irSensor = 3;
bool isValue = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(irSensor,INPUT);
}

void loop() {
  isValue = digitalRead(irSensor);
  Serial.println(isValue);
  if(isValue == LOW){
    Serial.println("Object is detected"); //pas sur ligne noir
  }
  else{
    Serial.println("Object not detected"); //suis ligne noir
  }
  delay(200);
}