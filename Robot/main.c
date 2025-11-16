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
  * @��  ��  �������������С�����Ƴ���
  * 
  ******************************************************************************
  * @˵  ��
  *
  *  
  ******************************************************************************
  */

#include "stm32f4xx.h"
#include <stdio.h>

#include "ax_robot.h"
#include "ax_tim.h"    

#include "ax_kinematics.h"

/**
  * @��  ��  �����˷�����̼�����
  * @��  ��  ��
  * @����ֵ  ��
  */
void ROBOT_SendDataToRos(void)
{
    //���ڷ�������
	static uint8_t comdata[6]; 	
	
	//�������ٶ�ֵ ��λΪm/s���Ŵ�1000��
	comdata[0] = (u8)( R_Vel.RT_IX >> 8 );
	comdata[1] = (u8)( R_Vel.RT_IX );
	comdata[2] = (u8)( R_Vel.RT_IY >> 8 );
	comdata[3] = (u8)( R_Vel.RT_IY );
	comdata[4] = (u8)( R_Vel.RT_IW >> 8 );
	comdata[5] = (u8)( R_Vel.RT_IW );
	
	//USB���ڷ�������
    AX_UART1_SendPacket(comdata, 6, ID_UTX_DATA);		
}

/**
  * @��  ��  PS2�ֱ����Ƴ���
  * @��  ��  ��
  * @����ֵ  ��
  */
void ROBOT_PS2_Control(void)
{
	static uint8_t speed = 4;  //�����ٶ�
	
	//��ȡPS2�ֱ���ֵ
	AX_PS2_ScanKey(&my_joystick);
	
	//���̵�ģʽ�£�ִ�п��Ʋ���
	if(my_joystick.mode ==  0x73)
	{
		R_Vel.TG_IX = (int16_t)(speed*(0x80 - my_joystick.RJoy_UD));
		R_Vel.TG_IY = (int16_t)(speed*(0x80 - my_joystick.RJoy_LR));
		
		//����ǰ�����������
		#if (ROBOT_TYPE == ROBOT_AKM)
			ax_akm_angle = (int16_t)(4*(0x80 - my_joystick.LJoy_LR));
		#else
			R_Vel.TG_IW = (int16_t)(4*speed*(0x80 - my_joystick.LJoy_LR));
		#endif	
	}
}

/**
  * @��  ��  ����������
  * @��  ��  ��
  * @����ֵ  ��
  */
int main(void)
{
	//�����ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    

	//����ӿڳ�ʼ��
	AX_SERVO_S1_Init();
	AX_SERVO_S2_Init();
	
	//�����ʼ����Ƶ��20KHZ
    AX_MOTOR_InitAll();
    AX_MOTOR_SetZeroMode(MOTOR_ZERO_MODE_COAST);
	
	//��ʱ������ʼ��
	AX_DELAY_Init();  
	
	//LED��ʼ��
	AX_LED_Init();  
	
	//��������ʼ��
	AX_BEEP_Init();    
	
	//���Դ��ڳ�ʼ��
	AX_UART1_Init(230400);
	
	//��������ʼ����
	AX_ENCODER_A_Init();  
	AX_ENCODER_B_Init();  
	AX_ENCODER_C_Init();  
	AX_ENCODER_D_Init(); 
	
	//PS2�ֱ���ʼ��
	AX_PS2_Init();
	
	//��ʱ����ʼ��
	AX_TIM7_Init(20000);//���ö�ʱ�����ڶ�ʱʱ��
    AX_TIM7_Cmd(ENABLE);//��ʱ��ʹ��
	
	while (1)
	{	
		//ִ�����ڣ�20ms��50Hz
		if(AX_TIM7_CheckIrqStatus())
		{
			//PS2�ֱ����ƴ���
			ROBOT_PS2_Control();	
			
			//�������˶�ѧ����
			AX_ROBOT_Kinematics();	

			//��̼����ݷ���
			ROBOT_SendDataToRos();		
			
			//LED��ת
			AX_LED_Green_Toggle();			
		}
	}
}

/******************* (C) ��Ȩ 2023 XTARK *******************************/
