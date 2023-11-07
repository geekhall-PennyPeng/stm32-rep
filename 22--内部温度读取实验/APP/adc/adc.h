#ifndef _adc_H
#define _adc_H

#include "system.h"

#define ADC_GPIO_PIN GPIO_PIN_5
#define ADC_PROT GPIOA

void ADCx_Init(void);
u16 Get_Adc(u32 ch);
u16 Get_ADC_Value(u32 ch, u8 times);

#endif

