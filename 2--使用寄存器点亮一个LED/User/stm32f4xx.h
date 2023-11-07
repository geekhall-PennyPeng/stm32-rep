#define PERIPH_BASE         ((unsigned int)0X40000000)
    
#define AHB1PERIPH_BASE     (PERIPH_BASE+0X20000)

#define GPIOF_BASE          (AHB1PERIPH_BASE+0X1400)
#define GPIOF_MODER         *(unsigned int*)(GPIOF_BASE+0X00)
#define GPIOF_BSRR          *(unsigned int*)(GPIOF_BASE+0X18)

#define RCC_BASE            (AHB1PERIPH_BASE+0X3800)
#define RCC_AHB1ENR         *(unsigned int*)(RCC_BASE+0X30)
