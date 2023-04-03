//
// Created by vlad on 03.04.2023.
//

#ifndef VAKIOS64_MEMORY_H
#define VAKIOS64_MEMORY_H

#include <stdint.h>
#include <stddef.h>

extern void* memcpy(void* dest, const void* src, size_t count );
extern void* memset (void * ptr, int value, size_t num );
extern void* memset16 (void *ptr, uint16_t value, size_t num);

#endif //VAKIOS64_MEMORY_H
