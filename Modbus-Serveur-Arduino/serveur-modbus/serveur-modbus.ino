#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoModbus.h>
#include <Servo.h>


/* 
  Biliotheque Modbus pour la commande du Robot Dobot

  Connectique : 
    Arduino Mega
    Shield Ethernet Arduino
    Boutton Arret d'urgence :       Pin 2
    Led debug Modbus :              Pin 7
    Servo moteur table d'indexage : Pin 9

  led de Debug sur port 7 de l'arduino
    5 blinks : error
    2 blink : discrete output 1
    3 blink : discrete input 1
    1 blink : discrete output 0
  
  Definition de 13 INPUTS : entrees discretes modbus / capteurs du dobot
  Definition de 11 COILS :  sorties discretes modbus / actions du dobot
*/


/*-- Adresse des differents Capteurs reels et Virtuels --*/
// Modbus INPUT REGISTERS
#define INPUT_ADDR      10011
#define INPUT_OK_SECU   10011
#define INPUT_C2        10012
#define INPUT_C1        10013
#define INPUT_I         10014
#define INPUT_C3        10015
#define INPUT_FinPrise  10016
#define INPUT_FinPose   10017
#define INPUT_T1        10018
#define INPUT_T2        10019
#define INPUT_TI        10020
#define INPUT_SCD       10021
#define INPUT_SCG       10022
#define INPUT_PE        10023

// Fonctions dobot associees aux capteurs
#define F_INPUT_OK_SECU     genere_valeur // a remplacer par la fonction dobot associee
#define F_INPUT_C2          genere_valeur
#define F_INPUT_C1          genere_valeur
#define F_INPUT_I           genere_valeur
#define F_INPUT_C3          genere_valeur
#define F_INPUT_FinPrise    genere_valeur
#define F_INPUT_FinPose     genere_valeur
#define F_INPUT_T1          genere_valeur
#define F_INPUT_T2          genere_valeur
#define F_INPUT_TI          genere_valeur
#define F_INPUT_SCD         genere_valeur
#define F_INPUT_SCG         genere_valeur
#define F_INPUT_PE          genere_valeur

/*-- Adresse des differentes Trajectoires --*/
// Modbus Coil
#define COILS_ADDR    0
#define COIL_SECU     0
#define COIL_StopTi   1
#define COIL_StartTi  2
#define COIL_Stop2    3
#define COIL_Start2   4
#define COIL_Stop1    5
#define COIL_Start1   6
#define COIL_Prise    7
#define COIL_Pose     8
#define COIL_Droite   9
#define COIL_Gauche   10

// Modbus Coil
#define F_COIL_SECU()     blinkRedLight(5) // a remplacer par la fonction dobot
#define F_COIL_StopTi()   myservo.write((servoPos+=45)%180)  // rotation en degre de la table d'indexage  
//#define F_COIL_StartTi()  myservo.write((servoPos+=45)%180-180) // rotation de 45 degre de la table d'indexage 
#define F_COIL_StartTi()  myservo.write((servoPos+=45)%180) // rotation de 45 degre de la table d'indexage 
#define F_COIL_Stop2()    dobotSet()
#define F_COIL_Start2()   dobotSet()
#define F_COIL_Stop1()    dobotSet()
#define F_COIL_Start1()   dobotSet()
#define F_COIL_Prise()    dobotSet()
#define F_COIL_Pose()     dobotSet()
#define F_COIL_Droite()   dobotSet()
#define F_COIL_Gauche()   dobotSet()

// Variables globales
int value; 
int valeur=26;
int CoilValue=0;

// Gestion Bouton d'urgence
const int buttonPin=2; // bouton urgence
int stop; // Etat bouton d'urgence

// Gestion servo moteur Table d'Indexage
Servo myservo;                           
int servoPin = 9;     // Servo moteur sur la pin 9
int servoPos = 0;


// Gestion Modbus
const int ledPin   =7; // led debug modbus
ModbusTCPServer modbusServer;
EthernetServer ethServer(502);  // Serveur Modbus sur le port 502
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Configuration de l'adresse MAC et IP de l'Arduino
IPAddress ip(169, 254, 36, 66);  // Adresse IP statique

// Variable pour tests - a supprimer
uint8_t input_val=FALSE;


// Led rouge pour debug modbus
void blinkRedLight(int nb)
{
  for (int i=0;i<nb;i++)
    digitalWrite(ledPin, HIGH); delay(10); digitalWrite(ledPin, LOW);delay(10);
  delay(1000);
}

void blinkPacketReceived()
{
   digitalWrite(ledPin, HIGH); delay(100); digitalWrite(ledPin, LOW);delay(100);
}

void stopOnError()
{
    blinkRedLight(5);
    digitalWrite(ledPin, HIGH);
    while(1);
}



void dobotSet()
{

}

// fonction qui ne fait rien
void nop()
{

}

uint8_t genere_valeur()
{
  input_val=!input_val;/*!input_val*/;
  Serial.println(input_val);
  return(input_val);
}

void setup() {
  int success = 0; 

  Serial.begin(115200); // configuration ligne serie pour debug 
  while (!Serial);      // Ne fonctionne pas avec le shield Ethernet ! A supprimer

  // configure les broches de l'arduino
  pinMode(ledPin, OUTPUT);    // led debug
  pinMode(buttonPin, INPUT);  // boutton stop
  digitalWrite(ledPin, LOW);  // extinction de la led
  myservo.attach(servoPin);   // servo moteur
  myservo.write(servoPos);    // position initiale 0 degres

  // Initialisation du module Ethernet
  Ethernet.begin(mac, ip);
  ethServer.begin();
  Serial2.print("Adresse IP : ");
  Serial2.println(Ethernet.localIP());

  // Démarrer le serveur Modbus
  if (!modbusServer.begin()) {
    Serial.println("Échec de l'initialisation du serveur Modbus TCP");
    stopOnError();
  }

  // Définition des registres Modbus (exemple : 10 registres de stockage)
  // modbusServer.configureHoldingRegisters(OUTPUT_REGS_ADDR, 13);
  // modbusServer.configureInputRegisters(INPUT_REGS_ADDR, 11);

  // definition des sorties binaires
  success=modbusServer.configureCoils(COILS_ADDR,11);
  if (!success)     stopOnError();
  // definition des entrees binaires
  success=modbusServer.configureDiscreteInputs(INPUT_ADDR,13);
  if (!success)     stopOnError();
  Serial.println("Serveur Modbus TCP pret");
}
// Lecture des Sorties binaires
void manageCoils()
{
  //#define COIL_SECU     00000
  if (value=modbusServer.coilRead(COIL_SECU))
      {F_COIL_SECU();return;}
  //#define COIL_StopTi   00001
   if (value=modbusServer.coilRead(COIL_StopTi))
      {F_COIL_StopTi();return;}
  //#define COIL_StartTi  00002
    if (value=modbusServer.coilRead(COIL_StartTi))
      {F_COIL_StartTi(); return;}
  //#define COIL_Stop2    00003
    if (value=modbusServer.coilRead(COIL_Stop2))
      {F_COIL_Stop2(); return;}
  //#define COIL_Start2   00004
    if (value=modbusServer.coilRead(COIL_Start2))
      {F_COIL_Start2(); return;}
  //#define COIL_Stop1    00005
    if (value=modbusServer.coilRead(COIL_Stop1))
      {F_COIL_Stop1(); return;}
  //#define COIL_Start1   00006
    if (value=modbusServer.coilRead(COIL_Start1))
      {F_COIL_Start1(); return;}
  //#define COIL_Prise    00007
    if (value=modbusServer.coilRead(COIL_Prise))
      {F_COIL_Prise(); return;}
  //#define COIL_Pose     00008
    if (value=modbusServer.coilRead(COIL_Pose))
      {F_COIL_Pose(); return;}
  //#define COIL_Droite   00009
    if (value=modbusServer.coilRead(COIL_Droite))
      {F_COIL_Droite(); return;}
  //#define COIL_Gauche   00010
    if (value=modbusServer.coilRead(COIL_Gauche))
      {F_COIL_Gauche(); return;}
  if (value==1)
  {
    blinkPacketReceived(); // led Debug x2 : 1
  }
}
 
 void manageInputs()
 {
  //#define INPUT_OK_SECU   100011
  if (modbusServer.discreteInputWrite(INPUT_OK_SECU,F_INPUT_OK_SECU())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_C2        10012
  if (modbusServer.discreteInputWrite(INPUT_C2,F_INPUT_C2())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_C1        10013
  if (modbusServer.discreteInputWrite(INPUT_C1,F_INPUT_C1())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_I         10014
   input_val=F_INPUT_I();
  if (modbusServer.discreteInputWrite(INPUT_I,input_val/*F_INPUT_I()*//*genere_valeur()*//*FALSE*/)==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_C3        10015
  if (modbusServer.discreteInputWrite(INPUT_C3,F_INPUT_C3())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_FinPrise  10016
  if (modbusServer.discreteInputWrite(INPUT_FinPrise,F_INPUT_FinPrise())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_FinPose   10017
  if (modbusServer.discreteInputWrite(INPUT_FinPose,F_INPUT_FinPose())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_T1        10018
  if (modbusServer.discreteInputWrite(INPUT_T1,F_INPUT_T1())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_T2        10019
  if (modbusServer.discreteInputWrite(INPUT_T2,F_INPUT_T2())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_TI        10020
  if (modbusServer.discreteInputWrite(INPUT_TI,F_INPUT_TI())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_SCD       10021
  if (modbusServer.discreteInputWrite(INPUT_SCD,F_INPUT_SCD())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_SCG       10022
 if (modbusServer.discreteInputWrite(INPUT_SCG,F_INPUT_SCG())==-1)
      blinkRedLight(3); // led Debug x3 : error
 // #define INPUT_PE        10023 
  if (modbusServer.discreteInputWrite(INPUT_PE,F_INPUT_PE())==-1)
      blinkRedLight(3); // led Debug x3 : error
}

/* Gestion des sorties numériques 16bits 
testé, fonctionne, à adapter aux besoins */

void manageInputRegs()
{
 if ((CoilValue = modbusServer.inputRegisterRead(COIL_StopTi))==-1){
      Serial.println("Error while reading holding register"); // Registre 0 = Temps en secondes
     }
    else
    {
      valeur=CoilValue;
    }
}

// Gestion des Registres - entrees numériques 16 bits  ....
    // Exemple : Mettre à jour un registre avec une valeur
    // Fonctionnement teste mais la lecture de la valeur pose soucis ... 
    // peut-être probleme lie a holding register au lieu de input ... 
void manageOutputRegs()
{
    if (modbusServer.holdingRegisterWrite(INPUT_C1,valeur)!=1)
      Serial.println("Error while writing holding register"); // Registre 0 = Temps en secondes
    else
      Serial.println("register Write");
}

void manageLocalIO()
{
  stop = digitalRead(buttonPin); // Lire l'état du bouton poussoir
  if (stop == HIGH)
      digitalWrite(ledPin, HIGH);
}


void loop() {
  Serial.println("Loop begins");
  while(1)
  {
    // Accepter les connexions clients
    EthernetClient client = ethServer.available();
  
    if (client) {
      // a new client connected
      Serial.println("new client");
      // let the Modbus TCP accept the connection 
      modbusServer.accept(client);
      manageInputs();
      //Serial.println("ecoute");
      while (client.connected()) 
      {
         //if(modbusServer.poll())
         manageInputs();
        // poll for Modbus TCP requests, while client connected
        if(modbusServer.poll())
            manageCoils();
        manageLocalIO();
      }
    }
  }
}