#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

osThreadId defaultTaskHandle;
osThreadId GET_CHASSIS_INFHandle;
osThreadId GET_GIMBAL_INFHandle;
osThreadId GET_SHOOT_INFHandle;
osThreadId canTaskHandle;
osThreadId infoTaskHandle;
osTimerId chassisTimerHandle;
osTimerId gimbalTimerHandle;
osTimerId shootTimerHandle;

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init()
{
	taskENTER_CRITICAL();
	
	/* Create the timer(s) */
  /* definition and creation of chassisTimer */
  osTimerDef(chassisTimer, chassis_task);
  chassisTimerHandle = osTimerCreate(osTimer(chassisTimer), osTimerPeriodic, NULL);
	
	osTimerDef(gimTimer, gimbal_task);
	gimbalTimerHandle =  osTimerCreate(osTimer(gimTimer),   osTimerPeriodic, NULL);
	
	osTimerDef(shootTimer, shoot_task);
	shootTimerHandle =  osTimerCreate(osTimer(shootTimer),   osTimerPeriodic, NULL);
	
	
	/* Create the thread(s) */
  
	/* high priority task */
  /* definition and creation of canTask */
  osThreadDef(canTask, can_send_task, osPriorityAboveNormal, 0, 256);
  canTaskHandle = osThreadCreate(osThread(canTask), NULL);
	
	/* definition and creation of GET_CHASSIS_INF */
  osThreadDef(GET_CHASSIS_INF, Get_Chassis_Info, osPriorityAboveNormal, 0, 256);
  GET_CHASSIS_INFHandle = osThreadCreate(osThread(GET_CHASSIS_INF), NULL);
	
	/* definition and creation of GET_GIMBAL_INF */
  osThreadDef(GET_GIMBAL_INF, Get_Gimbal_Info, osPriorityAboveNormal, 0, 256);
  GET_GIMBAL_INFHandle = osThreadCreate(osThread(GET_GIMBAL_INF), NULL);
	
	/* definition and creation of GET_SHOOT_INF */
  osThreadDef(GET_SHOOT_INF, Get_Shoot_Info, osPriorityAboveNormal, 0, 256);
  GET_SHOOT_INFHandle = osThreadCreate(osThread(GET_SHOOT_INF), NULL);
	
	
	/* low priority task */
  /* definition and creation of mode_switch_Task */
  osThreadDef(mode_switch_Task, mode_switch_task, osPriorityNormal, 0, 256);
  infoTaskHandle = osThreadCreate(osThread(mode_switch_Task), NULL);
	
	/* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
	
	/* unpack task */
	
	taskEXIT_CRITICAL();
	
}


/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */ 
}



/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
