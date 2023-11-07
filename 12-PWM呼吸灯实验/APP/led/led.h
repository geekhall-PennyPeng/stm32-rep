#ifndef _led_H
#define _led_H

#include "system.h"

#define LED1_PROT_RCC_ENABLE    __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED1_PROT  GPIOF
#define LED1_GPIO_PIN   GPIO_PIN_9

#define LED2_PROT  GPIOF
#define LED2_PROT_RCC_ENABLE    __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED2_GPIO_PIN   GPIO_PIN_10

#define LED1 PFout(9)
#define LED2 PFout(10)

void LED_Init(void);

#endif
