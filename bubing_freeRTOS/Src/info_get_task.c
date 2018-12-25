#include "main.h"
#include "cmsis_os.h"

uint32_t info_time_last;
int info_time_ms;

/* USER CODE BEGIN Header_info_get_task */
/**
* @brief Function implementing the infoTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_info_get_task */
void info_get_task(void const * argument)
{
  /* USER CODE BEGIN info_get_task */
	osEvent event;
  /* Infinite loop */
  for(;;)
  {
    event = osSignalWait(INFO_GET_SIGNAL, osWaitForever);
		if(event.status == osEventSignal)
		{
			if(event.value.signals & INFO_GET_SIGNAL)
			{
				info_time_ms = HAL_GetTick() - info_time_last;
				info_time_last = HAL_GetTick();
				
				taskENTER_CRITICAL();
				
				Get_Chassis_Info();
				
				taskENTER_CRITICAL();
				
			}
		}
  }
  /* USER CODE END info_get_task */
}


