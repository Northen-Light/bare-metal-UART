#include "uart.h"

extern int main(void);
extern char _estack;
extern char _end_rodata_;
extern char _start_data_;
extern char _end_data_;
extern char _start_bss_;
extern char _end_bss_;

void Reset_Handler(void);
void HardFault_Handler(void);

__attribute__((section(".isr_vector")))
char *vector_table[] = {
  &_estack,
  (char *) Reset_Handler,
  0,
  (char *) HardFault_Handler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  (char *) USART1_IRQHandler,
};

void Reset_Handler(void) {
  char *data_start_src = &_end_rodata_;
  char *data_start_dest = &_start_data_;
  char *data_end_dest = &_end_data_;

  while (data_start_dest != data_end_dest) {
    *data_start_dest++ = *data_start_src++;
  }

  char *bss_start = &_start_bss_;
  char *bss_end = &_end_bss_;

  while (bss_start != bss_end) {
    *bss_start++ = 0;
  }

  main();
}

void HardFault_Handler(void) {
  __asm volatile ("bkpt #0");
  while(1);
}