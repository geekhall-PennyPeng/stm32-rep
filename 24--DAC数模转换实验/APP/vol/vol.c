#include "vol.h"
#include "adc.h"

ADC_HandleTypeDef Vol_Handler;

void Vol_Init(void)
{
    Vol_Handler.Instance=ADC1;//ADC����ַ
    Vol_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;//4��Ƶ 84/4=21MHZ
    Vol_Handler.Init.Resolution=ADC_RESOLUTION_12B;//�ֱ�������Ϊ12
    Vol_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;//�����Ҷ���
    Vol_Handler.Init.ScanConvMode=DISABLE;//ɨ��ģʽ �ر�
    Vol_Handler.Init.EOCSelection=DISABLE;//�ر���ѯ�жϱ�־
    Vol_Handler.Init.ContinuousConvMode=DISABLE;//�ر��ⲿ����
    Vol_Handler.Init.NbrOfConversion=1;//˳����������������Ϊ1
    Vol_Handler.Init.DiscontinuousConvMode=DISABLE;//������ģʽ
    Vol_Handler.Init.NbrOfDiscConversion=0;
    Vol_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;//���ô�������Ϊ�������
    Vol_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//�����ⲿ����
    Vol_Handler.Init.DMAContinuousRequests=DISABLE;//����DMA
    
    HAL_ADC_Init(&Vol_Handler);//��ʼ��ADC
    HAL_ADC_Start(&Vol_Handler);//����ADC
}

u16 Get_Vol_Adc_Value(void)
{
    Get_ADC_Value(&Vol_Handler,ADC_CHANNEL_5, 10);
}