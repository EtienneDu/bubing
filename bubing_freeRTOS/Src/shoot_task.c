#include "main.h"
#include "math.h"

/* shoot task global parameter */
shoot_t shoot = {0};

extern osThreadId canTaskHandle;
extern osThreadId GET_SHOOT_INFHandle;


//�����ʱ����
void shoot_task(void const * argument)
{
		if(gim.ctrl_mode != GIMBAL_INIT)
		{
				switch (shoot.mode)
				{
					case REMOTE_CTRL:
						shoot_remote_handler();
					break;
					default:
						break;
				}
				if(shoot.heat > shoot.trig.max_ref)
				{shoot.trig.spd_ref = 0;}
				
				glb_cur.shoot_cur[0] = chassis_pid_calc(&pid_fric_spd[0], shoot.fric.fric_wheel_spd_fdb[0], -shoot.fric.fric_wheel_spd_ref[0] * 28.571248f);    //28.571248f��ʾʲô��
				glb_cur.shoot_cur[1] = chassis_pid_calc(&pid_fric_spd[1], shoot.fric.fric_wheel_spd_fdb[1],  shoot.fric.fric_wheel_spd_ref[1] * 28.571248f);
				glb_cur.shoot_cur[2] = chassis_pid_calc(&pid_trigger_spd, shoot.trig.trig_spd, shoot.trig.spd_ref);
				
				osSignalSet(GET_SHOOT_INFHandle, SHOOT_GET_SIGNAL);
				osSignalSet(canTaskHandle, SHOOT_MOTOR_MSG_SEND);
				
//				printf("�����ʱ����");
		}
}


void shoot_remote_handler(void)
{
	if(shoot.fric.switching == ON)
	{
		shoot.trig.delay++;
		shoot.trig.max_ref = 88888;
		shoot.fric.fric_wheel_spd_ref[0] = shoot.fric.fric_wheel_spd_ref[1] = 15;		
		if(shoot.trig.delay > 1000)
		{
			shoot.trig.spd_ref = -6;
		}
	}
	else
	{	
		shoot.trig.delay = 0;
		shoot.trig.spd_ref = 0;
		shoot.fric.fric_wheel_spd_ref[0] = shoot.fric.fric_wheel_spd_ref[1] = 0;	
	}
}

void Shoot_Param_Init(void)
{
		 for (int k = 0; k < 2; k++)
  {
    PID_struct_init(&pid_fric_spd[k], POSITION_PID, 10000, 7000,
		150, 3, 0); 
	}
	
	shoot.trig.max_ref = 100;
	 /* bullet trigger motor pid parameter */
  PID_struct_init(&pid_trigger, POSITION_PID, 30, 2000,
                  0.5, 0, 0);
  PID_struct_init(&pid_trigger_spd, POSITION_PID, 10000, 5000,
                  1200, 2, 0);
}


