#include "wkup.h"

void Enter_Standby_Mode(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();//ʹ�ܵ�Դʱ��
    
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);//������ѱ�־
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);//���û�������
    HAL_PWR_EnterSTANDBYMode(); //�������ģʽ
}
