#include "lsens.h"
#include "adc.h"
ADC_HandleTypeDef ADC3_Handler;

void Lsens_Init(void)
{
    ADC3_Handler.Instance=ADC3;//ADC基地址
    ADC3_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;//4分频 84/4=21MHZ
    ADC3_Handler.Init.Resolution=ADC_RESOLUTION_12B;//分辨率设置为12
    ADC3_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;//数据右对齐
    ADC3_Handler.Init.ScanConvMode=DISABLE;//扫描模式 关闭
    ADC3_Handler.Init.EOCSelection=DISABLE;//关闭轮询中断标志
    ADC3_Handler.Init.ContinuousConvMode=DISABLE;//关闭外部触发
    ADC3_Handler.Init.NbrOfConversion=1;//顺序器排名数量设置为1
    ADC3_Handler.Init.DiscontinuousConvMode=DISABLE;//不连续模式
    ADC3_Handler.Init.NbrOfDiscConversion=0;
    ADC3_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;//设置触发极性为软件触发
    ADC3_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//禁用外部触发
    ADC3_Handler.Init.DMAContinuousRequests=DISABLE;//禁用DMA
    
    HAL_ADC_Init(&ADC3_Handler);//初始化ADC
    HAL_ADC_Start(&ADC3_Handler);//开启ADC
}

u8 Lsens_Get_Value(void)
{
    u16 adc_value=0;
    double light_value;
    
    adc_value=(float)Get_ADC_Value(&ADC3_Handler,ADC_CHANNEL_5,10);
    if(adc_value>4000) adc_value=4000;
    
    light_value=(u8)(100-adc_value/40);
    return light_value;
}
