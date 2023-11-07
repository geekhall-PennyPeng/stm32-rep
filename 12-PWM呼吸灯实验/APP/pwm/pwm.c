#include "pwm.h"

TIM_HandleTypeDef TIM14_Handler;
TIM_OC_InitTypeDef TIM14_CH1_Handler;

void TIM14_CH1_PWM_Init(u16 per, u16 psc)
{  
    TIM14_Handler.Instance=TIM14;
    TIM14_Handler.Init.Prescaler=psc;//
    TIM14_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//�ߵ�ƽ��Ч
    TIM14_Handler.Init.Period=per;
    TIM14_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//����Ƶ
    HAL_TIM_PWM_Init(&TIM14_Handler);//��ʼ��
    TIM14_CH1_Handler.OCMode=TIM_OCMODE_PWM1;//����PWMģʽ
    TIM14_CH1_Handler.Pulse=per/2;
    TIM14_CH1_Handler.OCPolarity=TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&TIM14_Handler,&TIM14_CH1_Handler,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&TIM14_Handler,TIM_CHANNEL_1);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //ʹ�ܶ�ʱ��������˿�
    __HAL_RCC_GPIOF_CLK_ENABLE();
    //��ʼ����ʱ��14
    __HAL_RCC_TIM14_CLK_ENABLE();
    GPIO_InitStructure.Pin=GPIO_PIN_9; //�����������
    GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;//����Ϊ����ģʽ
    GPIO_InitStructure.Pull=GPIO_PULLUP;//����ģʽ
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;//����ģʽ
    GPIO_InitStructure.Alternate=GPIO_AF9_TIM14;//����Ϊ��ʱ��14
    HAL_GPIO_Init(GPIOF,&GPIO_InitStructure);//��ʼ��GPIO    
}
void TIM14_SetCompare1(u32 compare)
{
    TIM14->CCR1=compare;
}
