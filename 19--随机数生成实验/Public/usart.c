#include "usart.h"

UART_HandleTypeDef UART1_Handler;

u8 aRxBuffer[RXBUFFERSIZE];

u16 USART1_RX_STA=0;
u8 USART1_RX_BUF[USART1_REC_LEN];


void UART1_Init(u32 bound)
{
    UART1_Handler.Instance=USART1;//ѡ�񴮿�1
    UART1_Handler.Init.BaudRate=bound;//���ò�����
    UART1_Handler.Init.WordLength=USART_WORDLENGTH_8B;//8λ����λ
    UART1_Handler.Init.StopBits=USART_STOPBITS_1;//����ֹͣΪһλ
    UART1_Handler.Init.Parity=USART_PARITY_NONE;//��У��λ
    UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;//��ʹ��Ӳ����
    UART1_Handler.Init.Mode=USART_MODE_TX_RX;//����Ϊ�շ�ģʽ  
    HAL_UART_Init(&UART1_Handler);
    //__HAL_UART_ENABLE_IT(&UART1_Handler,UART_IT_RXNE);//ʹ���ж�
    HAL_UART_Receive_IT(&UART1_Handler,aRxBuffer,RXBUFFERSIZE);//ʹ���ж�
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    if(huart->Instance==USART1)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();
        
        GPIO_InitStructure.Pin=GPIO_PIN_9|GPIO_PIN_10; 
        GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;  //�����������
        GPIO_InitStructure.Pull=GPIO_PULLUP;          //����
        GPIO_InitStructure.Speed=GPIO_SPEED_FAST;     //����
        GPIO_InitStructure.Alternate=GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);
        
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        HAL_NVIC_SetPriority(USART1_IRQn,3,3);
    }  
    
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance==USART1)
    {
        if((USART1_RX_STA&0X8000)==0)
        {
            if(USART1_RX_STA&0X4000)
            {
                if(aRxBuffer[0]!=0X0A)USART1_RX_STA=0;
                else USART1_RX_STA|=0X8000;
            }
            else
            {
                if(aRxBuffer[0]==0X0D) USART1_RX_STA|=0X4000;
                else
                {
                    USART1_RX_BUF[USART1_RX_STA&0X3FFF]=aRxBuffer[0];
                    USART1_RX_STA++;
                    if(USART1_RX_STA>USART1_REC_LEN-1) USART1_RX_STA=0;
                }
            }
        }
    }
}

void USART1_IRQHandler(void)
{
    u32 timeout=0;
    HAL_UART_IRQHandler(&UART1_Handler);
    timeout=0;
    while(HAL_UART_GetState(&UART1_Handler)!=HAL_UART_STATE_READY)
    {
        timeout++;
        if(timeout>=HAL_MAX_DELAY)break;
    }
    timeout=0;
    while(HAL_UART_Receive_IT(&UART1_Handler,(u8 *)aRxBuffer,RXBUFFERSIZE)!=HAL_OK)
    {
        timeout++;
        if(timeout>=HAL_MAX_DELAY)break;
    }
    
}

