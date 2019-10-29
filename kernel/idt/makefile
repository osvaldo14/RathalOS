CB=gcc -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -g
CA=nasm -f elf32 -o

all: idt.o idt_asm.o

idt.o: idt.c idt.h
	$(CB) -c $< -o $@

idt_asm.o: idt_asm.s
	$(CA) $@ $<

clean:
	rm -f *.o