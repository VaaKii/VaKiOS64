#include <tty/tty.h>
#include <sys/stdio.h>
#include <memory/gdt.h>
#include <memory/paging.h>
#include <memory/idt.h>
#include <memory/pic.h>
#include <memory/pit.h>
#include <memory/memory.h>

extern uint32_t kernel_end;

void kernel_main(void){
    terminal_initialize();
    mm_init(&kernel_end);
    init_gdt();
    idt_init();
    exception_init();
    paging_init();
    pic_init();
    pit_init();
    asm volatile("hlt");
}