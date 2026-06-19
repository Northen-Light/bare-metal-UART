#ifndef STRING_H
#define STRING_H

#include "stdint.h"

void readline(char *buf, uint8_t *bfull, uint8_t maxlen);
void printstr(const char *buf);
void printnumber(uint8_t num);

void strrev(char *s, uint8_t len);
uint32_t strlen(const char *buf);
int32_t to_upper(int32_t c);
void to_uppercase_str(char *s);

#endif