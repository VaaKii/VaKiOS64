cmake_minimum_required(VERSION 3.24)
project(VaKiOS64 C)

set(CMAKE_C_STANDARD 11)

include_directories(kernel)
include_directories(kernel/include)
include_directories(kernel/include/memory)
include_directories(kernel/include/sys)
include_directories(kernel/include/tty)

add_executable(VaKiOS64
        kernel/include/memory/gdt.h
        kernel/include/sys/stdio.h
        kernel/include/tty/tty.h
        kernel/src/arch/memory/gdt.c
        kernel/src/arch/sys/stdio.c
        kernel/src/arch/vga/tty.c
        kernel/src/arch/kernel.c kernel/include/memory/idt.h kernel/src/arch/memory/idt.c kernel/include/memory/memory.h kernel/src/arch/memory/memory.c kernel/src/arch/memory/exceptions.c)
