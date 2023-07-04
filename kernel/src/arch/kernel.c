#include <tty/tty.h>
#include <sys/stdio.h>
#include <memory/gdt.h>
#include <memory/paging.h>
#include <memory/idt.h>
#include <memory/pic.h>
#include <memory/pit.h>
#include <drivers/keyboard.h>
#include <memory/memory.h>
#include <tty/vga.h>

extern uint32_t kernel_end;


static char *buffer = 0;
static char c = 0;
static int loc = 0;
void shell(){
    buffer = (char *)malloc(256);
    char *prompt = "(VlaDOS(PizDOS)) $ ";
    clear();
    prompt:
    printf("%s", prompt);
    memset(buffer, 0, 256);
    if (!keyboard_enabled()) {
        panic("Keyboard not enabled!");
    }

    while (1) {
        c = keyboard_get_key();
        if(c=='\b' && loc != 0){
            erase();
            loc--;
            buffer[loc]=0;
        }
        if (c=='\n'){
            putchar('\n');
            if(buffer[0]!=0) {
                if (!strcmp(buffer,"ily")) {
                    printf("I love you my sunshine <3\n");
                }
                if (!strcmp(buffer,"sergey pidor")) {
                    printf("Sam pidor!\n");
                }
                if(!strcmp(buffer,"cls")){
                    clear();
                }
                if(!strcmp(buffer,"vgatest")){
                    printf("Testing VGA\n");
                    for(int i = 50; i < 100;i++){
                        for(int g = 100;i< 200;i++){
                            putpixel(i,g,VGA_COLOR_RED);
                        }
                    }
                }


            }
            loc = 0;
            goto prompt;
        }
        if (c && c!='\b') {
            buffer[loc]=c;
            loc++;
            putchar(c);
        }
    }
}

void kernel_main(void){
    terminal_initialize();
    mm_init(&kernel_end);
    init_gdt();
    idt_init();
    exception_init();
    pic_init();
    pit_init();
    asm volatile("sti");
    paging_init();
    keyboard_init();
    printf("Running shell\n");
    shell();
}


