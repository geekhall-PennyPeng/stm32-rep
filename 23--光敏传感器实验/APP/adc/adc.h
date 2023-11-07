#ifndef _adc_H
#define _adc_H

#include "system.h"

#define ADC1_GPIO_PIN GPIO_PIN_5
#define ADC1_PROT GPIOA

#define ADC3_GPIO_PIN GPIO_PIN_7
#define ADC3_PROT GPIOF

void ADCx_Init(ADC_TypeDef *Instance);
u16 Get_Adc(ADC_HandleTypeDef* ADC_Handler,u32 ch);
u16 Get_ADC_Value(ADC_HandleTypeDef* ADC_Handler,u32 ch, u8 times);

#endif

