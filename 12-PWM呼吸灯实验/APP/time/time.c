#include "time.h"
#include "LED.h"

TIM_HandleTypeDef TIM3_Handler;

void TIM3_Init(u16 per,u16 psc)
{
    TIM3_Handler.Instance=TIM3;//��ƶ�ʱ���ӿ�
    TIM3_Handler.Init.Prescaler=psc;//�����Զ�װ��ֵ
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//��������
    TIM3_Handler.Init.Period=per;//��Ƶϵ��
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    
    HAL_TIM_Base_Init(&TIM3_Handler);//��ʼ��
    HAL_TIM_Base_Start_IT(&TIM3_Handler);//������ʱ���ж�
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();//ʱ��ʹ��
        HAL_NVIC_SetPriority(TIM3_IRQn,1,3);//�����ж���ռ����Ӧ���ȼ�
        HAL_NVIC_EnableIRQ(TIM3_IRQn);//�����ж�
    }
}

void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
    {
        LED1=!LED1;
    }
}
