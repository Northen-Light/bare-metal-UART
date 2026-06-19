#ifndef UART_H
#define UART_H

#include "stdint.h"

void usart1_init();
char usart1_read_char();
void usart1_write_char(char c);

#endif