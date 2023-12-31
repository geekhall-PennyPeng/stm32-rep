/*******************************************************************************
*                 
*                 		       普中科技
--------------------------------------------------------------------------------
* 实 验 名		 : LED闪烁（使用位带操作）
* 实验说明       : 
* 连接方式       : 
* 注    意		 : 位带操作程序在system.h内
*******************************************************************************/

#include "system.h"
#include "led.h"

/*******************************************************************************
* 函 数 名         : delay
* 函数功能		   : 延时函数，通过while循环占用CPU，达到延时功能
* 输    入         : i
* 输    出         : 无
*******************************************************************************/
void delay(u32 i)
{
	while(i--);
}

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	LED_Init();
	while(1)
	{
		LED1=!LED1;  //D1状态取反
		delay(6000000);
	}
}


