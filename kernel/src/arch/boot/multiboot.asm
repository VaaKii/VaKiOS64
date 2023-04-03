MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot


section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 32768 ; 32 KiB
stack_top:

section .text

global __idt_default_handler:function
__idt_default_handler:
    pusha
    mov al, 0x20
    mov dx, 0x20
    out dx, al
    popa
    iret

global _set_gdtr:function
_set_gdtr:
    push ebp
    mov ebp,esp
    lgdt [0x600]
    mov esp,ebp
    pop ebp
    ret

global _reload_segments:function
_reload_segments:
    push ebp
    mov ebp, esp

    push eax
    mov ax,0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    pop eax

    jmp 0x8:me
me:
    mov esp, ebp
    pop ebp
    ret

global _start:function (_start.end-_start)
_start:
    mov esp, stack_top
    extern kernel_main
    call kernel_main

    cli
    hlt
.hang:
    jmp .hang
.end:
