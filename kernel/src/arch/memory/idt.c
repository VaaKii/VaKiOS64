#include <memory/idt.h>

__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

static idtr_t idtr;

static uint8_t test_success = 0;
static uint32_t test_timeout = 0x1000;

static uint8_t  __idt_setup = 0;

extern void __idt_default_handler(void);

void idt_init(){
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * 255;
    __idt_setup = 1;
    for (uint8_t i = 0;i< 255;i++){
        idt_set_descriptor(i,&__idt_default_handler);
    }
    idt_set_descriptor(0x2f,&__idt_test_handler);

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    printf("Test IDT\n");
    asm volatile("int $0x2f");
    while(test_timeout-- != 0){
        if(test_success != 0){
            printf("Test success!\n");
            idt_set_descriptor(0x2f,&__idt_default_handler);
            break;            }
    }
    if(!test_success) panic("Test failed!(timeout)\n");
    __idt_setup = 0;
    return;
}


void __idt_test_handler()
{
    INT_START;
    test_success = 1;
    INT_END;
}

void idt_set_descriptor(uint8_t i, void* callback){
    idt_entry_t* descriptor = &idt[i];

    descriptor->isr_low = (uint32_t)callback & 0xFFFF;
    descriptor->kernel_cs = 0x08;
    descriptor->attributes = 0x8e; //I'll find out what they're for.
    descriptor->isr_high = (uint32_t)callback >> 16;
    descriptor->reserved = 0;
    if(test_success) printf("Registered INT#%d\n",i);
    return;
}



