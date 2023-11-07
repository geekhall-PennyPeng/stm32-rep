#include "time.h"
#include "LED.h"

TIM_HandleTypeDef TIM3_Handler;

void TIM3_Init(u16 per,u16 psc)
{
    TIM3_Handler.Instance=TIM3;//设计定时器接口
    TIM3_Handler.Init.Prescaler=psc;//设置自动装配值
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//上升计数
    TIM3_Handler.Init.Period=per;//分频系数
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    
    HAL_TIM_Base_Init(&TIM3_Handler);//初始化
    HAL_TIM_Base_Start_IT(&TIM3_Handler);//开启定时器中断
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();//时钟使能
        HAL_NVIC_SetPriority(TIM3_IRQn,1,3);//设置中断抢占、响应优先级
        HAL_NVIC_EnableIRQ(TIM3_IRQn);//开启中断
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
