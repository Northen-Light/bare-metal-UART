#ifndef UART_H
#define UART_H
typedef void (*usart1_rx_callback_t)(char);

void usart1_init(void);
void usart1_write_char(char c);
void usart1_set_rx_callback(usart1_rx_callback_t cb);
void USART1_IRQHandler(void);

#endif