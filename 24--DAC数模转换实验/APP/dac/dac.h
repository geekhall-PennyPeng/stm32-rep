#ifndef _dac_H
#define _dac_H

#include "system.h"

void DAC1_Init(void);
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac);
void Set_DAC_Vol(u16 vol);
u32 Get_DAC_Value(void);

#endif
