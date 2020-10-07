/* ###################################################################
**     Filename    : main.c
**     Project     : mpu6050
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-10-02, 15:54, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CI2C1.h"
#include "IntI2cLdd1.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "math.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
/* User includes (#include below this line is not maintained by Processor Expert) */
void setUpFIFO(){
	word sent, recv;

	byte resetDevice[2] = {0x6B, 1<<7};
	byte resetFIFO[2] = {0x6A, 1<<2};

	CI2C1_SendBlock(resetDevice, 2, &sent);
	CI2C1_SendBlock(resetFIFO, 2, &sent);

	byte setClock[2] = {0x6B, 1};
	CI2C1_SendBlock(setClock, 2, &sent);

	byte setDLPF[2] = {0x1A, 1<<1}; //DLPF to make f = 1kHz

	// tells which registers are being written to the FIFO buffer
	byte enableFIFO[2] = {0x23, 0x78};  // bits 3-6 are 1's, change to bit shifting
	CI2C1_SendBlock(enableFIFO, 2, &sent);

	int FIFO_channels = 6; // 6 short ints (12 bytes) of data being read from the FIFO buffer

	byte userControl[2] = {0x6A, 1<<6};
	CI2C1_SendBlock(userControl, 2, &sent);  // enable FIFO

	// wait 10ms
	// read 10 lots of 12 bytes from the fifo buffer
}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

	word snt;
	word rcv;
	byte response=0;
	byte acc[6];
	byte gyro[6];

	float PI = 3.141592654;
	float AccX, AccY, AccZ;
	float accAngleX = 0, accAngleY = 0;
	float GyroX, GyroY, GyroZ;
	float gyroAngleX = 0, gyroAngleY = 0, gyroAngleZ = 0;
	float yaw = 0, pitch = 0, roll = 0;

	byte enable[2]={0x6B, 0};

	byte WHO_AM_I=0x75;
	byte ACCEL_XOUT_H = 0x3B;
	byte GYRO_XOUT_H = 0x43;

    FC321_Enable();
	float  elapsedTime = 0.001; // 1ms for f=1kHz

	CI2C1_SendBlock(enable, 2, &snt);// Enable MPU

	// Check connection by reading WHO am I register
	CI2C1_SendChar(WHO_AM_I);
	CI2C1_RecvChar(&response);  // WHO am I register should read 0x68

	setUpFIFO();

	for(;;){
		// read accelerometer values
		CI2C1_SendChar(ACCEL_XOUT_H);
		CI2C1_RecvBlock(acc,6,&rcv);

		AccX = (acc[0]<<8 | acc[1]) / 16384.0;  // sensitivity values on datasheet
		AccY = (acc[2]<<8 | acc[3]) / 16384.0;
		AccZ = (acc[4]<<8 | acc[5]) / 16384.0;

		// calculate pitch and roll from accelerometer
		accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180/PI) - 0.58;
		accAngleY = (atan(-1*AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) *180/PI) +1.58;

		CI2C1_SendChar(GYRO_XOUT_H);
		CI2C1_RecvBlock(gyro,6,&rcv);

		GyroX = ((gyro[0]<<8 | gyro[1]) / 131.0) + 0.56;  // sensitivity values on datasheet
		GyroY = ((gyro[2]<<8 | gyro[3]) / 131.0) - 2;
		GyroZ = ((gyro[4]<<8 | gyro[5]) / 131.0) + 0.79;

		gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
		gyroAngleY = gyroAngleY + GyroY * elapsedTime;  // elapsed time = 1ms

		yaw =  yaw + GyroZ * elapsedTime;
		roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
		pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
	}


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/
/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/