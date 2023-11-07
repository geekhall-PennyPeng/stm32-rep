#include "touch_key.h"
#include "SysTick.h"
#include "usart.h"

TIM_HandleTypeDef TIM2_Handler;

u32 touch_defailt_val=0;//触控默认初始值


#define Touch_ARR_MAX_VAL 0XFFFFFFFF

void TIM2_CH1_Input_Init(u32 arr,u16 psc)
{
//    printf("开始定时器捕获执行初始化");
    TIM_IC_InitTypeDef TIM_CH1;
    
    TIM2_Handler.Instance=TIM2;
    TIM2_Handler.Init.Prescaler=psc; //设置预分配值
    TIM2_Handler.Init.Period=arr;//设置预装值
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP ;//设置为上升沿捕获
	TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //设置为不分频
    HAL_TIM_IC_Init(&TIM2_Handler);
    //配置IC时钟通道

    TIM_CH1.ICPolarity=TIM_ICPOLARITY_RISING;//上升沿触发
    TIM_CH1.ICSelection=TIM_ICSELECTION_DIRECTTI; //映射选择 直连模式
    TIM_CH1.ICFilter=0;//不启用滤波器
    HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM_CH1,TIM_CHANNEL_1);//配置CI时钟
    HAL_TIM_IC_Start_IT(&TIM2_Handler,TIM_CHANNEL_1);//开启定时器、捕获通道、中断
//    printf("定时器捕获执行初始化正常");
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{  
    GPIO_InitTypeDef GPIO_InitStructure;
    
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitStructure.Pin=GPIO_PIN_5; //PF0
    GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;  //复用推挽输出
    GPIO_InitStructure.Pull=GPIO_NOPULL;          //浮空
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //高速
    GPIO_InitStructure.Alternate=GPIO_AF1_TIM2; //定时器5模式
    HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO

}

void Touch_Rest(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
	
	GPIO_InitStructure.Pin=GPIO_PIN_5; //PF0
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;  //复用推挽输出
    GPIO_InitStructure.Pull=GPIO_PULLDOWN;          //低电平
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO
    
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);//管脚置低
    delay_ms(5);//延时等待放电结束
    
    __HAL_TIM_CLEAR_FLAG(&TIM2_Handler,TIM_FLAG_CC1|TIM_FLAG_UPDATE);//标志清零
    __HAL_TIM_SET_COUNTER(&TIM2_Handler,0);//计数清零
    
    GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;  //复用推挽输出
    GPIO_InitStructure.Pull=GPIO_NOPULL;          //浮空
    GPIO_InitStructure.Alternate=GPIO_AF1_TIM2; //定时器5模式
    HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO
   
}

u16 Touch_Get_Val(void) //获取触摸时间
{
//    printf("开始获取触摸时间");
    Touch_Rest();
    while(__HAL_TIM_GET_FLAG(&TIM2_Handler,TIM_FLAG_CC1)==RESET)
    {
        if(__HAL_TIM_GET_COUNTER(&TIM2_Handler)>Touch_ARR_MAX_VAL-500)
            return __HAL_TIM_GET_COUNTER(&TIM2_Handler);
    }
//    printf("获取触摸时间结束");
    return HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_1);
}

u8 Touch_Key_Init(u16 psc)
{
    u32 buf[10];
    u8 i=0,j=0;
    u16 tmp=0;
    TIM2_CH1_Input_Init(Touch_ARR_MAX_VAL,psc);
    for(i=0;i<10;i++)
    {
        buf[i]=Touch_Get_Val();
    }
    for(i=0;i<9;i++)
    {
        for(j=i+1;j<10;j++)
        {
            if(buf[i]>buf[j])
            {
                tmp=buf[i];
                buf[i]=buf[j];
                buf[j]=tmp;
            }
        }
    }
    tmp=0;
    for(i=2;i<8;i++)
    {
        tmp+=buf[i];
    }
    touch_defailt_val=tmp/6;
    printf("touch_defailt_val=%d\r\n",touch_defailt_val);
    if(touch_defailt_val>(Touch_ARR_MAX_VAL/2))return 1;
    return 0;
}
u16 Touch_Get_MaxVal(u8 n)
{
    u16 tmp=0,res=0;
    while(n--)
    {
        tmp=Touch_Get_Val();
        if(res<tmp) res=tmp;
    }
    return res;
}
#define TOUCH_GATE_VAL 80
u8 Touch_Key_Scan(u8 mode)
{
    u8 simple=3;
    u8 res=0;
    u16 rval=Touch_Get_MaxVal(simple);
    static u8 keyen=0;
    
    if(mode) 
    {
        keyen=0;
        simple=6;
    }
    
    if(rval>(touch_defailt_val+TOUCH_GATE_VAL)&&rval<(touch_defailt_val*10))
    {
        if(keyen==0&&rval>(touch_defailt_val+TOUCH_GATE_VAL))
        {
            res=1;
            keyen=1;
            printf("触摸有效，捕获高电平值为：%d\r\n",rval);
        }
        
    }
    else
       keyen=0; 
    return res;
}

