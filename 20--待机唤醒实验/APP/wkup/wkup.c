#include "wkup.h"

void Enter_Standby_Mode(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();//使能电源时钟
    
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);//清除唤醒标志
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);//设置唤醒引脚
    HAL_PWR_EnterSTANDBYMode(); //进入待机模式
}
