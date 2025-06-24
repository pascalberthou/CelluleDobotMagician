#ifndef DOBOT_H
#define DOBOT_H

#include "type.h"
#include "Command.h"
#include <stdio.h>

#define X1 -71.14275 //X-coordinate of A point
#define Y1 215.7542//Y-coordinate of A point
#define Z1 46.6987//Z-coordinate of A point
#define R1 108.3176 //R-coordinate of A point


#define X2 -73.1375//X-coordinate of B point
#define Y2 212.3363//Y-coordinate of B point
#define Z2 30.5996 //Z-coordinate of B point
#define R2 109.0059 //R-coordinate of B point

#define X3 1.539 //X-coordinate of C point
#define Y3 195.9458 //Y-coordinate of C point
#define Z3 44.054 //Z-coordinate of C point
#define R3 89.55 //R-coordinate of C point

#define X4 246.9173 //X-coordinate of D point
#define Y4 -103.4815 //Y-coordinate of D point
#define Z4 27.2219 //Z-coordinate of D point
#define R4 -22.7383 //R-coordinate of d point

#define X5 260.5969 //X-coordinate of E point
#define Y5 137.5167 //Y-coordinate of E point
#define Z5 28.7954 //Z-coordinate of E point
#define R5 27.8206//R-coordinate of E point

#define X6 115.8233 //X-coordinate of F point
#define Y6 193.5941 //Y-coordinate of F point
#define Z6 105.6224 //Z-coordinate of F point
#define R6 59.1088//R-coordinate of F point


typedef enum tagIOFunction {
    IOFunctionDummy,
    IOFunctionDO,
    IOFunctionPWM,
    IOFunctionDI,
    IOFunctionADC,
    IOFunctionDIPU,
    IOFunctionDIPD,
} IOFunction;

/*********************************************************************************************************
** Device Init
*********************************************************************************************************/
extern void Dobot_Init();


/*********************************************************************************************************
** Home function
*********************************************************************************************************/
extern void Dobot_SetHOMECmd(void);


/*********************************************************************************************************
** EndEffector function
*********************************************************************************************************/
extern void Dobot_Pince(bool isGriped);

/*********************************************************************************************************
** PTP function
*********************************************************************************************************/
extern void Dobot_SetPTPCmd(uint8_t Model,float x,float y,float z,float r);

extern void Dobot_AllerTapis1(bool state);
extern void Dobot_AllerTapis2(bool state);
extern void Dobot_AllerPos1(bool state);
extern void Dobot_AllerPos2(bool state);
extern void Dobot_AllerPos3(bool state);
extern void Dobot_AllerPosHOME(bool state);


/*********************************************************************************************************
** EIO function
*********************************************************************************************************/
extern void Dobot_SetIOMultiplexing(uint8_t address,uint8_t function);
extern uint8_t Dobot_GetIODI(uint8_t address);
extern uint8_t Dobot_Piece();
extern uint8_t Dobot_Getcolor();

extern void Dobot_Tapis1(bool enable);
extern void Dobot_Tapis2(bool enable);

/***************************************************************************************************************************************************/











#endif
