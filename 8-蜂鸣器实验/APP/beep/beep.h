#ifndef _beep_H
#define _beep_H

#include "system.h"

#define BEEP_PROT_RCC_ENABLE    __HAL_RCC_GPIOF_CLK_ENABLE()
#define BEEP_PROT  GPIOF
#define BEEP_GPIO_PIN   GPIO_PIN_8

#define BEEP PFout(8)

void BEEP_Init(void);

#endif
