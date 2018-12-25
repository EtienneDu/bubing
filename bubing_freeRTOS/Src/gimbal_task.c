#include "main.h"
#include "math.h"

/* gimbal task global parameter */
gimbal_t gim;

uint32_t handler_run_time = 0;

extern ramp_t pit_ramp;
extern ramp_t yaw_ramp;
extern osThreadId canTaskHandle;
extern osThreadId GET_CHASSIS_INFHandle;
extern osThreadId GET_GIMBAL_INFHandle;

static  uint16_t ppidp ,ppidi ,ppidd ,spidp ,spidi ,spidd = 0;

void gimbal_task(void const * argument)
{
	handler_run_time++;
//	gimbal_time_ms = HAL_GetTick() - gimbal_time_last;
//	gimbal_time_last = HAL_GetTick();

	/* gimbal mode switch */
	 switch (gim.ctrl_mode)
	{
		case GIMBAL_INIT:
			init_mode_handler();
		break;
		
		case GIMBAL_NORMAL:
			normal_mode_handler();
		break;
		
		case GIMBAL_WRITHE:
			normal_mode_handler();
		break;
		
		default:
		break;
	}
	/* gimbal pit and yaw position pid */
//	pid_pit.p = ppidp;
//	pid_pit.i = ppidi;
//	pid_pit.d = ppidd;
	
	pid_calc(&pid_yaw, gim.pid.yaw_angle_fdb, gim.pid.yaw_angle_ref);
	pid_calc(&pid_pit, gim.pid.pit_angle_fdb, gim.pid.pit_angle_ref);
	
	gim.pid.yaw_spd_ref = pid_yaw.out;
	gim.pid.pit_spd_ref = pid_pit.out;
	
//	gim.pid.yaw_spd_ref = 20;
//	gim.pid.pit_spd_ref = 20;
 
	/* gimbal pid and yaw speed pid */
	gim.pid.yaw_spd_fdb = gim.sensor.yaw_palstance;
	gim.pid.pit_spd_fdb = gim.sensor.pit_palstance;


	
//	pid_pit_spd.p = spidp;
//	pid_pit_spd.i = spidi;
//	pid_pit_spd.d = spidd;
	
	pid_calc(&pid_yaw_spd, gim.pid.yaw_spd_fdb, gim.pid.yaw_spd_ref);
	pid_calc(&pid_pit_spd, gim.pid.pit_spd_fdb, gim.pid.pit_spd_ref);

	/* gimbal current out */
	glb_cur.gimbal_cur[0] = pid_yaw_spd.out;
	glb_cur.gimbal_cur[1] = pid_pit_spd.out;
	glb_cur.gimbal_cur[2] = 0;
	
	osSignalSet(GET_GIMBAL_INFHandle, GIMBAL_INFO_GET_SIGNAL);
	osSignalSet(canTaskHandle, GIMBAL_MOTOR_MSG_SEND);
	
	
	
/*************************************����**********************************************/	
//	printf("��̨����\t");
//	printf("%d\t",glb_cur.gimbal_cur[0]);
//  Ni_Ming(0xf1,gim.pid.yaw_spd_ref,gim.pid.yaw_spd_fdb,pid_yaw_spd.out,0);
/***************************************************************************************/	
}

void init_mode_handler(void)
{
	gim.pid.pit_angle_fdb = gim.sensor.pit_relative_angle;
  gim.pid.yaw_angle_fdb = gim.sensor.yaw_relative_angle;
	gim.pid.pit_angle_ref = 0;
	gim.pid.yaw_angle_ref = 0;
	if(handler_run_time > 2000)
	{
		gim.ctrl_mode = GIMBAL_NORMAL;
	}
}

void normal_mode_handler(void)
{
	gim.pid.pit_angle_fdb = gim.sensor.pit_relative_angle;
  gim.pid.yaw_angle_fdb = gim.sensor.yaw_relative_angle;
}


void Gimbal_Param_Init(void)
{
	memset(&gim, 0, sizeof(gimbal_t));
	
	gim.ctrl_mode 		 = GIMBAL_INIT;
	gim.last_ctrl_mode = GIMBAL_INIT;
	
	/* pitch and yaw ramp Initializa */
	ramp_init(&pit_ramp, PIT_PREPARE_TIMS_MS);
	ramp_init(&yaw_ramp, YAW_PREPARE_TIMS_MS);
	
	/* pitch axis motor pid parameter */
  PID_struct_init(&pid_pit, POSITION_PID, 1000, 1000,
                  30, 0, 0); //30
  PID_struct_init(&pid_pit_spd, POSITION_PID, 6000, 2000,
                  60, 0, 0); //60

  /* yaw axis motor pid parameter */
  PID_struct_init(&pid_yaw, POSITION_PID, 1000, 1000,
                  20, 0, 0); //8
  PID_struct_init(&pid_yaw_spd, POSITION_PID, 6000, 2000,
                  60, 0, 0);//60   2
}





