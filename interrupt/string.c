#include "string.h"
#include "uart.h"

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
    digits[idx++] = num % 10 + 48;
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

uint32_t strlen(const char *buf) {
  uint32_t len = 0;
  while(*buf++) len++;
  return len;
}

int32_t to_upper(int32_t c) {
  return (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
}

void to_uppercase_str(char *s) {
  while(*s) {
    *s = to_upper(*s);
    s++;
  }
}