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

/* Includes ------------------------------------------------------------------*/
#include "ax_speed.h"
#include "ax_robot.h"


/**
  * @��  ��  ���PID���ƺ���
  * @��  ��  spd_target:�������ٶ�Ŀ��ֵ ,��Χ����250��
  *          spd_current: �������ٶȵ�ǰֵ
  * @����ֵ  ���PWM�ٶ�
  */
int16_t AX_SPEED_PidCtlA(float spd_target, float spd_current)
{
	static int16_t motor_pwm_out;
	static float bias,bias_last;

	//���ƫ��ֵ
	bias = spd_target - spd_current;
	
	//PID���������PWMֵ
	motor_pwm_out += ax_motor_kp*bias + ax_motor_kd*(bias-bias_last);
	
	//��¼�ϴ�ƫ��
	bias_last = bias;
	
	//����������
    if(motor_pwm_out > MOTOR_PWM_PERIOD)
        motor_pwm_out = MOTOR_PWM_PERIOD;
    if(motor_pwm_out < -MOTOR_PWM_PERIOD)
        motor_pwm_out = -MOTOR_PWM_PERIOD;
	
	//����PWM����ֵ
	return motor_pwm_out;
}	

/**
  * @��  ��  ���PID���ƺ���
  * @��  ��  spd_target:�������ٶ�Ŀ��ֵ 
  *          spd_target: �������ٶȵ�ǰֵ
  * @����ֵ  ���PWM�ٶ�
  */
int16_t AX_SPEED_PidCtlB(float spd_target, float spd_current)
{
	static int16_t motor_pwm_out;
	static float bias,bias_last;

	//���ƫ��ֵ
	bias = spd_target - spd_current;
	
	//PID���������PWMֵ
	motor_pwm_out += ax_motor_kp*bias + ax_motor_kd*(bias-bias_last);
	
	//��¼�ϴ�ƫ��
	bias_last = bias;
	
	//����������
    if(motor_pwm_out > MOTOR_PWM_PERIOD)
        motor_pwm_out = MOTOR_PWM_PERIOD;
    if(motor_pwm_out < -MOTOR_PWM_PERIOD)
        motor_pwm_out = -MOTOR_PWM_PERIOD;
	
	//����PWM����ֵ
	return motor_pwm_out;
}

/**
  * @��  ��  ���PID���ƺ���
  * @��  ��  spd_target:�������ٶ�Ŀ��ֵ 
  *          spd_target: �������ٶȵ�ǰֵ
  * @����ֵ  ���PWM�ٶ�
  */
int16_t AX_SPEED_PidCtlC(float spd_target, float spd_current)
{
	static int16_t motor_pwm_out;
	static float bias,bias_last;

	//���ƫ��ֵ
	bias = spd_target - spd_current;
	
	//PID���������PWMֵ
	motor_pwm_out += ax_motor_kp*bias + ax_motor_kd*(bias-bias_last);
	
	//��¼�ϴ�ƫ��
	bias_last = bias;
	
	//����������
    if(motor_pwm_out > MOTOR_PWM_PERIOD)
        motor_pwm_out = MOTOR_PWM_PERIOD;
    if(motor_pwm_out < -MOTOR_PWM_PERIOD)
        motor_pwm_out = -MOTOR_PWM_PERIOD;
	
	//����PWM����ֵ
	return motor_pwm_out;
}

/**
  * @��  ��  ���PID���ƺ���
  * @��  ��  spd_target:�������ٶ�Ŀ��ֵ 
  *          spd_target: �������ٶȵ�ǰֵ
  * @����ֵ  ���PWM�ٶ�
  */
int16_t AX_SPEED_PidCtlD(float spd_target, float spd_current)
{
	static int16_t motor_pwm_out;
	static float bias,bias_last;

	//���ƫ��ֵ
	bias = spd_target - spd_current;
	
	//PID���������PWMֵ
	motor_pwm_out += ax_motor_kp*bias + ax_motor_kd*(bias-bias_last);
	
	//��¼�ϴ�ƫ��
	bias_last = bias;
	
	//����������
    if(motor_pwm_out > MOTOR_PWM_PERIOD)
        motor_pwm_out = MOTOR_PWM_PERIOD;
    if(motor_pwm_out < -MOTOR_PWM_PERIOD)
        motor_pwm_out = -MOTOR_PWM_PERIOD;
	
	//����PWM����ֵ
	return motor_pwm_out;
}


/******************* (C) ��Ȩ 2023 XTARK **************************************/

