
#ifndef VAKIOS64_IDT_H
#define VAKIOS64_IDT_H

#include <stdint.h>
#include <sys/stdio.h>

typedef struct {
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
    uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
    uint8_t     reserved;     // Set to zero
    uint8_t     attributes;   // Type and attributes; see the IDT page
    uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t	limit;
    uint32_t	base;
} __attribute__((packed)) idtr_t;

#define INT_START asm volatile("pusha");
#define INT_END asm volatile("popa"); \
	asm volatile("iret");

void idt_set_descriptor(uint8_t i,void* callback);
void idt_init();
void exception_init();
void __idt_test_handler();


#endif //VAKIOS64_IDT_H
