#include "adc.h"
#include "SysTick.h"
#include "usart.h"

ADC_HandleTypeDef ADC1_Handler;

void ADCx_Init(void)
{
    ADC1_Handler.Instance=ADC1;//ADC����ַ
    ADC1_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;//4��Ƶ 84/4=21MHZ
    ADC1_Handler.Init.Resolution=ADC_RESOLUTION_12B;//�ֱ�������Ϊ12
    ADC1_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;//�����Ҷ���
    ADC1_Handler.Init.ScanConvMode=DISABLE;//ɨ��ģʽ �ر�
    ADC1_Handler.Init.EOCSelection=DISABLE;//�ر���ѯ�жϱ�־
    ADC1_Handler.Init.ContinuousConvMode=DISABLE;//�ر��ⲿ����
    ADC1_Handler.Init.NbrOfConversion=1;//˳����������������Ϊ1
    ADC1_Handler.Init.DiscontinuousConvMode=DISABLE;//������ģʽ
    ADC1_Handler.Init.NbrOfDiscConversion=0;
    ADC1_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;//���ô�������Ϊ�������
    ADC1_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//�����ⲿ����
    ADC1_Handler.Init.DMAContinuousRequests=DISABLE;//����DMA
    
    HAL_ADC_Init(&ADC1_Handler);//��ʼ��ADC
    HAL_ADC_Start(&ADC1_Handler);//����ADC
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_ADC1_CLK_ENABLE();//ʹ��ADCʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();//ʹ��GPIOAʱ��
	
	GPIO_InitStructure.Pin=ADC_GPIO_PIN; //PA5 
    GPIO_InitStructure.Mode=GPIO_MODE_ANALOG;  //ģ������
    GPIO_InitStructure.Pull=GPIO_NOPULL;          //��ʹ������
    HAL_GPIO_Init(ADC_PROT,&GPIO_InitStructure);//��ʼ��GPIO
}

u16 Get_Adc(u32 ch)
{
    ADC_ChannelConfTypeDef ADC_ChannelConf;
    
    ADC_ChannelConf.Channel=ch;
    ADC_ChannelConf.Rank=1;
    ADC_ChannelConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;
    ADC_ChannelConf.Offset=0;
    HAL_ADC_ConfigChannel(&ADC1_Handler,&ADC_ChannelConf);
    
    HAL_ADC_Start(&ADC1_Handler);//����ADC
    HAL_ADC_PollForConversion(&ADC1_Handler,10);
    return (u16)HAL_ADC_GetValue(&ADC1_Handler);
}

u16 Get_ADC_Value(u32 ch, u8 times)
{
    u32 temp_val=0;
    u8 t=0;
    for(t=0;t<times;t++)
    {
        temp_val+=Get_Adc(ch);
//        printf("temp_val=%d",temp_val);
        delay_ms(5);
    }
    return (u16)temp_val/times;
}
