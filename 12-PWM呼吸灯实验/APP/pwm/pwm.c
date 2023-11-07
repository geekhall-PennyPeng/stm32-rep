#include "pwm.h"

TIM_HandleTypeDef TIM14_Handler;
TIM_OC_InitTypeDef TIM14_CH1_Handler;

void TIM14_CH1_PWM_Init(u16 per, u16 psc)
{  
    TIM14_Handler.Instance=TIM14;
    TIM14_Handler.Init.Prescaler=psc;//
    TIM14_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//高电平有效
    TIM14_Handler.Init.Period=per;
    TIM14_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//不分频
    HAL_TIM_PWM_Init(&TIM14_Handler);//初始化
    TIM14_CH1_Handler.OCMode=TIM_OCMODE_PWM1;//设置PWM模式
    TIM14_CH1_Handler.Pulse=per/2;
    TIM14_CH1_Handler.OCPolarity=TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&TIM14_Handler,&TIM14_CH1_Handler,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&TIM14_Handler,TIM_CHANNEL_1);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //使能定时器与输出端口
    __HAL_RCC_GPIOF_CLK_ENABLE();
    //初始化定时器14
    __HAL_RCC_TIM14_CLK_ENABLE();
    GPIO_InitStructure.Pin=GPIO_PIN_9; //设置输出引脚
    GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;//设置为推挽模式
    GPIO_InitStructure.Pull=GPIO_PULLUP;//上拉模式
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;//高速模式
    GPIO_InitStructure.Alternate=GPIO_AF9_TIM14;//设置为定时器14
    HAL_GPIO_Init(GPIOF,&GPIO_InitStructure);//初始化GPIO    
}
void TIM14_SetCompare1(u32 compare)
{
    TIM14->CCR1=compare;
}
