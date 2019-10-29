CB=gcc -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -g
CA=nasm -f elf32 -o

all: gdt.o gdt_asm.o

gdt.o: gdt.c gdt.h
	$(CB) -c $< -o $@

gdt_asm.o: gdt_asm.s
	$(CA) $@ $<

clean:
	rm -f *.o