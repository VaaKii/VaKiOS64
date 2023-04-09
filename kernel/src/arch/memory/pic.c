#include <sys/stdio.h>
#include <memory/pic.h>

uint8_t inportb(uint16_t portid) {
    uint8_t ret;
    asm volatile("inb %%dx,%%al":"=a"(ret):"d"(portid));
    return ret;
}

uint16_t inportw(uint16_t portid) {
    uint16_t ret;
    asm volatile("inw %%dx,%%ax":"=a"(ret):"d"(portid));
    return ret;
}

uint32_t inportl(uint16_t portid) {
    uint32_t ret;
    asm volatile("inl %%dx,%%eax":"=a"(ret):"d"(portid));
    return ret;
}

void outportb(uint16_t portid, uint8_t val) {
    asm volatile("outb %%al,%%dx": :"d"(portid), "a"(val));
}

void outportw(uint16_t portid, uint16_t val) {
    asm volatile("outw %%ax,%%dx": :"d"(portid), "a"(val));
}

void outportl(uint16_t portid, uint32_t val) {
    asm volatile("outl %%eax,%%dx": :"d"(portid), "a"(val));
}

void pic_init() {
/* First step is to save current masks, set by BIOS */
    printf("Beginning initialization\n");
/* set up cascading mode */
    outportb(PIC_MASTER_CMD, 0x10 + 0x01);
    outportb(PIC_SLAVE_CMD, 0x10 + 0x01);
/* Setup master's vector offset */
    outportb(PIC_MASTER_DATA, 0x20);
/* Tell the slave its vector offset */
    outportb(PIC_SLAVE_DATA, 0x28);
/* Tell the master that he has a slave */
    outportb(PIC_MASTER_DATA, 4);
    outportb(PIC_SLAVE_DATA, 2);
/* Enabled 8086 mode */
    outportb(PIC_MASTER_DATA, 0x01);
    outportb(PIC_SLAVE_DATA, 0x01);

    printf("Resetting masks\n");
    outportb(PIC_MASTER_DATA, 0);
    outportb(PIC_SLAVE_DATA, 0);
    printf("Init done.\n");
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) { outportb(PIC_SLAVE_CMD, PIC_CMD_EOI); }
    outportb(PIC_MASTER_CMD, PIC_CMD_EOI);
}