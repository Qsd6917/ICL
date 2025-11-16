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
  * @��  ��  ���˴����Ŷ�
  * @��  ��  ����������PID�ٶȿ���
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_SPEED_H
#define __AX_SPEED_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f4xx.h"
#include "ax_motor.h"

//���PID�ջ��ٶȿ��ƺ���
int16_t AX_SPEED_PidCtlA(float spd_target, float spd_current);   //PID���ƺ��������A
int16_t AX_SPEED_PidCtlB(float spd_target, float spd_current);    //PID���ƺ��������B
int16_t AX_SPEED_PidCtlC(float spd_target, float spd_current);    //PID���ƺ��������C
int16_t AX_SPEED_PidCtlD(float spd_target, float spd_current);    //PID���ƺ��������D


#endif

/******************* (C) ��Ȩ 2023 XTARK **************************************/
