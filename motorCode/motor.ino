// #include <Wire.h>
// #include <Adafruit_MotorShield.h>

// Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);  // Moteur gauche connecté à M2
// Adafruit_DCMotor *motorRight = AFMS.getMotor(2); // Moteur droit connecté à M1

// void setup() {
//   AFMS.begin();

//   motorLeft->setSpeed(0);  // Vitesse du moteur (0-255)
//   motorRight->setSpeed(0); 

//   motorLeft->run(FORWARD);  
//   motorRight->run(FORWARD); 
// }

// void loop() {
//   // On controle la vitesse de rotation des roues
//   motorLeft->setSpeed(0);  // Vitesse du moteur (0-255)
//   motorRight->setSpeed(0); 
// }


#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Initialisation de la carte Adafruit Motor Shield et des moteurs
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);  // Moteur gauche (connecté à M2)
Adafruit_DCMotor *motorRight = AFMS.getMotor(2); // Moteur droit (connecté à M1)

// Initialisation
void setup() {
  AFMS.begin();  // Démarrage de la carte
  Serial.begin(9600);  // Initialisation du port série pour debug
}

// Fonction pour avancer
void avancer(int vitesse) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(vitesse);
  motorRight->setSpeed(vitesse);
}

// Fonction pour reculer
void reculer(int vitesse) {
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  motorLeft->setSpeed(vitesse);
  motorRight->setSpeed(vitesse);
}

// Fonction pour tourner à gauche sur place
void tournerGaucheSurPlace(int vitesse) {
  motorLeft->run(BACKWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(vitesse);
  motorRight->setSpeed(vitesse);
}

// Fonction pour tourner à droite sur place
void tournerDroiteSurPlace(int vitesse) {
  motorLeft->run(FORWARD);
  motorRight->run(BACKWARD);
  motorLeft->setSpeed(vitesse);
  motorRight->setSpeed(vitesse);
}

// Fonction pour tourner à gauche avec un rayon
void tournerGaucheAvecRayon(int vitesseGauche, int vitesseDroite) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(vitesseGauche);
  motorRight->setSpeed(vitesseDroite);
}

// Fonction pour tourner à droite avec un rayon
void tournerDroiteAvecRayon(int vitesseGauche, int vitesseDroite) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(vitesseGauche);
  motorRight->setSpeed(vitesseDroite);
}

// Fonction pour arrêter le robot
void arret() {
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

// Fonction pour un arrêt progressif
void arretProgressif(int vitesseInitiale) {
  for (int vitesse = vitesseInitiale; vitesse >= 0; vitesse--) {
    motorLeft->setSpeed(vitesse);
    motorRight->setSpeed(vitesse);
    delay(10);  // Ajuster pour ralentir plus ou moins vite
  }
  arret();  // Une fois arrêté, libérer les moteurs
}

// Boucle principale
void loop() {
  avancer(150);  // Avancer à une vitesse de 150
  delay(2000);   // Attendre 2 secondes

  reculer(150);  // Reculer à une vitesse de 150
  delay(2000);   // Attendre 2 secondes

  tournerGaucheSurPlace(150);  // Tourner à gauche sur place
  delay(1000);                 // Attendre 1 seconde

  tournerDroiteSurPlace(150);  // Tourner à droite sur place
  delay(1000);                 // Attendre 1 seconde

  tournerGaucheAvecRayon(50, 150);  // Tourner à gauche avec un rayon
  delay(2000);                      // Attendre 2 secondes

  tournerDroiteAvecRayon(150, 50);  // Tourner à droite avec un rayon
  delay(2000);                      // Attendre 2 secondes

  arret();  // Arrêter le robot
  delay(2000);  // Attendre 2 secondes

  arretProgressif(150);  // Arrêter progressivement depuis une vitesse de 150
  delay(2000);           // Attendre 2 secondes
}
