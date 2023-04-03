#include <memory/gdt.h>
#include <sys/stdio.h>

extern void _set_gdtr(void);
extern void _reload_segments(void);


static uint32_t gdt_pointer = 0;
static uint32_t gdtr_loc = 0;
static uint32_t gdt_size = 0;

void init_gdt(){
    gdt_pointer = 0x606;
    gdtr_loc = 0x600;
    add_descriptor(0,0);
    add_descriptor(1, create_descriptor(0,0x000FFFFF,(GDT_CODE_PL0)));
    add_descriptor(2, create_descriptor(0,0x000FFFFF, (GDT_DATA_PL0)));
    add_descriptor(3, create_descriptor(0,0x000FFFFF,(GDT_CODE_PL3)));
    add_descriptor(4, create_descriptor(0,0x000FFFFF, (GDT_DATA_PL3)));
    set_descriptor();
    printf("GDT is alive!\n");
}

int set_descriptor(){
    *(uint16_t*)gdtr_loc = (gdt_size - 1) & 0x0000ffff; // -1 because gdt counts to 65536 for some reason. WHY? I DO NOT KNOW! 0:15 bits set limit
    gdtr_loc += 2; // add 2 bytes
    *(uint32_t*)gdtr_loc = gdt_pointer; // set pointer an another bits 16:??
    _set_gdtr();
    _reload_segments();
    return 0;
}


int add_descriptor(uint8_t id,uint64_t desc){
    uint32_t loc = gdt_pointer + sizeof(uint64_t) * id; // Create location in memory
    *(uint64_t*)loc = desc; // Set GDT descriptor
    gdt_size += sizeof(desc); // Need for limit of GDT
    return 0;
}

uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
    uint64_t descriptor;

    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24

    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;

    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0

    return descriptor;
}