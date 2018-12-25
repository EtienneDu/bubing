#include "main.h"
/**
* @brief Function implementing the MODE_SWITCH_TAS thread.
* @param argument: Not used
* @retval None
*/

extern osTimerId chassisTimerHandle;
extern osTimerId gimbalTimerHandle;
extern osTimerId shootTimerHandle;
uint8_t ctrl_mode = 0;
uint32_t mode_switch_times, Reset= 0;
ramp_mode_ee ramp_mode = RAMP_FLAT;
extern osThreadId GET_CHASSIS_INFHandle;
extern osThreadId GET_GIMBAL_INFHandle;
extern osThreadId GET_SHOOT_INFHandle;

/* USER CODE END Header_info_get_task */
void mode_switch_task(void const * argument)
{
  /* USER CODE BEGIN info_get_task */
	osDelay(1500);
	
	//启动定时器任务，指定定时时间（毫秒）、
	osTimerStart(chassisTimerHandle ,4);
	osTimerStart(gimbalTimerHandle, 1);
	osTimerStart(shootTimerHandle, 1);
	
	uint32_t mode_wake_time = osKernelSysTick();
  /* Infinite loop */
  for(;;)
  {
    /* uint32_t  is :4294967295 ms
								 is :4294967    s
								 is :71582      min
							   is :1193       h
								 is :49         days       */
		mode_switch_times++;
		
		taskENTER_CRITICAL();
		
		get_main_ctrl_mode();
		
		taskEXIT_CRITICAL();
		
		osSignalSet(GET_CHASSIS_INFHandle, INFO_GET_SIGNAL);
		osSignalSet(GET_GIMBAL_INFHandle, GIMBAL_INFO_GET_SIGNAL);
		osSignalSet(GET_SHOOT_INFHandle, SHOOT_GET_SIGNAL);
		osDelayUntil(&mode_wake_time, 5);
		
  }
  /* USER CODE END info_get_task */
}


void get_main_ctrl_mode(void)
{
	static uint32_t last_Reset = 0;
	
	if((RC_CtrlData.rc.s2 == 1) || (RC_CtrlData.rc.s2 == 2))
	{
		ctrl_mode = REMOTE_CTRL;
	}
	else if(RC_CtrlData.rc.s2 == 3)
	{	
		ctrl_mode = KEYBOR_CTRL;
	}
	
	/*遥控无信号，底盘目标输出为0*/
	if(mode_switch_times % 400 == 0)
	{
		if(Reset == last_Reset)
		{
			gim.stop = 1;
		}
		else
		{
			gim.stop = 0;
		}
	}
	if((mode_switch_times %200 == 0)  && (mode_switch_times %400 != 0))
	{
		last_Reset = Reset;
	}
	
	/*遥控无信号，底盘目标输出为0*/
	
	if(moto_pit.total_angle + gyro_data.pitch < -8)
	{
		gim.limit_delay++;
		if(gim.limit_delay > 100)
		{
			ramp_mode = RAMP_UP;
		}
	}
	else if(moto_pit.total_angle + gyro_data.pitch > 8)
	{
		gim.limit_delay++;
		if(gim.limit_delay > 100)
		{
			ramp_mode = RAMP_DOWN;
		}
	}
	else
	{
		gim.limit_delay = 0;
		ramp_mode = RAMP_FLAT;
	}
}


