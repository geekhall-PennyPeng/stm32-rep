#include "input.h"

TIM_HandleTypeDef TIM5_Handler;

void TIM5_CH1_Input_Init(u32 arr,u16 psc)
{
    TIM_IC_InitTypeDef TIM_CH1;
    
    TIM5_Handler.Instance=TIM5;
    TIM5_Handler.Init.Prescaler=psc; //����Ԥ����ֵ
    TIM5_Handler.Init.Period=arr;//����Ԥװֵ
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP ;//����Ϊ�����ز���
	TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //����Ϊ����Ƶ
    HAL_TIM_IC_Init(&TIM5_Handler);
    //����ICʱ��ͨ��

    TIM_CH1.ICPolarity=TIM_ICPOLARITY_RISING;//�����ش���
    TIM_CH1.ICSelection=TIM_ICSELECTION_DIRECTTI; //ӳ��ѡ�� ֱ��ģʽ
    TIM_CH1.ICFilter=0X00;//�������˲���
    HAL_TIM_IC_ConfigChannel(&TIM5_Handler,&TIM_CH1,TIM_CHANNEL_1);//����CIʱ��
    HAL_TIM_IC_Start_IT(&TIM5_Handler,TIM_CHANNEL_1);//������ʱ��������ͨ�����ж�
    __HAL_TIM_ENABLE_IT(&TIM5_Handler,TIM_IT_UPDATE);//�����������
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{  
    GPIO_InitTypeDef GPIO_InitStructure;
    
    __HAL_RCC_TIM5_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitStructure.Pin=GPIO_PIN_0; //PF0
    GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;  //�����������
    GPIO_InitStructure.Pull=GPIO_PULLDOWN;          //����
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //����
    GPIO_InitStructure.Alternate=GPIO_AF2_TIM5; //��ʱ��5ģʽ
    HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIO
    HAL_NVIC_SetPriority(TIM5_IRQn,2,0);//�����ж����ȼ�
    HAL_NVIC_EnableIRQ(TIM5_IRQn);//ʹ���ж�
}

void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM5_Handler);
}

u8 TIM5_CH1_CAPTURE_STA=0;
u32 TIM5_CH1_CAPTURE_VAL=0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if((TIM5_CH1_CAPTURE_STA&0X80)==0)
    {
        if(TIM5_CH1_CAPTURE_STA&0X40)
        {
            if((TIM5_CH1_CAPTURE_VAL&0X3F)==0X3F)
            {
                TIM5_CH1_CAPTURE_STA|=0X80;
                TIM5_CH1_CAPTURE_VAL=0XFFFFFFFF;
            }
            TIM5_CH1_CAPTURE_VAL++;
        }
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if((TIM5_CH1_CAPTURE_STA&0X80)==0)
    {
        if(TIM5_CH1_CAPTURE_STA&0X40)
        {
            TIM5_CH1_CAPTURE_STA|=0X80;//�ɹ�����ߵ�ƽ
            TIM5_CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM5_Handler,TIM_CHANNEL_1);
            TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);//��λ������
            TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//���ò�����
        }
        else
        {
            TIM5_CH1_CAPTURE_STA=0;//״̬����
            TIM5_CH1_CAPTURE_VAL=0;//��ֵ����
            TIM5_CH1_CAPTURE_STA|=0X40;//�޸�Ϊ�½��ش���
            __HAL_TIM_DISABLE(&TIM5_Handler);//�رն�ʱ��            
            __HAL_TIM_SET_COUNTER(&TIM5_Handler,0);//������ֵ����
            TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);//��λ������
            TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//���ò�����
            __HAL_TIM_ENABLE(&TIM5_Handler);//ʹ�ܶ�ʱ��
        }
    }
}
