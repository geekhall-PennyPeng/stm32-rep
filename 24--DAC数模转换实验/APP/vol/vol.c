#include "vol.h"
#include "adc.h"

ADC_HandleTypeDef Vol_Handler;

void Vol_Init(void)
{
    Vol_Handler.Instance=ADC1;//ADC基地址
    Vol_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;//4分频 84/4=21MHZ
    Vol_Handler.Init.Resolution=ADC_RESOLUTION_12B;//分辨率设置为12
    Vol_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;//数据右对齐
    Vol_Handler.Init.ScanConvMode=DISABLE;//扫描模式 关闭
    Vol_Handler.Init.EOCSelection=DISABLE;//关闭轮询中断标志
    Vol_Handler.Init.ContinuousConvMode=DISABLE;//关闭外部触发
    Vol_Handler.Init.NbrOfConversion=1;//顺序器排名数量设置为1
    Vol_Handler.Init.DiscontinuousConvMode=DISABLE;//不连续模式
    Vol_Handler.Init.NbrOfDiscConversion=0;
    Vol_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;//设置触发极性为软件触发
    Vol_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//禁用外部触发
    Vol_Handler.Init.DMAContinuousRequests=DISABLE;//禁用DMA
    
    HAL_ADC_Init(&Vol_Handler);//初始化ADC
    HAL_ADC_Start(&Vol_Handler);//开启ADC
}

u16 Get_Vol_Adc_Value(void)
{
    Get_ADC_Value(&Vol_Handler,ADC_CHANNEL_5, 10);
}