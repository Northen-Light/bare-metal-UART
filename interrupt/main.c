#include "uart.h"
#include "string.h"

#define BUFFER_SIZE 128

char buf[BUFFER_SIZE];
int idx = 0, bfull = 0;

int main(void) {
  usart1_init();
  while(1);
  return 0;
}

void app(char ch) {
  if (!bfull) usart1_write_char(ch);

  if (ch == '\r') {
    buf[idx] = '\0';
    idx = 0;

    printstr("\r\n");

    if (bfull) {
      bfull = 0;
      printstr("\r\n");
      return;
    }

    printstr("str : ");
    printstr(buf);
    printstr("\r\n");

    to_uppercase_str(buf);
    printstr("upper case str : ");
    printstr(buf);
    printstr("\r\n");

    int len = strlen(buf);

    printstr("length of str : ");
    printnumber(len);
    printstr("\r\n");

    strrev(buf, len);
    printstr("reverse str : ");
    printstr(buf);
    printstr("\r\n");
    printstr("\r\n");

  } else {
    if (idx < BUFFER_SIZE - 1) {
      buf[idx++] = ch;
    } else {
      bfull = 1;
      printstr("\r\nBuffer full. Enter to continue...");
    }
  }
}