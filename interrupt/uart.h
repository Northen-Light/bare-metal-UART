#ifndef UART_H
#define UART_H

void usart1_init();
void usart1_write_char(char c);
void USART1_IRQHandler(void);

#endif