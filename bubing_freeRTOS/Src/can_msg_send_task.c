#include "main.h"
#include "cmsis_os.h"



/* USER CODE BEGIN Header_can_msg_send_task */
/**
* @brief Function implementing the canTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_can_msg_send_task */
void can_msg_send_task(void const * argument)
{
  /* USER CODE BEGIN can_msg_send_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END can_msg_send_task */
}

