#include "uart.h"
#include "string.h"

#define BUFFER_SIZE   127

char buf[BUFFER_SIZE];
uint8_t bfull;

int main(void) {
  usart1_init();
  
  while(1) {
    readline(buf, &bfull, BUFFER_SIZE);
    if (bfull) {
      printstr("Buffer full");
      printstr("\r\n");
    } else {
      printstr("\r\n");

      printstr("str : ");
      printstr(buf);
      printstr("\r\n");

      to_uppercase_str(buf);
      printstr("upper case str : ");
      printstr(buf);
      printstr("\r\n");

      uint8_t len = strlen(buf);

      strrev(buf, len);
      printstr("reverse str : ");
      printstr(buf);
      printstr("\r\n");

      printstr("length of str : ");
      printnumber(len);
      printstr("\r\n");
      printstr("\r\n");
    }
  };
  return 0;
}