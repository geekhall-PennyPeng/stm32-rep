#include "adc.h"
#include "SysTick.h"
#include "usart.h"

ADC_HandleTypeDef ADC1_Handler;

void ADC1_Init(ADC_TypeDef *Instance)
{
    ADC1_Handler.Instance=Instance;//ADC基地址
    ADC1_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;//4分频 84/4=21MHZ
    ADC1_Handler.Init.Resolution=ADC_RESOLUTION_12B;//分辨率设置为12
    ADC1_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;//数据右对齐
    ADC1_Handler.Init.ScanConvMode=DISABLE;//扫描模式 关闭
    ADC1_Handler.Init.EOCSelection=DISABLE;//关闭轮询中断标志
    ADC1_Handler.Init.ContinuousConvMode=DISABLE;//关闭外部触发
    ADC1_Handler.Init.NbrOfConversion=1;//顺序器排名数量设置为1
    ADC1_Handler.Init.DiscontinuousConvMode=DISABLE;//不连续模式
    ADC1_Handler.Init.NbrOfDiscConversion=0;
    ADC1_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;//设置触发极性为软件触发
    ADC1_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//禁用外部触发
    ADC1_Handler.Init.DMAContinuousRequests=DISABLE;//禁用DMA
    
    HAL_ADC_Init(&ADC1_Handler);//初始化ADC
    HAL_ADC_Start(&ADC1_Handler);//开启ADC
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance==ADC1)
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        __HAL_RCC_ADC1_CLK_ENABLE();//使能ADC时钟
        __HAL_RCC_GPIOA_CLK_ENABLE();//使能GPIOA时钟
        
        GPIO_InitStructure.Pin=ADC1_GPIO_PIN; //PA5 
        GPIO_InitStructure.Mode=GPIO_MODE_ANALOG;  //模拟输入
        GPIO_InitStructure.Pull=GPIO_NOPULL;          //不使用上拉
        HAL_GPIO_Init(ADC1_PROT,&GPIO_InitStructure);//初始化GPIO 
    }
    else if(hadc->Instance==ADC3)
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        __HAL_RCC_ADC3_CLK_ENABLE();//使能ADC时钟
        __HAL_RCC_GPIOF_CLK_ENABLE();//使能GPIOA时钟
        
        GPIO_InitStructure.Pin=ADC3_GPIO_PIN; //PA5 
        GPIO_InitStructure.Mode=GPIO_MODE_ANALOG;  //模拟输入
        GPIO_InitStructure.Pull=GPIO_NOPULL;          //不使用上拉
        HAL_GPIO_Init(ADC3_PROT,&GPIO_InitStructure);//初始化GPIO
    }
}

u16 Get_Adc(ADC_HandleTypeDef* ADC_Handler,u32 ch)
{
    ADC_ChannelConfTypeDef ADC_ChannelConf;
    
    ADC_ChannelConf.Channel=ch;
    ADC_ChannelConf.Rank=1;
    ADC_ChannelConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;
    ADC_ChannelConf.Offset=0;
    HAL_ADC_ConfigChannel(ADC_Handler,&ADC_ChannelConf);
    
    HAL_ADC_Start(ADC_Handler);//开启ADC
    HAL_ADC_PollForConversion(ADC_Handler,10);
    return (u16)HAL_ADC_GetValue(ADC_Handler);
}

u16 Get_ADC_Value(ADC_HandleTypeDef* ADC_Handler,u32 ch, u8 times)
{
    u32 temp_val=0;
    u8 t=0;
    for(t=0;t<times;t++)
    {
        temp_val+=Get_Adc(ADC_Handler,ch);
        delay_ms(5);
    }
    return (u16)temp_val/times;
}




