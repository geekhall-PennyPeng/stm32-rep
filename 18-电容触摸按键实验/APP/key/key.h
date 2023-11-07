#ifndef _key_H
#define _key_H

#include "system.h"

#define KEY0_PROT_RCC_ENABLE    __HAL_RCC_GPIOE_CLK_ENABLE()
#define KEY0_PROT  GPIOE                      
#define KEY0_GPIO_PIN   GPIO_PIN_4            
                                              
#define KEY1_PROT_RCC_ENABLE    __HAL_RCC_GPIOE_CLK_ENABLE()
#define KEY1_PROT  GPIOE                      
#define KEY1_GPIO_PIN   GPIO_PIN_3            
                                              
#define KEY2_PROT_RCC_ENABLE    __HAL_RCC_GPIOE_CLK_ENABLE()
#define KEY2_PROT  GPIOE
#define KEY2_GPIO_PIN   GPIO_PIN_2

#define KEY_UP_PROT_RCC_ENABLE    __HAL_RCC_GPIOA_CLK_ENABLE()
#define KEY_UP_PROT  GPIOA
#define KEY_UP_GPIO_PIN   GPIO_PIN_0

#define KEY0 PEin(4)
#define KEY1 PEin(3)
#define KEY2 PEin(2)
#define KEY_UP PAin(0)

#define KEY_UP_PRESS 1
#define KEY0_PRESS 2
#define KEY1_PRESS 3
#define KEY2_PRESS 4
/*
定义KEY模式
*/
#define KEY_CONTINUOUS 0	//连续的
#define KEY_DISCONTINUOUS 1	//不连续的

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
    
#endif
