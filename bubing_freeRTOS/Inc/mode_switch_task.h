#ifndef __mode_switch_task__H
#define __mode_switch_task__H
#include "main.h"

#define 	REMOTE_CTRL				1			
#define 	KEYBOR_CTRL				3
typedef enum
{
  RAMP_FLAT = 0,
	RAMP_UP   = 1,
	RAMP_DOWN = 2,
} ramp_mode_ee;

void mode_switch_task(void const * argument);
void get_main_ctrl_mode(void);

extern ramp_mode_ee ramp_mode;
extern uint8_t ctrl_mode;
extern uint32_t Reset;

#endif


