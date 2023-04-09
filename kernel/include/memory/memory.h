//
// Created by vlad on 03.04.2023.
//

#ifndef VAKIOS64_MEMORY_H
#define VAKIOS64_MEMORY_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;

extern void mm_init();
extern char* pmalloc(size_t size); /* page aligned alloc */
extern char* malloc(size_t size);
extern void free(void *mem);
extern void pfree(void *mem);
extern void* memcpy(void* dest, const void* src, size_t count );
extern void* memset (void * ptr, int value, size_t num );
extern void* memset16 (void *ptr, uint16_t value, size_t num);

#endif //VAKIOS64_MEMORY_H
