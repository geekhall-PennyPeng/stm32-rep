#include "input.h"

TIM_HandleTypeDef TIM5_Handler;

void TIM5_CH1_Input_Init(u32 arr,u16 psc)
{
    TIM_IC_InitTypeDef TIM_CH1;
    
    TIM5_Handler.Instance=TIM5;
    TIM5_Handler.Init.Prescaler=psc; //设置预分配值
    TIM5_Handler.Init.Period=arr;//设置预装值
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP ;//设置为上升沿捕获
	TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //设置为不分频
    HAL_TIM_IC_Init(&TIM5_Handler);
    //配置IC时钟通道

    TIM_CH1.ICPolarity=TIM_ICPOLARITY_RISING;//上升沿触发
    TIM_CH1.ICSelection=TIM_ICSELECTION_DIRECTTI; //映射选择 直连模式
    TIM_CH1.ICFilter=0X00;//不启用滤波器
    HAL_TIM_IC_ConfigChannel(&TIM5_Handler,&TIM_CH1,TIM_CHANNEL_1);//配置CI时钟
    HAL_TIM_IC_Start_IT(&TIM5_Handler,TIM_CHANNEL_1);//开启定时器、捕获通道、中断
    __HAL_TIM_ENABLE_IT(&TIM5_Handler,TIM_IT_UPDATE);//开启溢出更新
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{  
    GPIO_InitTypeDef GPIO_InitStructure;
    
    __HAL_RCC_TIM5_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitStructure.Pin=GPIO_PIN_0; //PF0
    GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;  //服用推挽输出
    GPIO_InitStructure.Pull=GPIO_PULLDOWN;          //下拉
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //高速
    GPIO_InitStructure.Alternate=GPIO_AF2_TIM5; //定时器5模式
    HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO
    HAL_NVIC_SetPriority(TIM5_IRQn,2,0);//设置中断优先级
    HAL_NVIC_EnableIRQ(TIM5_IRQn);//使能中断
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
            TIM5_CH1_CAPTURE_STA|=0X80;//成功捕获高电平
            TIM5_CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM5_Handler,TIM_CHANNEL_1);
            TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);//复位捕获极性
            TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//设置捕获极性
        }
        else
        {
            TIM5_CH1_CAPTURE_STA=0;//状态清零
            TIM5_CH1_CAPTURE_VAL=0;//数值清零
            TIM5_CH1_CAPTURE_STA|=0X40;//修改为下降沿触发
            __HAL_TIM_DISABLE(&TIM5_Handler);//关闭定时器            
            __HAL_TIM_SET_COUNTER(&TIM5_Handler,0);//计数器值清零
            TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);//复位捕获极性
            TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//设置捕获极性
            __HAL_TIM_ENABLE(&TIM5_Handler);//使能定时器
        }
    }
}
