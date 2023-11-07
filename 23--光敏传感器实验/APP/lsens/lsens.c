#include "lsens.h"
#include "adc.h"
ADC_HandleTypeDef ADC3_Handler;

void Lsens_Init(void)
{
    ADC3_Handler.Instance=ADC3;//ADC����ַ
    ADC3_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;//4��Ƶ 84/4=21MHZ
    ADC3_Handler.Init.Resolution=ADC_RESOLUTION_12B;//�ֱ�������Ϊ12
    ADC3_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;//�����Ҷ���
    ADC3_Handler.Init.ScanConvMode=DISABLE;//ɨ��ģʽ �ر�
    ADC3_Handler.Init.EOCSelection=DISABLE;//�ر���ѯ�жϱ�־
    ADC3_Handler.Init.ContinuousConvMode=DISABLE;//�ر��ⲿ����
    ADC3_Handler.Init.NbrOfConversion=1;//˳����������������Ϊ1
    ADC3_Handler.Init.DiscontinuousConvMode=DISABLE;//������ģʽ
    ADC3_Handler.Init.NbrOfDiscConversion=0;
    ADC3_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;//���ô�������Ϊ�������
    ADC3_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//�����ⲿ����
    ADC3_Handler.Init.DMAContinuousRequests=DISABLE;//����DMA
    
    HAL_ADC_Init(&ADC3_Handler);//��ʼ��ADC
    HAL_ADC_Start(&ADC3_Handler);//����ADC
}

u8 Lsens_Get_Value(void)
{
    u16 adc_value=0;
    double light_value;
    
    adc_value=(float)Get_ADC_Value(&ADC3_Handler,ADC_CHANNEL_5,10);
    if(adc_value>4000) adc_value=4000;
    
    light_value=(u8)(100-adc_value/40);
    return light_value;
}
