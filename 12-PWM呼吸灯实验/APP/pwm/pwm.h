#ifndef _pwm_H
#define _pwm_H
 
#include "system.h"
 
void TIM14_CH1_PWM_Init(u16 per, u16 psc);
void TIM14_SetCompare1(u32 compare);
  
#endif

