#include "adc.h"
#include "adc_temp.h"
#include "SysTick.h"
#include "usart.h"

ADC_HandleTypeDef Temp_Handler;

void Temp_Init(void)
{
    Temp_Handler.Instance=ADC1;//ADC基地址
    Temp_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;//4分频 84/4=21MHZ
    Temp_Handler.Init.Resolution=ADC_RESOLUTION_12B;//分辨率设置为12
    Temp_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;//数据右对齐
    Temp_Handler.Init.ScanConvMode=DISABLE;//扫描模式 关闭
    Temp_Handler.Init.EOCSelection=DISABLE;//关闭轮询中断标志
    Temp_Handler.Init.ContinuousConvMode=DISABLE;//关闭外部触发
    Temp_Handler.Init.NbrOfConversion=1;//顺序器排名数量设置为1
    Temp_Handler.Init.DiscontinuousConvMode=DISABLE;//不连续模式
    Temp_Handler.Init.NbrOfDiscConversion=0;
    Temp_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;//设置触发极性为软件触发
    Temp_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//禁用外部触发
    Temp_Handler.Init.DMAContinuousRequests=DISABLE;//禁用DMA
    
    HAL_ADC_Init(&Temp_Handler);//初始化ADC
    HAL_ADC_Start(&Temp_Handler);//开启ADC
}

int Get_Temperature_Value(void)
{
    u16 adc_value=0;
    double vol,temperate;
    int result;
    
    adc_value=(float)Get_ADC_Value(&Temp_Handler,ADC_CHANNEL_16,10);
    vol=3.3/4096*adc_value;
    temperate=((vol-0.76)/0.0025)+25;
    result=temperate*100;
    return result;
}
