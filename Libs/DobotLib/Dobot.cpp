#include "command.h"
#include "type.h"
#include "stdio.h"
#include "Dobot.h"
#include "FlexiTimer2.h"
#include "Protocol.h"
#include "HardwareSerial.h"
#include "arduino.h"


/*Cette bfonction initialise les paramètres du bras robotique Dobot Magician.
 Elle est utilisée pour configurer le bras robotique pour le contrôle à partir de l'Arduino*/
void Dobot_Init()
{
    SERIALNUM.begin(115200);  //SERIALNUM==Serial2(pin 16(tx) et pin 17(rx))
    delay(1000);

    ProtocolInit();

    Serial.println("Dobot Init");
    for(int i = 0; i < 21; i++){
        Dobot_SetIOMultiplexing(i,IOFunctionDI);
    }
    SetQueuedCmdStartExec();
}

// Fonction qui raméne le robot a une position initiale
void Dobot_SetHOMECmd(void)
{
    SetHomeCmd();
    WaitQueuedCmdFinished();
}
// Fonction qui determine le mode de mouvement ainsi que le point cible qu'on veut atteindre.
void Dobot_SetPTPCmd(uint8_t Model,float x,float y,float z,float r)
{
    static PTPCmd ptpCmd;

    ptpCmd.ptpMode = Model; // Mode de mouvement
    ptpCmd.x = x;  // coordonnée x de la position cible
    ptpCmd.y = y;  // coordonnée Y de la position cible
    ptpCmd.z = z;  // coordonnée Z de la position cible
    ptpCmd.rHead = r; // orientation de l'organe terminale

    SetPTPCmd(&ptpCmd);
    WaitQueuedCmdFinished();
}


void Dobot_SetIOMultiplexing(uint8_t address,uint8_t function) //Set IO en entrée ou sortie
{
    static IOConfig iOConfig;

    iOConfig.address = address; //Adresse de l'IO (1 a 20)
    iOConfig.function = (IOFunction)function; //Fonctionement de l'IO (PWM,DI,AI..)

    SetIOMultiplexing(&iOConfig);
}

uint8_t Dobot_GetIODI(uint8_t address) //Donne le Résultat de l'entrée DI (Digital input)
{
    static EIODI eIODI;

    eIODI.address = address;

    GetIODI(&eIODI);

    return eIODI.value;
}



// Fonction pour ouvrir ou fermer la pince
void Dobot_Pince(bool isGriped)
{
    static EndEffectorGripper Pince;

    Pince.isEnable = 1;
    Pince.isGriped = isGriped; // 1:fermer Pince 0:Ouvrir Pince

    SeEndEffectorGritpper(&Pince);
}

/***************************************************************************************************************/

void Dobot_AllerTapis1(bool state)
{
  	if (state == 1)
  	{
    	Dobot_SetPTPCmd(JUMP_XYZ,X1,Y1,Z1,R1);
  	}

}

void Dobot_AllerTapis2(bool state)
{
  	if (state == 1)
  	{
    	Dobot_SetPTPCmd(JUMP_XYZ,X5,Y5,Z5,R5);
  	}
}

void Dobot_AllerPos1(bool state)
{
  	if (state == 1)
  	{
    	Dobot_SetPTPCmd(JUMP_XYZ,X2,Y2,Z2,R2);
  	}
}

void Dobot_AllerPos2(bool state)
{
  	if (state == 1)
  	{
    	Dobot_SetPTPCmd(JUMP_XYZ,X3,Y3,Z3,R3);
  	}
}

void Dobot_AllerPos3(bool state)
{
  	if (state == 1)
  	{
    	Dobot_SetPTPCmd(JUMP_XYZ,X4,Y4,Z4,R4);
  	}
}

void Dobot_AllerPosHOME(bool state)
{
  	if (state == 1)
  	{
    	Dobot_SetPTPCmd(JUMP_XYZ,X6,Y6,Z6,R6);
  	}
}
/***************************************************************************************************************/

// Fonction pour controler (Activer/Désactiver) le Tapis_1 address=0:Donc il doit étre brancher sur stepper1
void Dobot_Tapis1(bool enable)
{
    static EMotor eMotor;

    eMotor.address = 0;
    eMotor.enable = enable;
    eMotor.speed = 4000;

    SetEMotor(&eMotor);
}

// Fonction pour controler (Activer/Désactiver) le Tapis_1 address=1:Donc il doit étre brancher sur stepper2

void Dobot_Tapis2(bool enable)
{
    static EMotor eMotor;

    eMotor.address = 1;
    eMotor.enable = enable;
    eMotor.speed = 4000;

    SetEMotor(&eMotor);
}
/*********************************************************************************************************************/

uint8_t Dobot_Piece() //Fonction de detection d'une piece sur le Tapis (Detecteur branché a GP4)
{
	uint8_t state;
	Dobot_SetIOMultiplexing(7,IOFunctionDI);  //Set IO7(ADC-GP4) en entrée
	state=Dobot_GetIODI(7);                     //Résultat de l'entrée IO7
	return state;
}
/***************************************************************************************************************************/

uint8_t Dobot_Getcolor()
{
	uint8_t res1,res2;
	Dobot_SetIOMultiplexing(4,IOFunctionDI); //Set IO4(ADC-GP5) en entrée
    Dobot_SetIOMultiplexing(5,IOFunctionDI); //Set IO5(ADC-GP5) en entrée
	res1=Dobot_GetIODI(4);
	res2=Dobot_GetIODI(5);
	if(res1== 0 && res2== 0)
	{
  		return 0;
	}
	if(res1== 0 && res2== 1)
	{
  		return 1;
	}
	if(res1== 1 && res2== 0)
	{
 		 return 2;
	}
    else
	{
 		 return 3;
    }
}


