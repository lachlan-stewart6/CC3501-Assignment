/* ###################################################################
**     Filename    : mqx_tasks.c
**     Project     : 87686
**     Processor   : MK20DX128VMC7
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-10-24, 13:51, # CodeGen: 22
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         AccelData_task - void AccelData_task(uint32_t task_init_data);
**         GyroData_task - void GyroData_task(uint32_t task_init_data);
**         MagData_task - void MagData_task(uint32_t task_init_data);
**         SendBluetooth_task - void SendBluetooth_task(uint32_t task_init_data);
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

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  AccelData_task (module mqx_tasks)
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
void AccelData_task(uint32_t task_init_data)
{
  int counter = 0;

  while(1) {
    counter++;

    /* Write your code here ... */

  }
}

/*
** ===================================================================
**     Event       :  GyroData_task (module mqx_tasks)
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
void GyroData_task(uint32_t task_init_data)
{
  int counter = 0;

  while(1) {
    counter++;

    /* Write your code here ... */

  }
}

/*
** ===================================================================
**     Event       :  MagData_task (module mqx_tasks)
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
void MagData_task(uint32_t task_init_data)
{
  int counter = 0;

  while(1) {
    counter++;

    /* Write your code here ... */

  }
}

/*
** ===================================================================
**     Event       :  SendBluetooth_task (module mqx_tasks)
**
**     Component   :  Task4 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void SendBluetooth_task(uint32_t task_init_data)
{
  int counter = 0;

  while(1) {
    counter++;

    /* Write your code here ... */

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
