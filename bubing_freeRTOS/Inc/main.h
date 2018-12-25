

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif


#define ture true
#define flase false
#define mian main
	
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_tim_ex.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_dma.h"
#include "FreeRTOS.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "can_msg_send_task.h"
#include "info_get_task.h"
#include "mode_switch_task.h"
#include "common_task.h"
#include "chassis_task.h"
#include "get_chassis_info.h"
#include "gimbal_task.h"
#include "get_gimbal_info.h"
#include "shoot_task.h"
#include "get_shoot_info.h"
#include "cmsis_os.h"
#include "can.h"
#include "usart.h"
#include "pid.h"
#include "ramp.h"
#include "niming.h"
	
	
	
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
