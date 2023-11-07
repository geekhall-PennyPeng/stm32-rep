#ifndef _usart_H
#define _usart_H

#include "system.h"
#define RXBUFFERSIZE 1

#define USART1_REC_LEN 200 //接收缓存长度

extern u16 USART1_RX_STA;
extern UART_HandleTypeDef UART1_Handler;
extern u8 USART1_RX_BUF[USART1_REC_LEN];

void UART1_Init(u32 bound);


#endif
