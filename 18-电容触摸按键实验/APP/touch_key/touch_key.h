#ifndef touch_key_H
#define touch_key_H

#include "system.h"

void TIM2_CH1_Input_Init(u32 arr,u16 psc);
u16 Touch_Get_Val(void);
u8 Touch_Key_Init(u16 psc);
u8 Touch_Key_Scan(u8 mode);

#endif
