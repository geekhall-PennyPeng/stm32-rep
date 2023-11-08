#include "adc.h"
#include "adc_temp.h"
#include "SysTick.h"
#include "usart.h"

ADC_HandleTypeDef Temp_Handler;

void Temp_Init(void)
{
    Temp_Handler.Instance=ADC1;//ADC����ַ
    Temp_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;//4��Ƶ 84/4=21MHZ
    Temp_Handler.Init.Resolution=ADC_RESOLUTION_12B;//�ֱ�������Ϊ12
    Temp_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;//�����Ҷ���
    Temp_Handler.Init.ScanConvMode=DISABLE;//ɨ��ģʽ �ر�
    Temp_Handler.Init.EOCSelection=DISABLE;//�ر���ѯ�жϱ�־
    Temp_Handler.Init.ContinuousConvMode=DISABLE;//�ر��ⲿ����
    Temp_Handler.Init.NbrOfConversion=1;//˳����������������Ϊ1
    Temp_Handler.Init.DiscontinuousConvMode=DISABLE;//������ģʽ
    Temp_Handler.Init.NbrOfDiscConversion=0;
    Temp_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;//���ô�������Ϊ�������
    Temp_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//�����ⲿ����
    Temp_Handler.Init.DMAContinuousRequests=DISABLE;//����DMA
    
    HAL_ADC_Init(&Temp_Handler);//��ʼ��ADC
    HAL_ADC_Start(&Temp_Handler);//����ADC
}

int Get_Temperature_Value(void)
{
    u16 adc_value=0;
    double vol,temperate;
    int result;
    
    adc_value=(float)Get_ADC_Value(&Temp_Handler,ADC_CHANNEL_16,10);
    vol=3.3/4096*adc_value;
    temperate=((vol-0.76)/0.0025)+25;
    result=temperate*100;
    return result;
}
