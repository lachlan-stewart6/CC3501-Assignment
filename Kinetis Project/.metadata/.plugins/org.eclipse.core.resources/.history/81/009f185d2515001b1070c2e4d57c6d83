/* ###################################################################
**     Filename    : main.c
**     Project     : 87686
**     Processor   : MK20DX128VMC7
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-10-22, 14:05, # CodeGen: 0
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
#include "Bluetooth_Term.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "GyroTimer.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
#include "BluetoothTimer.h"
#include "RealTimeLdd2.h"
#include "TU2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "math.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
/* User includes (#include below this line is not maintained by Processor Expert) */
int16_t data[128]; // 256 bytes;
int data_index=0;

void sendBT(float pitch, float roll, float yaw, float MagX, float MagY,
			float MagZ, word elapsedTime) {
		Bluetooth_Term_MoveTo(1,1);
		Bluetooth_Term_SendStr("Pitch: ");
		Bluetooth_Term_SendFloatNum(pitch);
		Bluetooth_Term_SendStr("\r\n");
		Bluetooth_Term_SendStr("Roll: ");
		Bluetooth_Term_SendFloatNum(roll);
		Bluetooth_Term_SendStr("\r\n");
		Bluetooth_Term_SendStr("Yaw: ");
		Bluetooth_Term_SendFloatNum(yaw);
		Bluetooth_Term_SendStr("\r\n");
		Bluetooth_Term_SendStr("MagX: ");
		Bluetooth_Term_SendFloatNum(MagX);
		Bluetooth_Term_SendStr("\r\n");
		Bluetooth_Term_SendStr("MagY: ");
		Bluetooth_Term_SendFloatNum(MagY);
		Bluetooth_Term_SendStr("\r\n");
		Bluetooth_Term_SendStr("MagZ: ");
		Bluetooth_Term_SendFloatNum(MagZ);
		Bluetooth_Term_SendStr("\r\n");
		Bluetooth_Term_SendStr("Time(us): ");
		Bluetooth_Term_SendNum(elapsedTime);
		Bluetooth_Term_SendStr("\r\n");
		//Bluetooth_Term_Cls();
	}


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	float PI = 3.141592654;
	float AccX, AccY, AccZ;
	float accAngleX = 0, accAngleY = 0;
	float GyroX, GyroY, GyroZ;
	float gyroAngleX = 0, gyroAngleY = 0, gyroAngleZ = 0;
	float MagX = 0, MagY = 0, MagZ = 0;
	float yaw = 0, pitch = 0, roll = 0;
	word elapsedTime, bluetoothTime;
	char ICM_addr = 0x69;
	byte acc[6];
	byte gyro[6];
	byte mag[6];
	byte PWR_MGMT_1 = {0x06};
	byte ICM_WHO_AM_I = {0x00};
	word sent, recv;
	byte response;

	byte enableICM[2] = {PWR_MGMT_1, 0};
	CI2C1_SendBlock(enableICM, 2, &sent);
	CI2C1_SendChar(ICM_WHO_AM_I);
	CI2C1_RecvChar(&response);
	char ICM_confirm[100];
	sprintf(ICM_confirm, "MPU Setup (expecting 234): %i\r\n", response);
	Bluetooth_Term_SendStr(ICM_confirm);

	// Bluetooth_Term_Cls();
	for (;;){
		CI2C1_SendChar(0x2D);
		CI2C1_RecvBlock(acc,6,&recv);

		AccX = (acc[0]<<8 | acc[1]);  // sensitivity values on datasheet
		AccY = (acc[2]<<8 | acc[3]);
		AccZ = (acc[4]<<8 | acc[5]);

		// calculate pitch and roll from accelerometer
		accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180/PI) - 0.58;
		accAngleY = (atan(-1*AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) *180/PI) + 1.58;

		CI2C1_SendChar(0x33);
		CI2C1_RecvBlock(gyro,6,&recv);

		GyroX = (gyro[0]<<8 | gyro[1]);  // sensitivity values on datasheet
		GyroY = (gyro[2]<<8 | gyro[3]);
		GyroZ = (gyro[4]<<8 | gyro[5]);

		BluetoothTimer_GetTimeUS(&elapsedTime);
		gyroAngleX = gyroAngleX + (GyroX * (elapsedTime/1000000)); // deg/s * s = deg
		gyroAngleY = gyroAngleY + (GyroY * (elapsedTime/1000000));
		BluetoothTimer_Reset();

		yaw =  yaw + GyroZ * elapsedTime/1000000;
		roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
		pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;

		CI2C1_SendChar(0x11);
		CI2C1_RecvBlock(mag,6,&recv);

		MagX = (acc[0]<<8 | acc[1]);  // sensitivity values on datasheet
		MagZ = (acc[2]<<8 | acc[3]);
		MagY = (acc[4]<<8 | acc[5]);

		GyroTimer_GetTimeMS(&bluetoothTime);
		if (bluetoothTime >= 1000){
			sendBT(pitch, roll, yaw, MagX, MagY, MagZ, elapsedTime);
			GyroTimer_Reset();
		}

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
