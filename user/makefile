CC=gcc
CFLAGS=-m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -Wall -Wextra -c -MMD -fno-pie 
FFLAGS =-static -T app.ld -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -fno-pie

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
DEPS=$(OBJS:%.o=%.d)

all: shell.o syscall_asm.o wrapper.o entrypoint_asm.o shell fsadd

shell:  shell.o entrypoint_asm.o syscall_asm.o wrapper.o
	$(CC) $(FFLAGS) shell.o entrypoint_asm.o syscall_asm.o wrapper.o -o shell

shell.o: shell.c
	$(CC) $(CFLAGS) $< -o $@

wrapper.o: wrapper.c
	$(CC) $(CFLAGS) $< -o $@

entrypoint_asm.o: entrypoint_asm.s
	nasm -f elf32 -o entrypoint_asm.o entrypoint_asm.s

syscall_asm.o: syscall_asm.s
	nasm -f elf32 -o syscall_asm.o syscall_asm.s

clean:
	rm -f *.o *.d *.out shell

fsadd :
	../tools/fs_del shell ../RathalFS.img
	../tools/fs_add shell ../RathalFS.img

-include $(DEPS)
