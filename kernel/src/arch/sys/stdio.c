#include <sys/stdio.h>
#include <tty/tty.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>


char tbuf[32];
char bchars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void __itoa(unsigned i, unsigned base, char *buf) {
    int pos = 0;
    int opos = 0;
    int top = 0;

    if (i == 0 || base > 16) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    while (i != 0) {
        tbuf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    top = pos--;
    for (opos = 0; opos < top; pos--, opos++)
        buf[opos] = tbuf[pos];
    buf[opos] = 0;
}

void __itoa_s(int i, unsigned base, char *buf) {
    if (base > 16) return;
    if (i < 0) {
        *buf++ = '-';
        i *= -1;
    }
    __itoa(i, base, buf);
}
static bool print(const char *data, size_t length) {
    const unsigned char *bytes = (const unsigned char *) data;
    for (size_t i = 0; i < length; i++)
        if (putchar(bytes[i]) == EOF)
            return false;
    return true;
}


int printf(const char *restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);
    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            if (maxrem < amount) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, amount))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const char *format_begun_at = format++;
        if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters,
            int /* char promotes to int */);
            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        } else if (*format == 's') {
            format++;
            const char *str = va_arg(parameters,
            const char*);
            size_t len = strlen(str);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print( str, len))
                return -1;
            written += len;

        } else if (*format == 'x') {
            format++;
            int c = va_arg(parameters,
            int);
            char str[32] = {0};
            __itoa(c, 16, str);
            size_t len = strlen(str);
            if (!print(&str[0], len)) {
                return -1;
            }
            written += len;
        } else if (*format == 'd') {
            format++;
            int c = va_arg(parameters,
            int);
            char str[32] = {0};
            __itoa_s(c, 10, str);
            size_t len = strlen(str);
            if (!print( &str[0], len)) {
                return -1;
            }
            print("\n",1);
            written += len+ 1;
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, len))
                return -1;
            written += len;
            format += len;
        }
    }
    va_end(parameters);
    return written;
}

int putchar(int ic) {
    char c = (char) ic;
    terminal_putchar(c);
    return ic;
};
