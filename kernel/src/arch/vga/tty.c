#include <tty/tty.h>
#include <memory/memory.h>

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}



static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void scroll(){
    void * start = (void*)0xB8000 + 1 * VGA_WIDTH * 2;
    uint32_t size = terminal_row * VGA_WIDTH * 2;
    if(terminal_row < 25){
        return;
    }
    memcpy((void *) 0xB8000, start, size);
    start = (void*)0xB8000 + size;
    memset16(start,vga_entry(' ',terminal_color),VGA_WIDTH);
    terminal_row--;
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
    scroll();
    if(c == '\n') {terminal_row++;terminal_column=0;return;}
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
}

void erase(){
    if(--terminal_column == 0 && terminal_row != 0){
        terminal_row--;
        terminal_column = 80;
    }

    const size_t index = terminal_row * VGA_WIDTH + terminal_column;
    terminal_buffer[index] = vga_entry(' ', terminal_color);
}

void clear() {
memset16((void*)0xB8000, vga_entry(' ',terminal_color),80*25);
    terminal_row=0;
    terminal_column=0;
}