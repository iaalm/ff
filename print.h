#ifndef _PRINT_H_
#define _PRINT_H_
#include <stdarg.h>
#include "ctype.h"

void putc_k(char);
void puts_k(char*);
void putl_k(int);
void clean_screen();

int vsprintf_k(char *, const char *, va_list);
int sprintf_k(char *buf, const char *fmt, ...);
int printf_k(const char *fmt, ...);
#endif//_PRINT_H_
