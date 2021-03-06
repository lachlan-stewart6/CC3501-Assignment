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
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
#include "WAIT1.h"
#include "FC322.h"
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
#include <MPU6050.h>
#include <preRecordedData.h>
#include <HMC5883L.h>

/* User includes (#include below this line is not maintained by Processor Expert) */
int16_t data[128]; // 256 bytes;
int data_index=0;

extern char preRecordedData[900];

void printData(){
	Term1_SendStr("XG\tYG\tZG\tXA\tYA\tZA\r\n");
	for(int i=0;i<data_index;i+=6){
		Term1_SendNum(data[i]);
		Term1_SendChar('\t');
		Term1_SendNum(data[i+1]);
		Term1_SendChar('\t');
		Term1_SendNum(data[i+2]);
		Term1_SendChar('\t');
		Term1_SendNum(data[i+3]);
		Term1_SendChar('\t');
		Term1_SendNum(data[i+4]);
		Term1_SendChar('\t');
		Term1_SendNum(data[i+5]);
		Term1_SendStr("\r\n");
	}
}
void setUpFIFO(){
	word sent, recv;

	byte resetDevice[2] = {PWR_MGMT_1, 1<<DEVICE_RESET};
	byte resetFIFO[2] = {USER_CTRL, 1<<FIFO_RESET};
	byte setClock[2] = {PWR_MGMT_1, 1<<CLKSEL};
	byte setDLPF[2] = {CONFIG, 1<<DLPF_BW_180}; //DLPF to make f = 1kHz
	byte set_sample_rate[2] = {SMPRT_DIV, 0};
	byte dataToStore[2] = {FIFO_EN, (1<<XG_FIFO_EN)|(1<<YG_FIFO_EN)|(1<<ZG_FIFO_EN)|(1<<ACCEL_FIFO_EN)}; // tells which registers are being written to the FIFO buffer

	// reset device and FIFO
	CI2C1_SendBlock(resetDevice, 2, &sent);
	CI2C1_SendBlock(resetFIFO, 2, &sent);

	// set frequency to 1kHz
	CI2C1_SendBlock(setClock, 2, &sent);
	CI2C1_SendBlock(setDLPF,2,&sent);
	CI2C1_SendBlock(set_sample_rate,2,&sent);

	// enable FIFO
	CI2C1_SendBlock(dataToStore, 2, &sent);
}
short int getFIFOcount(){
	word recv;
	short int counts, counts_LSB, counts_MSB;
	CI2C1_SendChar(FIFO_COUNT_H);
	CI2C1_RecvBlock(&counts, 2, &recv);
	return counts;
}

void getFIFOData(int counts){
	Term1_SendStr("Starting to read FIFO buffer\r\n");
	word sent, recv;
	byte blocks_12 = counts/12;
	byte extra = counts - blocks_12*12;
	byte readFIFO = 0x74;

	for (int i=0; i<blocks_12; i++){
		CI2C1_SendChar(readFIFO);
		for (int j=0; j<12/2;j++){
			CI2C1_RecvBlock(&data[data_index], 2, &recv);
			data_index++;
		}
	}
	Term1_SendStr("finished getting FIFO data\r\n");
}

void sendBT(float pitch, float roll, float yaw, float MagX, float MagY,
		float MagZ, word elapsedTime) {
	Term1_MoveTo(1,1);
	Term1_SendStr("Pitch: ");
	Term1_SendFloatNum(pitch);
	Term1_SendStr("\r\n");
	Term1_SendStr("Roll: ");
	Term1_SendFloatNum(roll);
	Term1_SendStr("\r\n");
	Term1_SendStr("Yaw: ");
	Term1_SendFloatNum(yaw);
	Term1_SendStr("\r\n");
	Term1_SendStr("MagX: ");
	Term1_SendFloatNum(MagX);
	Term1_SendStr("\r\n");
	Term1_SendStr("MagY: ");
	Term1_SendFloatNum(MagY);
	Term1_SendStr("\r\n");
	Term1_SendStr("MagZ: ");
	Term1_SendFloatNum(MagZ);
	Term1_SendStr("\r\n");
	Term1_SendStr("Time(us): ");
	Term1_SendNum(elapsedTime);
	Term1_SendStr("\r\n");
	Term1_Cls();
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
  	Term1_SendStr("working\r\n\r\n");
	word sent;
	word recv;
	byte response=0;
	byte acc[6];
	byte gyro[6];
	byte mag[6];
	char MPU_ADDR = 0x68;
	char HMC_ADDR = 0x1E;
	float PI = 3.141592654;
	float AccX, AccY, AccZ;
	float accAngleX = 0, accAngleY = 0;
	float GyroX, GyroY, GyroZ;
	float gyroAngleX = 0, gyroAngleY = 0, gyroAngleZ = 0;
	float MagX = 0, MagY = 0, MagZ = 0;
	float yaw = 0, pitch = 0, roll = 0;
	word elapsedTime, bluetoothTime;
	byte enableFIFO[2] = {USER_CTRL, 1<<FIFO_EN_BIT}; // enable FIFO
	byte enableMPU[2]={PWR_MGMT_1, 0};
	byte disableFIFO[2] = {FIFO_EN, 0};  // send 0 to FIFO_en
	byte singleModeHMC[2] = {MODE, 0x01};


	short int FIFO_channels = 6; // 6 short ints (12 bytes) of data being read from the FIFO buffer

	uint16 start, stop, time;
	CI2C1_SendBlock(enableMPU, 2, &sent);// Enable MPU
	CI2C1_SelectSlave(MPU_ADDR);
	// Check connection by reading WHO am I register
	CI2C1_SendChar(WHO_AM_I);
	CI2C1_RecvChar(&response);  // WHO am I register should read 0x68

	char printThing[100];
	sprintf(printThing, "MPU Setup (expecting 104): %i\r\n", response);
	Term1_SendStr(printThing);

	CI2C1_SelectSlave(HMC_ADDR);
	CI2C1_SendBlock(singleModeHMC, 2, &sent); //put mag in single read mode
	/*
	setUpFIFO();
	CI2C1_SendBlock(enableFIFO, 2, &sent); // enable FIFO

	WAIT1_Waitms(3); // wait for 3ms

	CI2C1_SendBlock(disableFIFO, 2, &sent);

	// short int counts = getFIFOcount();
	CI2C1_SendChar(FIFO_COUNT_H);
	CI2C1_RecvBlock(&count1,2,&recv);
	Term1_SendStr("FIFO counts: ");
	Term1_SendNum(count1);
	Term1_SendStr("\r\n");

	// read and print FIFO buffer
	sprintf(printThing, "Read %i short ints from the FIFO buffer (expecting 120)\r\n", count1/2);
	Term1_SendStr(printThing);

	getFIFOData(count1/2);
	printFIFOData();
	 *
	 */
	FC321_Enable();
	Term1_Cls();
	FC321_Reset();
	for(;;){
		// read accelerometer values
		CI2C1_SelectSlave(MPU_ADDR);
		CI2C1_SendChar(ACCEL_XOUT_H);
		CI2C1_RecvBlock(acc,6,&recv);

		AccX = (acc[0]<<8 | acc[1]) / 16384.0;  // sensitivity values on datasheet
		AccY = (acc[2]<<8 | acc[3]) / 16384.0;
		AccZ = (acc[4]<<8 | acc[5]) / 16384.0;

		// calculate pitch and roll from accelerometer
		accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180/PI) - 0.58;
		accAngleY = (atan(-1*AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) *180/PI) + 1.58;

		CI2C1_SendChar(GYRO_XOUT_H);
		CI2C1_RecvBlock(gyro,6,&recv);

		GyroX = ((gyro[0]<<8 | gyro[1]) / 131.0) + 0.56;  // sensitivity values on datasheet
		GyroY = ((gyro[2]<<8 | gyro[3]) / 131.0) - 2;
		GyroZ = ((gyro[4]<<8 | gyro[5]) / 131.0) + 0.79;

		FC321_GetTimeUS(&elapsedTime);
		gyroAngleX = gyroAngleX + (GyroX * (elapsedTime/1000000)); // deg/s * s = deg
		gyroAngleY = gyroAngleY + (GyroY * (elapsedTime/1000000));
		FC321_Reset();

		yaw =  yaw + GyroZ * elapsedTime/1000000;
		roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
		pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
		// https://en.wikipedia.org/wiki/Rotation_matrix
		// https://www.globalsecurity.org/space/library/report/1997/basicnav.pdf

		CI2C1_SelectSlave(HMC_ADDR);
		CI2C1_SendChar(MAG_X_LSB);
		CI2C1_RecvBlock(mag, 6, &recv);

		MagX = (acc[0]<<8 | acc[1]);  // sensitivity values on datasheet
		MagZ = (acc[2]<<8 | acc[3]);
		MagY = (acc[4]<<8 | acc[5]);

		FC322_GetTimeMS(&bluetoothTime);
		if (bluetoothTime >= 1000){
			sendBT(pitch, roll, yaw, MagX, MagY, MagZ, elapsedTime);
			FC322_Reset();
		}

		//sendBT(pitch, roll, yaw, MagX, MagY, MagZ, elapsedTime);
	}
	Term1_SendStr("Finished");


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
