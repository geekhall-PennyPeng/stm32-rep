#include "led.h"


/*******************************************************************************
* �� �� ��         : LED_Init
* ��������		   : LED��ʼ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	LED1_PROT_RCC_ENABLE;//ʹ��LED1 GPIO�˿�ʱ��
    LED2_PROT_RCC_ENABLE;//ʹ��LED2 GPIO�˿�ʱ��
	
	GPIO_InitStructure.Pin=LED1_GPIO_PIN; //PF9,10 
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_InitStructure.Pull=GPIO_PULLUP;          //����
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(LED1_PROT,&GPIO_InitStructure);
    
    GPIO_InitStructure.Pin=LED2_GPIO_PIN; //PF9,10 
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(LED2_PROT,&GPIO_InitStructure);
	
	HAL_GPIO_WritePin(LED1_PROT,LED1_GPIO_PIN,GPIO_PIN_SET);	//PF9��1��Ĭ�ϳ�ʼ�������
    HAL_GPIO_WritePin(LED2_PROT,LED2_GPIO_PIN,GPIO_PIN_SET);	//PF10��1��Ĭ�ϳ�ʼ�������
}
