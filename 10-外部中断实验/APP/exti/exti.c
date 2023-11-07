#include "exti.h"
#include "key.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"

void EXTI_Init(void)
{
    //设置引脚功能  
    GPIO_InitTypeDef GPIO_InitStructure;   
    //KEY_UP
    KEY_UP_PROT_RCC_ENABLE;
    GPIO_InitStructure.Pin=KEY_UP_GPIO_PIN;
    GPIO_InitStructure.Mode=GPIO_MODE_IT_RISING; //上升沿触发
    GPIO_InitStructure.Pull=GPIO_PULLDOWN; //设置下拉电阻
    HAL_GPIO_Init(KEY_UP_PROT,&GPIO_InitStructure);
    //KEY0-KEY2
    KEY0_PROT_RCC_ENABLE;
    KEY1_PROT_RCC_ENABLE;
    KEY2_PROT_RCC_ENABLE;
    GPIO_InitStructure.Pin=KEY0_GPIO_PIN|KEY1_GPIO_PIN|KEY2_GPIO_PIN;
    GPIO_InitStructure.Mode=GPIO_MODE_IT_FALLING; //下降沿触发
    GPIO_InitStructure.Pull=GPIO_PULLUP; //设置上拉电阻
    HAL_GPIO_Init(GPIOE,&GPIO_InitStructure);
    
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);//设置中断
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);//中断使能
    
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);//设置中断
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);//中断使能  
    
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);//设置中断
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);//中断使能
    
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,3);//设置中断
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);//中断使能
}
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_UP_GPIO_PIN);
}
void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY2_GPIO_PIN);
}
void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_GPIO_PIN);
}
void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_GPIO_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(10);
    switch(GPIO_Pin)
    {
        case KEY_UP_GPIO_PIN:
            if(KEY_UP) LED1=!LED1;
            break;
        case KEY0_GPIO_PIN:
            if(!KEY0) LED2=!LED2;
            break;
        case KEY1_GPIO_PIN:
            if(!KEY1) BEEP=!BEEP;
            break;
        case KEY2_GPIO_PIN:
            if(!KEY2) LED_Init();
            BEEP_Init();
            break;
    }
}
