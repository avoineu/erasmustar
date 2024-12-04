#include <SoftwareSerial.h>

SoftwareSerial BTSerial(12,11);//TX=12,RX=11

void sendBluetoothMessage(String message) {
    BTSerial.println(message);
    Serial.println("Message Sent");
}

void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  sendBluetoothMessage("TEST message bluetooth robot");
  delay(500);
}
