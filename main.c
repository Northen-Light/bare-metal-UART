#include "mmap-regs.h"

#define BUFFER_SIZE   127

typedef unsigned int        uint32_t;
typedef unsigned short      uint16_t;
typedef unsigned char       uint8_t;
typedef signed int          int32_t;
typedef signed short        int16_t;
typedef signed char         int8_t;

char usart1_read_char();
void usart1_write_char(char c);

void readline(char *buf, uint8_t *bfull, uint8_t maxlen);
void printstr(const char *buf);
void printnumber(uint8_t num);

void strrev(char *s, uint8_t len);
uint32_t strlen(const char *buf);
int32_t to_upper(int32_t c);
void to_uppercase_str(char *s);

char buf[BUFFER_SIZE];
uint8_t bfull;

int main(void) {
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

      uint32_t len = strlen(buf);

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

void usart1_write_char(char c) {
  while (!(USART1_SR & (1 << 7)));
  USART1_DR = c;
}

char usart1_read_char() {
  while (!(USART1_SR & (1 << 5)));
  return USART1_DR;
}

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