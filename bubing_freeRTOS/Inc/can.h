#ifndef __can__H
#define __can__H
#include "main.h"
#include "stm32f4xx.h"

/* the ratio of motor encoder value translate to degree */
#define ENCODER_ANGLE_RATIO    (8192.0f/360.0f)
#define CHASSIS_3510 1

/* CAN send and receive ID */
typedef enum
{
	CAN_3510_M1_ID       = 0x201,
  CAN_3510_M2_ID       = 0x202,
	CAN_TRIGGER_MOTOR_ID = 0x203,
	
  CAN_3508_M1_ID       = 0x201,
  CAN_3508_M2_ID       = 0x202,
  CAN_3508_M3_ID       = 0x203,
  CAN_3508_M4_ID       = 0x204,
  CAN_YAW_MOTOR_ID     = 0x205,
  CAN_PIT_MOTOR_ID     = 0x206, 
  
  CAN_CHASSIS_ALL_ID   = 0x200,
  CAN_GIMBAL_ALL_ID    = 0x1ff,

} can_msg_id_e;

/* can receive motor parameter structure */
#define FILTER_BUF 5
typedef struct
{
  uint16_t ecd;                            //���������������ԭʼֵ
  uint16_t last_ecd;                       //��һ�εı��������������ԭʼֵ
  
  int16_t  speed_rpm;                      //ͨ������������õ���ת��ԭʼֵ
  int16_t  given_current;                  //ͨ������������õ��ĵ������ԭʼֵ

  int32_t  round_cnt;                      //���Ȧ��
  int32_t  total_ecd;                      //��������������ı�����ֵ
  float  total_angle;                      //����Ƕ�
	float  last_total_angle;								 //����ϴνǶ�
  
  uint16_t offset_ecd;										//��ʼ������ֵ
  uint32_t msg_cnt;                       //������
  
  int32_t  ecd_raw_rate;                  //ͨ������������õ��Ľ��ٶ�ԭʼֵ
  int32_t  rate_buf[FILTER_BUF];          //buf��for filter
  uint8_t  buf_cut;                       //������
  int32_t  filter_rate;                   //���ٶ�
	int32_t  last_filter_rate;              //�ϴν��ٶ�
} moto_measure_t;

typedef struct
{
	int16_t raw_pitch;           //δ�������pit�Ƕ�
	int16_t raw_roll;            //δ�������roll�Ƕ�
	int16_t raw_yaw;             //δ�������yaw�Ƕ�
	
	int16_t raw_v_x;             //δ�������x����ٶ�
	int16_t raw_v_y;             //δ�������y����ٶ�
	int16_t raw_v_z;             //δ�������z����ٶ�
	
	
	
	float pitch;                 //������pit�Ƕ�
	float roll;                  //������roll�Ƕ�
	float yaw;                   //������yaw�Ƕ�
	float	last_yaw;
	
	float pitch_angle;           //�Լ�ȥ������
	float last_pitch_angle;      //�Լ�ȥ������
	
	float yaw_angle;             //�Լ�ȥ������
	float last_yaw_angle;        //�Լ�ȥ������
	
	float v_x;                   //δ�������x����ٶ�
	float v_y;                   //δ�������y����ٶ�
	float v_z;                   //δ�������z����ٶ�
}	GYRO_DATA;

typedef struct
{
  uint16_t ecd;                            //���������������ԭʼֵ
  uint16_t last_ecd;                       //��һ�εı��������������ԭʼֵ
  
  int16_t  speed_rpm;                      //ͨ������������õ���ת��ԭʼֵ
  int16_t  given_current;                  //ͨ������������õ��ĵ������ԭʼֵ

  int32_t  round_cnt;                      //���Ȧ��
  int32_t  total_ecd;                      //��������������ı�����ֵ
  float  total_angle;                      //����Ƕ�
	float  last_total_angle;								 //����ϴνǶ�
  
  uint16_t offset_ecd;										//��ʼ������ֵ
  uint32_t msg_cnt;                       //������
  
  int32_t  ecd_raw_rate;                  //ͨ������������õ��Ľ��ٶ�ԭʼֵ
  int32_t  rate_buf[25];          	//buf��for filter
  uint8_t  buf_cut;                       //������
  int32_t  filter_rate;                   //���ٶ�
	int32_t  last_filter_rate;              //�ϴν��ٶ�
} shoot_moto_measure_t;

extern moto_measure_t moto_chassis[];
extern moto_measure_t moto_yaw, moto_pit, moto_trigger;
extern shoot_moto_measure_t moto_friction[2];
extern moto_measure_t moto_trigger;
extern GYRO_DATA gyro_data;


void MX_CAN1_Init(void);
void MX_CAN2_Init(void);
void send_chassis_cur(int16_t a,int16_t b,int16_t c,int16_t d);
void send_gimbal_cur(int16_t yaw_iq, int16_t pit_iq, int16_t trigger_iq);
void send_shoot_cur(int16_t iq1, int16_t iq2, int16_t iq3);
void encoder_data_handler(moto_measure_t* ptr, uint8_t Data[]);
void encoder_data_handler1(moto_measure_t* ptr, uint8_t Data[]);
void encoder_data_handler2(shoot_moto_measure_t* ptr, uint8_t Data[]);
void get_moto_offset(moto_measure_t* ptr, uint8_t Data[]);
void zitai_data_receive(GYRO_DATA* gyro,uint8_t Data[]);
void zitai_data_receive2 (GYRO_DATA* gyro,uint8_t Data[]);
void gyro_data_receive(GYRO_DATA* gyro,uint8_t Data[]);




#endif

