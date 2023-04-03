#ifndef VAKIOS64_STDIO_H
#define VAKIOS64_STDIO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#define EOF (-1)

#define panic(...) {printf("***KERNEL PANIC*** in %s at line %d in function: %s\n", __FILE__, __LINE__, __func__); printf(__VA_ARGS__); for(;;);}

int printf(const char* __restrict, ...);
int putchar(int);
void __itoa(unsigned i,unsigned base,char* buf);
void __itoa_s(int i,unsigned base,char* buf);

#endif //VAKIOS64_STDIO_H
