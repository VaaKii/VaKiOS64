#include <tty/tty.h>
#include <sys/stdio.h>
#include <memory/gdt.h>
#include <memory/idt.h>

void kernel_main(void){
    terminal_initialize();
    init_gdt();
    idt_init();
    exception_init();
    asm volatile("hlt");
}