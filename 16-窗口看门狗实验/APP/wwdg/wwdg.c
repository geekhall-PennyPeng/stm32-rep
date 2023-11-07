#include "wwdg.h"
#include "LED.h"
#include "SysTick.h"

WWDG_HandleTypeDef WWDG_Handler;

void WWDG_Init(u8 tr,u8 wr,u32 fpre)
{   
    WWDG_Handler.Instance=WWDG;
    WWDG_Handler.Init.Prescaler=fpre;
    WWDG_Handler.Init.Window=wr;
    WWDG_Handler.Init.Counter=tr;
    WWDG_Handler.Init.EWIMode=WWDG_EWI_ENABLE;
    HAL_WWDG_Init(&WWDG_Handler);
}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    __HAL_RCC_WWDG_CLK_ENABLE();
    
    HAL_NVIC_SetPriority(WWDG_IRQn,2,3);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}

void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&WWDG_Handler);
}

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    delay_us(600);
    HAL_WWDG_Refresh(&WWDG_Handler);
    LED2=!LED2;
}
