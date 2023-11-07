#include "key.h"
#include "SysTick.h"

void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    KEY0_PROT_RCC_ENABLE;  
    GPIO_InitStructure.Pin=KEY0_GPIO_PIN;
    GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_PROT,&GPIO_InitStructure);
    
    KEY1_PROT_RCC_ENABLE;
    GPIO_InitStructure.Pin=KEY1_GPIO_PIN;
    HAL_GPIO_Init(KEY1_PROT,&GPIO_InitStructure);
    
    KEY2_PROT_RCC_ENABLE;
    GPIO_InitStructure.Pin=KEY2_GPIO_PIN;
    HAL_GPIO_Init(KEY2_PROT,&GPIO_InitStructure);
    
    KEY_UP_PROT_RCC_ENABLE;
    GPIO_InitStructure.Pin=KEY_UP_GPIO_PIN;
    GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull=GPIO_PULLDOWN;;
    HAL_GPIO_Init(KEY_UP_PROT,&GPIO_InitStructure);
}
u8 KEY_Scan(u8 mode)
{
	static u8 key=1;
    if(mode==KEY_CONTINUOUS)     
		key=1;
	
	if(key==1&&(KEY_UP==1 || KEY0==0 || KEY1==0 || KEY2==0))
	{
		if(mode==KEY_CONTINUOUS)
			delay_ms(100);
		else if(mode==KEY_DISCONTINUOUS)
			delay_ms(10);	
		key=0;
		if(KEY_UP==1) return KEY_UP_PRESS;
		else if(KEY0==0) return KEY0_PRESS;
		else if(KEY1==0) return KEY1_PRESS;
		else if(KEY2==0) return KEY2_PRESS;		
	}
	
	else if(KEY_UP==0 && KEY0==1 && KEY1==1 && KEY2==1)
		key=1;
    return 0;
}
//u8 KEY_Scan(u8 mode)
//{
//    if(mode==KEY_CONTINUOUS)
//    {
//        if(KEY_UP==1 || KEY0==0 || KEY1==0 || KEY2==0)
//        {
//            delay_ms(10);
//            if(KEY_UP==1) return KEY_UP_PRESS;
//            else if(KEY0==0) return KEY0_PRESS;
//            else if(KEY1==0) return KEY1_PRESS;
//            else if(KEY2==0) return KEY2_PRESS;
//            
//        }
//    }
//    else if(mode==KEY_DISCONTINUOUS)
//    {
//        if(KEY_UP==1 || KEY0==0 || KEY1==0 || KEY2==0)
//        {
//            delay_ms(10);
//            if(KEY_UP==1) 
//            {                
//                while(KEY_UP==1);
//                return KEY_UP_PRESS;
//            }
//            else if(KEY0==0) 
//            {
//                while(KEY0==0) ;
//                return KEY0_PRESS;                
//            }
//                
//            else if(KEY1==0)
//            {
//                while(KEY1==0) ;
//                return KEY1_PRESS;                
//            }
//                
//            else if(KEY2==0) 
//            {
//                while(KEY2==KEY2_PRESS) ;
//                return KEY2_PRESS;            
//            }            
//        }
//    }
//    
//    return 0;
//}

