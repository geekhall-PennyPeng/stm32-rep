#include "iwdg.h"

IWDG_HandleTypeDef IWDG_Handler;

void IWDG_Init(u8 pre,u16 rlr)
{
    IWDG_Handler.Instance=IWDG;
    IWDG_Handler.Init.Prescaler=pre;
    IWDG_Handler.Init.Reload=rlr;
    HAL_IWDG_Init(&IWDG_Handler);
}

void IWDG_FeedDog(void)
{
    HAL_IWDG_Refresh(&IWDG_Handler);
}
