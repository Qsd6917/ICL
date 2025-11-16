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
  * @��  ��  ���PWM���ƺ���
  *
  ******************************************************************************
  * @˵  ��
  *
  ******************************************************************************
  */

#include "ax_motor.h" 

/**
  * @��  ��  ���PWM���Ƴ�ʼ����PWMƵ��Ϊ20KHZ	
  * @��  ��  ��
  * @����ֵ  ��
  */
void AX_MOTOR_AB_Init(void)
{ 
	
    GPIO_InitTypeDef GPIO_InitStructure; 

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure; 
	
	//ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	

	//���ù�������
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1); 
	
	//����IO��Ϊ���ù���-��ʱ��ͨ��
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
    GPIO_Init(GPIOE, &GPIO_InitStructure);

	//��ʱ������
    TIM_TimeBaseStructure.TIM_Period=MOTOR_PWM_PERIOD-1;   //�Զ���װ��ֵ 
	TIM_TimeBaseStructure.TIM_Prescaler=1;     //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    //PWM1 Mode configuration: Channel1 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;	    //ռ�ձȳ�ʼ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    //PWM1 Mode configuration: Channel2
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

    //PWM1 Mode configuration: Channel3
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    //PWM1 Mode configuration: Channel4
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM1, ENABLE);

    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM1, ENABLE);   
	
	//ʹ��MOEλ
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
}

/**
  * @��  �� ���PWM�ٶȿ���
  * @��  �� speed ���ת����ֵ����Χ-4200~4200
  * @����ֵ ��
  */
void AX_MOTOR_A_SetSpeed(int16_t speed)
{
    int16_t temp;
    
    temp = speed;
    
    if(temp>MOTOR_PWM_PERIOD)
        temp = MOTOR_PWM_PERIOD;
    if(temp<-MOTOR_PWM_PERIOD)
        temp = -MOTOR_PWM_PERIOD;
    
    if(temp > 0)
    {
        TIM_SetCompare1(TIM1, MOTOR_PWM_PERIOD);
        TIM_SetCompare2(TIM1, (MOTOR_PWM_PERIOD - temp));
    }
    else if(temp < 0)
    {
        TIM_SetCompare2(TIM1, MOTOR_PWM_PERIOD);
        TIM_SetCompare1(TIM1, (MOTOR_PWM_PERIOD + temp));
    }
    else
    {
        if(MOTOR_ZERO_MODE == MOTOR_ZERO_MODE_BRAKE)
        {
            TIM_SetCompare1(TIM1, MOTOR_PWM_PERIOD);
            TIM_SetCompare2(TIM1, MOTOR_PWM_PERIOD);
        }
        else
        {
            TIM_SetCompare1(TIM1, 0);
            TIM_SetCompare2(TIM1, 0);
        }
    }
}


/**
  * @��  �� ���PWM�ٶȿ���
  * @��  �� speed ���ת����ֵ����Χ-4200~4200
  * @����ֵ ��
  */
void AX_MOTOR_B_SetSpeed(int16_t speed)
{
    int16_t temp;
    
    temp = speed;
    
    if(temp>MOTOR_PWM_PERIOD)
        temp = MOTOR_PWM_PERIOD;
    if(temp<-MOTOR_PWM_PERIOD)
        temp = -MOTOR_PWM_PERIOD;
    
    if(temp > 0)
    {
        TIM_SetCompare3(TIM1, MOTOR_PWM_PERIOD);
        TIM_SetCompare4(TIM1, (MOTOR_PWM_PERIOD - temp));
    }
    else if(temp < 0)
    {
        TIM_SetCompare4(TIM1, MOTOR_PWM_PERIOD);
        TIM_SetCompare3(TIM1, (MOTOR_PWM_PERIOD + temp));
    }
    else
    {
        if(MOTOR_ZERO_MODE == MOTOR_ZERO_MODE_BRAKE)
        {
            TIM_SetCompare3(TIM1, MOTOR_PWM_PERIOD);
            TIM_SetCompare4(TIM1, MOTOR_PWM_PERIOD);
        }
        else
        {
            TIM_SetCompare3(TIM1, 0);
            TIM_SetCompare4(TIM1, 0);
        }
    }
}


/**
  * @��  ��  ���PWM���Ƴ�ʼ����PWMƵ��Ϊ20KHZ	
  * @��  ��  ��
  * @����ֵ  ��
  */
void AX_MOTOR_CD_Init(void)
{ 
	
    GPIO_InitTypeDef GPIO_InitStructure; 
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure; 
	
	//ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);	

	//���ù�������
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);
	
	//����IO��Ϊ���ù���-��ʱ��ͨ��
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
    GPIO_Init(GPIOE, &GPIO_InitStructure);

	//��ʱ������ 
    TIM_TimeBaseStructure.TIM_Period=MOTOR_PWM_PERIOD-1;   //�Զ���װ��ֵ 
	TIM_TimeBaseStructure.TIM_Prescaler=1;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

    //PWM1 Mode configuration: Channel1 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;	    //ռ�ձȳ�ʼ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	
    TIM_OC1Init(TIM9, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);

    //PWM1 Mode configuration: Channel2
    TIM_OC2Init(TIM9, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM9, ENABLE);

    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM9, ENABLE);   
	
	
	//ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);	

	//���ù�������
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12);/*����*/
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);/*����*/
	

	//����IO��Ϊ���ù���-��ʱ��ͨ��
	GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_UP;        //����
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	//��ʱ������
    TIM_TimeBaseStructure.TIM_Period=MOTOR_PWM_PERIOD-1;   //�Զ���װ��ֵ 
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);

    //PWM1 Mode configuration: Channel1 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;	    //ռ�ձȳ�ʼ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	
    TIM_OC1Init(TIM12, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);

    //PWM1 Mode configuration: Channel2
    TIM_OC2Init(TIM12, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM12, ENABLE);	

    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM12, ENABLE);   
}

/**
  * @��  �� ���PWM�ٶȿ���
  * @��  �� speed ���ת����ֵ����Χ-4200~4200
  * @����ֵ ��
  */
void AX_MOTOR_C_SetSpeed(int16_t speed)
{
    int16_t temp;
    
    temp = speed;
    
    if(temp>MOTOR_PWM_PERIOD)
        temp = MOTOR_PWM_PERIOD;
    if(temp<-MOTOR_PWM_PERIOD)
        temp = -MOTOR_PWM_PERIOD;
    
    if(temp > 0)
    {
        TIM_SetCompare1(TIM9, MOTOR_PWM_PERIOD);
        TIM_SetCompare2(TIM9, (MOTOR_PWM_PERIOD - temp));
    }
    else if(temp < 0)
    {
        TIM_SetCompare2(TIM9, MOTOR_PWM_PERIOD);
        TIM_SetCompare1(TIM9, (MOTOR_PWM_PERIOD + temp));
    }
    else
    {
        if(MOTOR_ZERO_MODE == MOTOR_ZERO_MODE_BRAKE)
        {
            TIM_SetCompare1(TIM9, MOTOR_PWM_PERIOD);
            TIM_SetCompare2(TIM9, MOTOR_PWM_PERIOD);
        }
        else
        {
            TIM_SetCompare1(TIM9, 0);
            TIM_SetCompare2(TIM9, 0);
        }
    }
    
}


/**
  * @��  �� ���PWM�ٶȿ���
  * @��  �� speed ���ת����ֵ����Χ-4200~4200
  * @����ֵ ��
  */
void AX_MOTOR_D_SetSpeed(int16_t speed)
{
    int16_t temp;
    
    temp = speed;
    
    if(temp>MOTOR_PWM_PERIOD)
        temp = MOTOR_PWM_PERIOD;
    if(temp<-MOTOR_PWM_PERIOD)
        temp = -MOTOR_PWM_PERIOD;
    
    if(temp > 0)
    {
        TIM_SetCompare1(TIM12, MOTOR_PWM_PERIOD);
        TIM_SetCompare2(TIM12, (MOTOR_PWM_PERIOD - temp));
    }
    else if(temp < 0)
    {
        TIM_SetCompare2(TIM12, MOTOR_PWM_PERIOD);
        TIM_SetCompare1(TIM12, (MOTOR_PWM_PERIOD + temp));
    }
    else
    {
        if(MOTOR_ZERO_MODE == MOTOR_ZERO_MODE_BRAKE)
        {
            TIM_SetCompare1(TIM12, MOTOR_PWM_PERIOD);
            TIM_SetCompare2(TIM12, MOTOR_PWM_PERIOD);
        }
        else
        {
            TIM_SetCompare1(TIM12, 0);
            TIM_SetCompare2(TIM12, 0);
        }
    }
}


/******************* (C) ��Ȩ 2023 XTARK **************************************/
