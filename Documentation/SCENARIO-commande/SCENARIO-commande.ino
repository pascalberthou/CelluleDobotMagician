#include <Dobot.h>
#include <FlexiTimer2.h>
//#include <Magician.h>
#include <Message.h>
#include <Packet.h>
#include <Protocol.h>
#include <ProtocolDef.h>
#include <ProtocolID.h>
#include <RingBuffer.h>
#include <command.h>
#include <symbol.h>
#include <type.h>
#include <SoftwareSerial.h>
#include <Arduino.h>



void setup() {
  // Initialisation de la communication série avec le robot Dobot


Serial.begin(115200);
Serial.println("Debut Setup");
Dobot_Init();
}


// boucle infinie
void loop() {
  uint8_t resss;
  
  resss=Dobot_Piece(); //premier test de la présence d'une piéce sur le tapis 1 (capteur IR).
  Serial.println(resss);



 while (resss==1) //boucle de test de la présence d'une piéce sur le tapis1 jusqu'a qu'une piéce est détectée sur le capteur 
 {
    resss=Dobot_Piece(); 
    Dobot_Tapis1(1); 
    Dobot_Tapis2(1);
 }
  Serial.println(resss);


 Dobot_Tapis1(0);  //Moteur du Tapis 1 mis a zéro
 Dobot_AllerTapis1(1); // Premiére position au dessus du tapis 1
  Dobot_Pince(0); //Ouvrir Pince
 delay(300);
 Dobot_AllerPos1(1); // le bras descend pour prendre la piéce.
 delay(300);
 Dobot_Pince(1);  //Fermer Pince
delay(300);
Dobot_AllerPos2(1);  // le bras se déplace vers le capteur couleur 
delay(300);
 
int8_t color;
 color= Dobot_Getcolor(); // Test de la couleur de la piéce 
 delay(300);

 if (color == 1)  // Si la piéce est verte
  {
    Dobot_AllerPos3(1);  // le bras se déplace vers la position du lot de piéces vertes
    delay(300);
    Dobot_Pince(0); //ouverture pince pour déposer la piéce verte
  }
  else     // si la piéce est rouge
  {
    Dobot_AllerTapis2(1);  // le bras se déplace vers le tapis 2
    delay(300);
    Dobot_Pince(0); // ouverture de la pince pour déposer la piéce rouge sur le tapis 2
    delay(300);
    Dobot_Tapis2(1); //Activation Moteur Tapis 2
    delay(3500);
    Dobot_Tapis2(0); // Désactivation Moteur Tapis 2
  }
 delay(300);
 Dobot_AllerPosHOME(1);  // le bras revient a sa position de repos en attente d'une detection d'une nouvelle piéce.
 delay(300);

}
