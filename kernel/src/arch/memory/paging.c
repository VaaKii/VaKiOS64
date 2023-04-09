#include <memory/paging.h>
#include <stdint.h>
#include <sys/stdio.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1024] __attribute__((aligned(4096)));


void paging_enable()
{
    asm volatile("mov %%eax, %%cr3": :"a"(&page_directory[0]));
    asm volatile("mov %cr0, %eax");
    asm volatile("orl $0x80000000, %eax");
    asm volatile("mov %eax, %cr0");
}

void paging_init(){
    printf("Setting up paging\n");
    for(int i = 0;i<1024;i++){
        page_directory[i] = 0 | 2;
    }

    for(unsigned int i = 0; i < 1024; i++)
    {
        first_page_table[i] = (i * 0x1000) | 3;
    }
    page_directory[0] = ((unsigned int)first_page_table | 3);
    paging_enable();
    printf("Paging is set!\n");
}