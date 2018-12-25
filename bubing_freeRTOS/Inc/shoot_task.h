#ifndef __SHOOT_TASK_H__
#define __SHOOT_TASK_H__

#include "main.h"

#define		SHOOT_BUFF       6
#define   FIVEFOLD_HEAT    0x100
#define 	ON							 1
#define   OFF							 0
#define   Lv_3						 3
#define   Lv_2						 2

//关于摩擦轮的结构体
typedef __packed struct
{
  /* trigger motor param */
  uint8_t  switching;
	uint8_t	 mode;
	
	float    shoot_fact_speed;
	float    shoot_buff_angle;
	
	float 	 fric_wheel_spd_ref[2];
	float    fric_wheel_spd_fdb[2];
	
	uint8_t  shoot_speed_high;
} fric_t;

//关于拨盘的结构体
typedef __packed struct
{
  /* trigger motor param */
  int32_t    spd_ref;
	int32_t    max_ref;
  int32_t    pos_ref;
	
	float      trig_spd;
	float   	 trig_pos;
  
	uint8_t    switching;
	uint8_t		 mode;
	uint32_t	 delay;
} trigger_t;

//射击状态的结构体
typedef __packed struct
{
  /* trigger motor param */
	uint8_t			mode;
	uint8_t			get_pos;
	
	uint8_t    	level;
	uint16_t   	heat;
	uint16_t   	hp;
	uint16_t    buff;
	
  fric_t      fric;
	trigger_t   trig;
} shoot_t;

extern shoot_t shoot;


void shoot_task(void const *argument);
void shoot_remote_handler(void);
void Shoot_Param_Init(void);


#endif

