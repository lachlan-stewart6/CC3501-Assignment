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
#include "WAIT1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"

/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "MPU6050.h"
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

  byte enable[]={0x6B, 0};
  byte reset_device[]={PWR_MGMT_1, 1<<DEVICE_RESET};
  byte fifo_reset[]={USER_CTRL, 1<<FIFO_RESET};
  byte set_clock[]={PWR_MGMT_1, PLL_X<<CLKSEL};
  byte set_DLPF[]={CONFIG, DLPF_BW_100<<DLPF_CONFIG};
  byte set_sample_rate[]={SMPRT_DIV, 0};
  byte data_to_store[]={FIFO_EN, (1<<XG_FIFO_EN)|(1<<YG_FIFO_EN)|(1<<ZG_FIFO_EN)|(1<<ACCEL_FIFO_EN)};

  byte enable_fifo[]={USER_CTRL, 1<<FIFO_EN_BIT};
  byte disable_fifo[]={FIFO_EN, 0};


  CI2C1_SendBlock(enable, 2, &snt);// Enable MPU
  //CI2C1_SendBlock(reset_device,2,&snt);
  CI2C1_SendBlock(fifo_reset,2,&snt);
  // Check connection by reading WHO am I register
  CI2C1_SendChar(WHO_AM_I);
  CI2C1_RecvChar(&response);  // WHO am I register should read 0x68


  byte count1[2]={0};
  byte count2[2]={0};

  CI2C1_SendBlock(set_clock,2,&snt);
  CI2C1_SendBlock(set_DLPF,2,&snt);
  CI2C1_SendBlock(set_sample_rate,2,&snt);
  CI2C1_SendBlock(data_to_store,2,&snt);

  CI2C1_SendBlock(enable_fifo,2,&snt);
  WAIT1_Waitms(3);

  CI2C1_SendBlock(disable_fifo,2,&snt);

  CI2C1_SendChar(FIFO_COUNT_H);
  CI2C1_RecvBlock(&count1,2,&rcv);

  WAIT1_Waitms(3);

  CI2C1_SendChar(FIFO_COUNT_H);
  CI2C1_RecvBlock(&count2,2,&rcv);

  WAIT1_Waitms(3);



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
