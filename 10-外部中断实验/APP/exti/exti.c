#include "exti.h"
#include "key.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"

void EXTI_Init(void)
{
    //�������Ź���  
    GPIO_InitTypeDef GPIO_InitStructure;   
    //KEY_UP
    KEY_UP_PROT_RCC_ENABLE;
    GPIO_InitStructure.Pin=KEY_UP_GPIO_PIN;
    GPIO_InitStructure.Mode=GPIO_MODE_IT_RISING; //�����ش���
    GPIO_InitStructure.Pull=GPIO_PULLDOWN; //������������
    HAL_GPIO_Init(KEY_UP_PROT,&GPIO_InitStructure);
    //KEY0-KEY2
    KEY0_PROT_RCC_ENABLE;
    KEY1_PROT_RCC_ENABLE;
    KEY2_PROT_RCC_ENABLE;
    GPIO_InitStructure.Pin=KEY0_GPIO_PIN|KEY1_GPIO_PIN|KEY2_GPIO_PIN;
    GPIO_InitStructure.Mode=GPIO_MODE_IT_FALLING; //�½��ش���
    GPIO_InitStructure.Pull=GPIO_PULLUP; //������������
    HAL_GPIO_Init(GPIOE,&GPIO_InitStructure);
    
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);//�����ж�
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);//�ж�ʹ��
    
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);//�����ж�
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);//�ж�ʹ��  
    
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);//�����ж�
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);//�ж�ʹ��
    
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,3);//�����ж�
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);//�ж�ʹ��
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
