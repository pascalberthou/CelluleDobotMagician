#ifndef DOBOT_H
#define DOBOT_H

#include "type.h"
#include "Command.h"
#include <stdio.h>

#define X1 91.3997 //X-coordinate of Apoint
#define Y1 259.5008//Y-coordinate of A point
#define Z1 80.7794 //Z-coordinate of A point
#define R1 170.597 //R-coordinate of A point


#define X2 90.1254//X-coordinate of B point
#define Y2 258.5482//Y-coordinate of B point
#define Z2 49.657 //Z-coordinate of B point
#define R2 170.7823 //R-coordinate of B point

#define X3 142.4404 //X-coordinate of C point
#define Y3 179.9995 //Y-coordinate of C point
#define Z3 73.8378 //Z-coordinate of C point
#define R3 151.6441 //R-coordinate of C point

#define X4 143.6304 //X-coordinate of D point
#define Y4 -216.6878 //Y-coordinate of D point
#define Z4 78.1144 //Z-coordinate of D point
#define R4 43.5382 //R-coordinate of d point

#define X5 299.4815 //X-coordinate of E point
#define Y5 -74.8326 //Y-coordinate of E point
#define Z5 52.4756 //Z-coordinate of E point
#define R5 85.9706//R-coordinate of E point

#define X6 225.5811 //X-coordinate of F point
#define Y6 51.738 //Y-coordinate of F point
#define Z6 75.3284 //Z-coordinate of F point
#define R6 112.9176//R-coordinate of F point


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
