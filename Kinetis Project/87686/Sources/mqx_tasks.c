/* ###################################################################
**     Filename    : mqx_tasks.c
**     Project     : 87686
**     Processor   : MK20DX128VMC7
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-10-24, 16:38, # CodeGen: 31
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         bing_task - void bing_task(uint32_t task_init_data);
**         bang_task - void bang_task(uint32_t task_init_data);
**         blop_task - void blop_task(uint32_t task_init_data);
**
** ###################################################################*/
/*!
** @file mqx_tasks.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup mqx_tasks_module mqx_tasks module documentation
**  @{
*/         
/* MODULE mqx_tasks */

#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"
#include "main.h"
#include "ICM20948.h"
#include "math.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
extern MessageQueue msg_queue;
float PI = 3.141592654;
/*
** ===================================================================
**     Event       :  bing_task (module mqx_tasks)
**
**     Component   :  Task1 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void bing_task(uint32_t task_init_data)
{

	word sent, recv;
	static Message msg;

	while (1){
	CI2C1_SelectSlave(ICM_ADDR);  // select accel and gyro device
	CI2C1_SendChar(ACCEL_XOUT_H);
	CI2C1_RecvBlock(msg.acc,6,&recv);

	msg.AccX = ((msg.acc[0]<<8 | msg.acc[1])/16384.0)*9.81;  // sensitivity values on datasheet
	msg.AccY = ((msg.acc[2]<<8 | msg.acc[3])/16384.0)*9.81;
	msg.AccZ = ((msg.acc[4]<<8 | msg.acc[5])/16384.0)*9.81;

	// calculate pitch and roll from accelerometer
	msg.accAngleX = (atan(msg.AccY / sqrt(pow(msg.AccX, 2) + pow(msg.AccZ, 2))) * 180/PI) - 0.58;
	msg.accAngleY = (atan(-1*msg.AccX / sqrt(pow(msg.AccY, 2) + pow(msg.AccZ, 2))) *180/PI) + 1.58;

	CI2C1_SendChar(GYRO_XOUT_H);
	CI2C1_RecvBlock(msg.gyro,6,&recv);

	msg.GyroX = (msg.gyro[0]<<8 | msg.gyro[1])/131.0;  // sensitivity values on datasheet
	msg.GyroY = (msg.gyro[2]<<8 | msg.gyro[3])/131.0;
	msg.GyroZ = (msg.gyro[4]<<8 | msg.gyro[5])/131.0;

	GyroTimer_GetTimeUS(&msg.elapsedTime);
	msg.gyroAngleX = msg.gyroAngleX + (msg.GyroX * (msg.elapsedTime/1000000)); // deg/s * s = deg
	msg.gyroAngleY = msg.gyroAngleY + (msg.GyroY * (msg.elapsedTime/1000000));
	GyroTimer_Reset();

	msg.yaw =  msg.yaw + msg.GyroZ * msg.elapsedTime/1000000;
	msg.roll = 0.96 * msg.gyroAngleX + 0.04 * msg.accAngleX;  // compliemtary filter
	msg.pitch = 0.96 * msg.gyroAngleY + 0.04 * msg.accAngleY;

	_lwmsgq_send(&msg_queue, (void*)&msg,
	    LWMSGQ_SEND_BLOCK_ON_FULL);
	_time_delay_ticks(20);
	}
}

/*
** ===================================================================
**     Event       :  bang_task (module mqx_tasks)
**
**     Component   :  Task2 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void bang_task(uint32_t task_init_data)
{
	static Message msg;
		word sent, recv;
		while (1){
		CI2C1_SelectSlave(MAG_ADDR);  // select magnetometer device

		CI2C1_SendChar(MAG_XOUT_H);
		CI2C1_RecvBlock(msg.mag,6,&recv);

		msg.MagX = (msg.mag[0]<<8 | msg.mag[1])*0.15;  // sensitivity values on datasheet
		msg.MagZ = (msg.mag[2]<<8 | msg.mag[3])*0.15;
		msg.MagY = (msg.mag[4]<<8 | msg.mag[5])*0.15;

		_lwmsgq_send(&msg_queue, (void*)&msg,
		    LWMSGQ_SEND_BLOCK_ON_FULL);
		_time_delay_ticks(20);
		}
}

/*
** ===================================================================
**     Event       :  blop_task (module mqx_tasks)
**
**     Component   :  Task3 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void blop_task(uint32_t task_init_data)
{
	static Message msg;
	while (1){
		BluetoothTimer_GetTimeMS(&msg.bluetoothTime);
		if (msg.bluetoothTime >= 1000){
			Bluetooth_Term_MoveTo(1,1);
			Bluetooth_Term_SendStr("Test MQX");
			Bluetooth_Term_SendStr("Pitch: ");
			Bluetooth_Term_SendNum(msg.pitch);
			Bluetooth_Term_SendStr("\r\n");
			Bluetooth_Term_SendStr("Roll: ");
			Bluetooth_Term_SendNum(msg.roll);
			Bluetooth_Term_SendStr("\r\n");
			Bluetooth_Term_SendStr("Yaw: ");
			Bluetooth_Term_SendNum(msg.yaw);
			Bluetooth_Term_SendStr("\r\n");
			Bluetooth_Term_SendStr("MagX: ");
			Bluetooth_Term_SendNum(msg.MagX);
			Bluetooth_Term_SendStr("\r\n");
			Bluetooth_Term_SendStr("MagY: ");
			Bluetooth_Term_SendNum(msg.MagY);
			Bluetooth_Term_SendStr("\r\n");
			Bluetooth_Term_SendStr("MagZ: ");
			Bluetooth_Term_SendNum(msg.MagZ);
			Bluetooth_Term_SendStr("\r\n");
			Bluetooth_Term_SendStr("Time(us): ");
			Bluetooth_Term_SendNum(msg.elapsedTime);
			Bluetooth_Term_SendStr("\r\n");

			BluetoothTimer_Reset();
		}
	}
}

/* END mqx_tasks */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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