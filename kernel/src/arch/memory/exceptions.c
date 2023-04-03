#include <memory/idt.h>

void exc_divide_by_zero()
{
    panic("Divide by zero!\n");
}

void exc_debug()
{
    panic("Debug!\n");
}

void exc_nmi()
{
    panic("NMI\n");
}

void exc_brp()
{
    panic("Breakpoint!\n");
}

void exc_overflow()
{
    panic("Overflow!\n");
}

void exc_bound()
{
    panic("Bound range exceeded.\n");
}

void exc_invopcode()
{
    printf("Invalid opcode.\n");
}

void exc_device_not_avail()
{
    panic("Device not available.\n");
}

void exc_double_fault()
{
    panic("Double fault, halting.\n");
}

void exc_coproc()
{
    panic("Coprocessor fault, halting.\n");
}

void exc_invtss()
{
    panic("TSS invalid.\n");
}

void exc_segment_not_present()
{
    panic("Segment not present.\n");
}

void exc_ssf()
{
    printf("Stacksegment faulted.\n");
}

void exc_gpf()
{
    printf("PIZDA!: General protection fault.\n");
}


void exc_reserved()
{
    panic("This shouldn't happen. Halted.\n");
}

void exception_init()
{
    printf("Installing exceptions handlers\n");
    idt_set_descriptor(0, exc_divide_by_zero);
    idt_set_descriptor(1, exc_debug);
    idt_set_descriptor(2, exc_nmi);
    idt_set_descriptor(3, exc_brp);
    idt_set_descriptor(4, exc_overflow);
    idt_set_descriptor(5, exc_bound);
    idt_set_descriptor(6, exc_invopcode);
    idt_set_descriptor(7, exc_device_not_avail);
    idt_set_descriptor(8, exc_double_fault);
    idt_set_descriptor(9, exc_coproc);
    idt_set_descriptor(10, exc_invtss);
    idt_set_descriptor(11, exc_segment_not_present);
    idt_set_descriptor(12, exc_ssf);
    idt_set_descriptor(13, exc_gpf);
    idt_set_descriptor(15, exc_reserved);
    return;
}