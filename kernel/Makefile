CC = i686-elf-gcc
CC_FLAGS = -std=gnu99 -g -ffreestanding -O2 -Wall -Wextra -Iinclude
ARCH_DIR = src/arch

include $(ARCH_DIR)/make.config

.PHONY: all
.SUFFIXES: .o .c .asm


myos.kernel: $(OBJS)
	$(CC) -T $(ARCH_DIR)/linker/link.ld -o myos.kernel -nostdlib -lgcc -ffreestanding $(OBJS)
	grub-file --is-x86-multiboot myos.kernel



.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

.asm.o:
	nasm -felf32 $< -o $@ -Wall

all: myos.kernel clean
clean:
	rm $(ARCH_DIR)/*/*.o $(ARCH_DIR)/*.o