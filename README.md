# Bare-metal UART Driver for STM32F103

A bare-metal UART driver for the STM32F103 (USART1 peripheral) written without using HAL or STM32Cube libraries. The driver communicates with a host computer through a USB-to-UART adapter (CP2102).

## Features

- Initialize USART1 for asynchronous serial communication.
- Read characters using `usart1_read_char()` (polling mode).
- Transmit characters using `usart1_write_char()`.
- Receive characters using the USART interrupt handler (interrupt mode).
- Echo characters received from the host terminal.
- Read a complete line into a buffer.
- Perform simple string operations such as:
  - Convert to uppercase
  - Reverse the string
  - Calculate string length
- Print strings to the host terminal using `printstr()`.