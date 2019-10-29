CreateIso=grub-mkrescue -o RathalOS.iso myos

elf: makefile
	$(MAKE) -C kernel

transfer:
	$(shell mv kernel/kernel.elf myos/boot)

iso:
	$(CreateIso)

all: clean elf transfer iso

run: all
	qemu-system-i386 -m 128 -cdrom RathalOS.iso -drive file=RathalFS.img,index=0,media=disk,format=raw

clean:
	rm -f RathalOS.iso myos/boot/kernel.elf
	$(MAKE) clean -C kernel