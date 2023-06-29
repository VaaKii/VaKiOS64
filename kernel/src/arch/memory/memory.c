#include <memory/memory.h>


void *memset16(void *ptr, uint16_t value, size_t num) {
    uint16_t *p = ptr;
    while (num--) {
        *p++ = value;
    }
    return ptr;
}

void *memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;
    while (num--) {
        *p++ = (unsigned char) value;
    }
    return ptr;
}

void* memcpy(void* dest, const void* src, size_t count )
{
    char *d = dest;
    const char *s = src;
    while (count--)
        *d++ = *s++;
    return dest;
}
int memcmp (const void *str1, const void *str2, size_t count)
{
    const unsigned char *s1 = str1;
    const unsigned char *s2 = str2;

    while (count-- > 0)
    {
        if (*s1++ != *s2++)
            return s1[-1] < s2[-1] ? -1 : 1;
    }
    return 0;
}