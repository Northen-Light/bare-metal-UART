#include "string.h"
#include "uart.h"

void readline(char *buf, uint8_t *bfull, uint8_t maxlen) {
  char ch;
  uint8_t idx = 0;
  *bfull = 0;
  while ((ch = usart1_read_char()) != '\r') {
    usart1_write_char(ch);
    if (idx < maxlen - 1) {
      buf[idx++] = ch;
    } else {
      *bfull = 1;
      break;
    }
  }
  buf[idx] = '\0';
  if (*bfull) {
    while(usart1_read_char() != '\r');
  }
}

void printstr (const char *s) {
  while (*s) {
    usart1_write_char(*s++);
  }
}

void printnumber(uint8_t num) {
  if (num == 0) {
    usart1_write_char('0');
    return;
  }

  char digits[12];
  uint8_t idx = 0, len;
  
  while (num) {
    digits[idx++] = num % 10 + '0';
    num /= 10;
  }

  digits[idx] = '\0';
  len = idx;
  strrev(digits, len);

  printstr(digits);
}

void strrev(char *s, uint8_t len) {
  if (len == 0) return;
  uint8_t st = 0, end = len - 1;

  while (st < end) {
    char tmp = s[st];
    s[st] = s[end];
    s[end] = tmp;
    st++;
    end--;
  }
}

uint8_t strlen(const char *buf) {
  uint8_t len = 0;
  while(*buf++) len++;
  return len;
}

char to_upper(char c) {
  return (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
}

void to_uppercase_str(char *s) {
  while(*s) {
    *s = to_upper(*s);
    s++;
  }
}