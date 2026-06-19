#include "uart.h"
#include "mmap-regs.h"

extern void app(char ch);

void usart1_init() {
  RCC_APB2ENR |= (1 << 2);
  RCC_APB2ENR |= (1 << 14);

  GPIOA_CRH &= ~(0xF << 4);
  GPIOA_CRH |= (0xA << 4);

  GPIOA_CRH &= ~(0xF << 8);
  GPIOA_CRH |= (0x8 << 8);
  GPIOA_ODR |= (1 << 10);

  USART1_CR1 = 0;
  // For STM32F103 @ 8 MHz, 115200 baud
  // USARTDIV = 8000000 / (16 × 115200)
  //          = 4.3403
  USART1_BRR = (4 << 4) | 5;

  USART1_CR1 |= (1 << 2);
  USART1_CR1 |= (1 << 3);
  USART1_CR1 |= (1 << 5);

  NVIC_ISER1 |= (1 << 5);
  
  USART1_CR1 |= (1 << 13);
}

void usart1_write_char(char c) {
  while (!(USART1_SR & (1 << 7)));
  USART1_DR = c;
}

void USART1_IRQHandler(void) {
  app(USART1_DR);
}