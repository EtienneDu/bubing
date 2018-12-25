#include "main.h"

/* communicate task global parameter */
motor_current_t glb_cur;



void can_send_task(void const *argument)
{
	osEvent event;
	for(;;)
	{
		event = osSignalWait(CHASSIS_MOTOR_MSG_SEND     | \
		                     GIMBAL_MOTOR_MSG_SEND      | \
		                      SHOOT_MOTOR_MSG_SEND, osWaitForever);
		if (event.status == osEventSignal)
		{
			if(event.value.signals & CHASSIS_MOTOR_MSG_SEND)
			{
				send_chassis_motor_ctrl_message(glb_cur.chassis_cur);
			}
			else if(event.value.signals & GIMBAL_MOTOR_MSG_SEND)
			{
				send_gimbal_motor_ctrl_message(glb_cur.gimbal_cur);
			}
			else if(event.value.signals & SHOOT_MOTOR_MSG_SEND)
			{
				send_shoot_motor_ctrl_message(glb_cur.shoot_cur);
			}
		}
//		printf("CAN∑¢ÀÕ»ŒŒÒ£°");
//		printf("%d\t",*glb_cur.gimbal_cur);
	}
}


