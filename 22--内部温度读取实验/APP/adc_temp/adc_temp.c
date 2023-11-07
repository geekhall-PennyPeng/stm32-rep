#include "adc.h"
#include "adc_temp.h"
#include "SysTick.h"
#include "usart.h"


int Get_Temperature_Value(void)
{
    u16 adc_value=0;
    double vol,temperate;
    int result;
    
    adc_value=(float)Get_ADC_Value(ADC_CHANNEL_16,10);
    vol=3.3/4096*adc_value;
    temperate=((vol-0.76)/0.0025)+25;
    result=temperate*100;
    return result;
}
