#include "mmap-regs.h"

void usart1_write_char(char c);
void usart1_write_string(const char *s);

void main(void) {
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
  USART1_CR1 |= (1 << 13);

  while(1) {
    usart1_write_string("Hello, World!\r\n");
  };
}

void usart1_write_char(char c) {
  while (!(USART1_SR & (1 << 7)));
  USART1_DR = c;
}

void usart1_write_string (const char *s) {
  while (*s) {
    usart1_write_char(*s++);
  }
}

char usart1_read_char() {
  while (!(USART1_SR & (1 << 5)));
  return USART1_DR;
}