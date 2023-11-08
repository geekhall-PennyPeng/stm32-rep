#include "dac.h"

DAC_HandleTypeDef DAC_Handler;

void DAC1_Init(void)
{  
    DAC_ChannelConfTypeDef DACCH1_Config;
    DAC_Handler.Instance=DAC;//配置基地址
    HAL_DAC_Init(&DAC_Handler);//初始化DAC
    
    DACCH1_Config.DAC_Trigger=DAC_TRIGGER_NONE;//不使用触发源
    DACCH1_Config.DAC_OutputBuffer=DAC_OUTPUTBUFFER_DISABLE;//不使用输出缓存
    HAL_DAC_ConfigChannel(&DAC_Handler,&DACCH1_Config,DAC_CHANNEL_1);
    
    HAL_DAC_Start(&DAC_Handler,DAC_CHANNEL_1);
}

void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{

        GPIO_InitTypeDef GPIO_InitStructure;
        __HAL_RCC_DAC_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        GPIO_InitStructure.Pin=GPIO_PIN_4; //PA5 
        GPIO_InitStructure.Mode=GPIO_MODE_ANALOG;  //模拟输入
        GPIO_InitStructure.Pull=GPIO_NOPULL;          //不使用上拉
        HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO 

} 
//vol 0-3300
void Set_DAC_Vol(u16 vol)
{
    float voltage = (float)vol / 3300.0;
    u32 data = (u32)(voltage * 4095);
    HAL_DAC_SetValue(&DAC_Handler, DAC_CHANNEL_1, DAC_ALIGN_12B_R, data);
}


u32 Get_DAC_Value(void)
{
    return HAL_DAC_GetValue(&DAC_Handler,DAC_CHANNEL_1);
}
