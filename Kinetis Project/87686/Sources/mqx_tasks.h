/* ###################################################################
**     Filename    : mqx_tasks.h
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
** @file mqx_tasks.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup mqx_tasks_module mqx_tasks module documentation
**  @{
*/         

#ifndef __mqx_tasks_H
#define __mqx_tasks_H
/* MODULE mqx_tasks */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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
#include "MQX1.h"
#include "SystemTimer1.h"

#ifdef __cplusplus
extern "C" {
#endif 

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
void bing_task(uint32_t task_init_data);

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
void bang_task(uint32_t task_init_data);

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
void blop_task(uint32_t task_init_data);


/* END mqx_tasks */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __mqx_tasks_H*/
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
