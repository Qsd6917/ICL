/**			                                                    
		   ____                    _____ _______ _____       XTARK@���˴���
		  / __ \                  / ____|__   __|  __ \ 
		 | |  | |_ __   ___ _ __ | |       | |  | |__) |
		 | |  | | '_ \ / _ \ '_ \| |       | |  |  _  / 
		 | |__| | |_) |  __/ | | | |____   | |  | | \ \ 
		  \____/| .__/ \___|_| |_|\_____|  |_|  |_|  \_\
				| |                                     
				|_|                OpenCTR   �����˿�����
									 
  ****************************************************************************** 
  *           
  * ��Ȩ���У� XTARK@���˴���  ��Ȩ���У�����ؾ�
  * ��˾��վ�� www.xtark.cn   www.tarkbot.com
  * �Ա����̣� https://xtark.taobao.com  
  * ����΢�ţ� ���˴��£���ע���ںţ���ȡ���¸�����Ѷ��
  *      
  ******************************************************************************
  * @��  ��  Musk Han@XTARK
  * @��  ��  V1.0
  * @��  ��  ���PWM���ƺ���
  *
  ******************************************************************************
  * @˵  ��
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_MOTOR_H
#define __AX_MOTOR_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

#ifndef MOTOR_DRV_TB6612
#define MOTOR_DRV_TB6612 1
#endif
#ifndef MOTOR_DRV_AT8236
#define MOTOR_DRV_AT8236 2
#endif
#ifndef MOTOR_DRIVER
#define MOTOR_DRIVER MOTOR_DRV_TB6612
#endif

#ifndef MOTOR_ZERO_MODE_BRAKE
#define MOTOR_ZERO_MODE_BRAKE 1
#endif
#ifndef MOTOR_ZERO_MODE_COAST
#define MOTOR_ZERO_MODE_COAST 2
#endif
#ifndef MOTOR_ZERO_MODE
#define MOTOR_ZERO_MODE MOTOR_ZERO_MODE_BRAKE
#endif

#ifndef MOTOR_PWM_PERIOD
#define MOTOR_PWM_PERIOD 4200
#endif

//X-SOFT �ӿں���
void AX_MOTOR_AB_Init(void); //���PWM���Ƴ�ʼ��
void AX_MOTOR_A_SetSpeed(int16_t speed);   //���A����
void AX_MOTOR_B_SetSpeed(int16_t speed);   //���B����

void AX_MOTOR_CD_Init(void); //���PWM���Ƴ�ʼ��
void AX_MOTOR_C_SetSpeed(int16_t speed);   //���C����
void AX_MOTOR_D_SetSpeed(int16_t speed);   //���D����

void AX_MOTOR_InitAll(void);
void AX_MOTOR_SetSpeeds(int16_t a, int16_t b, int16_t c, int16_t d);
void AX_MOTOR_SetZeroMode(uint8_t mode);
extern uint8_t ax_motor_zero_mode;
void AX_MOTOR_SafeStop(void);

#endif

/******************* (C) ��Ȩ 2023 XTARK **************************************/
