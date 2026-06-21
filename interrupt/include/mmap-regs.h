#define RCC_APB2ENR           *((volatile unsigned int *) 0x40021018)

#define NVIC_ISER1            *((volatile unsigned int *) 0xE000E104)

#define GPIOA_CRH             *((volatile unsigned int *) 0x40010804)
#define GPIOA_ODR             *((volatile unsigned int *) 0x4001080C)

#define USART1_SR             *((volatile unsigned int *) 0x40013800)
#define USART1_DR             *((volatile unsigned int *) 0x40013804)
#define USART1_BRR            *((volatile unsigned int *) 0x40013808)
#define USART1_CR1            *((volatile unsigned int *) 0x4001380C)
