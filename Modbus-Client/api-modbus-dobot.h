#ifndef __ROBOT__
#define __ROBOT__

#include <stdio.h> /* printf et scanf */
//static Tab_Etudiant *ADDRESS;

 uint16_t modbus_read(int input_reg);

/*-- Adresse des differents Capteurs reels et Virtuels --*/
// Modbus INPUT REGISTERS
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


/*-- Adresse des differentes Trajectoires --*/
// Modbus Coil
#define COIL_SECU     00000
#define COIL_StopTi   00001
#define COIL_StartTi  00002
#define COIL_Stop2    00003
#define COIL_Start2   00004
#define COIL_Stop1    00005
#define COIL_Start1   00006
#define COIL_Prise    00007
#define COIL_Pose     00008
#define COIL_Droite   00009
#define COIL_Gauche   00010


#define C2()        modbus_read_bin(INPUT_C2)
#define C1()        modbus_read_bin(INPUT_C1)
#define I()         modbus_read_bin(INPUT_I)
#define C3()        modbus_read_bin(INPUT_C3)
#define FinPrise()  modbus_read_bin(INPUT_FinPrise)
#define FinPose()   modbus_read_bin(INPUT_FinPose)
#define T1()        modbus_read_bin(INPUT_T1)
#define T2()        modbus_read_bin(INPUT_T2)
#define TI()        modbus_read_bin(INPUT_T1)
#define SCD()       modbus_read_bin(INPUT_SCD)
#define SCG()       modbus_read_bin(INPUT_SCG)
#define PE()        modbus_read_bin(INPUT_PE)
#define OK_SECU()   modbus_read_bin(INPUT_OK_SECU) 

/*-- Adresse des differentes Trajectoires --*/
// Modbus Coil
#define SECU(val)     modbus_write_bin(COIL_SECU,(val==0)?FALSE:TRUE)
#define StopTi(val)   modbus_write_bin(COIL_StopTi,(val==0)?FALSE:TRUE)
#define StartTi(val)  modbus_write_bin(COIL_StartTi,(val==0)?FALSE:TRUE)
#define Stop2(val)    modbus_write_bin(COIL_Stop2,(val==0)?FALSE:TRUE)
#define Start2(val)   modbus_write_bin(COIL_Start2,(val==0)?FALSE:TRUE)
#define Stop1(val)    modbus_write_bin(COIL_Stop1,(val==0)?FALSE:TRUE)
#define Start1(val)   modbus_write_bin(COIL_Start1,(val==0)?FALSE:TRUE)
#define Prise(val)    modbus_write_bin(COIL_Prise,(val==0)?FALSE:TRUE)
#define Pose(val)     modbus_write_bin(COIL_Pose,(val==0)?FALSE:TRUE)
#define Droite(val)   modbus_write_bin(COIL_Droite,(val==0)?FALSE:TRUE)
#define Gauche(val)   modbus_write_bin(COIL_Gauche,(val==0)?FALSE:TRUE)

/*-- Macro manipulation PPI --*/
// Non implementé
/*#define SetCtrlPPI(x) ADDRESS->Tab_PPI[3]= ((x)==1)
#define GetPortA() Lire_Val(ADDRESS->Tab_PPI[0])
#define SetPortA(x)  ADDRESS->Tab_PPI[0]= ((x)==1)
#define GetPortB() Lire_Val(ADDRESS->Tab_PPI[1])
#define SetPortB(x)  ADDRESS->Tab_PPI[1]= ((x)==1)
#define GetPortC() Lire_Val(ADDRESS->Tab_PPI[2])
#define SetPortC(x)  ADDRESS->Tab_PPI[2]= ((x)==1)


int init_comm(void)
{
  int fd ;
  fd = open("/dev/MyMem", O_RDWR);
  if( fd < 0)
    {
      printf("ERROR : Probleme Ouverture de /dev/MyMem \n");
      return 0;
    };
  ADDRESS= (Tab_Etudiant*) mmap( 0, sizeof(Tab_Etudiant),
			PROT_READ | PROT_WRITE,
			MAP_FILE | MAP_SHARED,
			fd, BASE_ADDRESS);
  close(fd);  
  
  if( ADDRESS < 0)
    {
      printf("ERROR : Probleme de Mappage de la memoire \n");
      return 0;
    }
  return 1;
}
*/

int init_comm(char* ip, int port);
void reset_comm(void);

#endif