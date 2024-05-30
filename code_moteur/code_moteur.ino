#include <SoftwareSerial.h> //extension pour gérer la connexion entre le module bluetooth et notre carte arduino
SoftwareSerial BluetoothSerial(2, 3); //configuration de la réception bluetooth avec les pins sur lesquels le mobule bluetooth est branché

//Pins sur lesquels nous avons branché le premier moteur
#define motor1Pin1 8
#define motor1Pin2 9
#define enable1Pin 7

//Pins sur lesquels nous avons branché le second moteur
#define motor2Pin1 10
#define motor2Pin2 11
#define enable2Pin 12


void setup() { //on configure chacun des pins en fonction de s'il s'agit une entrée ou une sortie
  pinMode(2, INPUT); 
  pinMode(3, OUTPUT);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  Serial.begin(9600);
  BluetoothSerial.begin(9600); //permet de définir la fréquence à laquelle le bluetooth fonctionne

  Serial.println("Setup complete"); //permet de vérifier dans la console si tout s'est correctement déroulé
}



void setMotorSpeed(int motorPin1, int motorPin2, int enablePin, int speed) { //fonction qui gère la mise en marche d'un moteur
  if (speed > 0) { //si la vitesse est positive alors on va faire passé du courant dans le pin défini en HIGH. Le LOW fonctionnera comme le - électrique
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  } else if (speed < 0) { //si la vitesse est négative, on va inversé le courant ce qui fera tourner le moteur dans le sens inverse.
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    speed = -speed;
  } else { //si on n'a une vitesse nulle, alors on éteint les moteurs
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  }
  analogWrite(enablePin, speed);
}

void turn_left() { //on va définir chaque fonction pour gérer les directions grâce aux sens de rotation de chaque moteur en appelant la fonction précédente
  Serial.println("GO LEFT");
  setMotorSpeed(motor1Pin1, motor1Pin2, enable1Pin, 1);
  setMotorSpeed(motor2Pin1, motor2Pin2, enable2Pin, -1);
}

void turn_right() {
  Serial.println("GO RIGHT");
  setMotorSpeed(motor1Pin1, motor1Pin2, enable1Pin, -1);
  setMotorSpeed(motor2Pin1, motor2Pin2, enable2Pin, 1);
}

void move_backward() {
  Serial.println("GO BACK");
  setMotorSpeed(motor1Pin1, motor1Pin2, enable1Pin, -1);
  setMotorSpeed(motor2Pin1, motor2Pin2, enable2Pin, -1);
}

void move_forward() {
  Serial.println("GO FRONT");
  setMotorSpeed(motor1Pin1, motor1Pin2, enable1Pin, 1);
  setMotorSpeed(motor2Pin1, motor2Pin2, enable2Pin, 1);
}

void stop_speed() {
  Serial.println("STOP");
  setMotorSpeed(motor1Pin1, motor1Pin2, enable1Pin, 0);
  setMotorSpeed(motor2Pin1, motor2Pin2, enable2Pin, 0);
}

float motor1Speed = 0;
float motor2Speed = 0;



void loop() { //on exécute tout le code en boucle
  if (BluetoothSerial.available()) { //si on recoit des données par bluetooth par l'application mobile...
    String Direction = BluetoothSerial.readStringUntil('\n'); //on lit cette information qu'on enregistre dans une chaine de charactère nommée Direction
    Serial.print("Received command: ");
    Serial.println(Direction);
    if((motor1Speed ==0)||(motor2Speed==0))
    {
      if (Direction == "Forward") { //en fonction de la chaine de caractères, on va appeler la fonction associée au sens demandé 
        move_forward();
        motor1Speed = 1; //permet réduire le nombre d'itération du code car lorsque le moteur est en route on ne rentrera pas dans la condition ci-dessus et on aura moins de test a effectué
        motor2Speed = 1;
      } else if (Direction == "Backward") {
        move_backward();
        motor1Speed = 1;
        motor2Speed = 1;
      } else if (Direction == "Right") {
        turn_right();
        motor1Speed = 1;
        motor2Speed = 1;
      } else if (Direction == "Left") {
        turn_left();
        motor1Speed = 1;
        motor2Speed = 1;
      }
    } 
    else if (Direction == "Stop") { //a chaque fois qu'on arrete d'appuyer sur un bouton de l'application mobile, alors on va arreter le robot
      stop_speed();
      motor1Speed = 0;
      motor2Speed = 0;
    }
  }

  
  if (motor1Speed != 0 && motor2Speed != 0) {
   Serial.println("Avance");
   delay(5); //délai de 5ms pour éviter la surcharge d'informations
 }
}
