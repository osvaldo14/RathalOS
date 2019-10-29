CC=gcc -static -Tkernel.ld -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -g
CB=gcc -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -g
CA=nasm -f elf32 -o
CX=gcc -MMD
AA= ./gdt/*.o ./idt/*.o ./drivers/*.o ../common/*.o ./fs/*.o ../common/fs/*.o
XX= ../common/*.o ../common/*.d ../common/fs/*.o ../common/fs/*.d 


kernel.elf: kernel.o bootstrap_asm.o display.o PIO_asm.o task.o task_asm.o syscall.o syscall_asm.o
	$(MAKE) -C gdt
	$(MAKE) -C idt
	$(MAKE) -C drivers
	$(MAKE) -C fs
	$(MAKE) -C ../common
	$(CC) $^ $(AA) -o $@

kernel.o: kernel.c 
	$(CB) -c $< -o $@

bootstrap_asm.o: boot/bootstrap_asm.s
	$(CA) $@ $<

display.o : display/display.c display/display.h
	$(CB) -c $< -o $@

PIO_asm.o: PIO/PIO_asm.s
	$(CA) -c $< -o $@

task.o: task/task.c
	$(CB) -c $< -o $@

task_asm.o: task/task_asm.s
	$(CA) -c $< -o $@

syscall.o: syscalls/syscall.c
	$(CB) -c $< -o $@

syscall_asm.o: syscalls/syscall_asm.s
	$(CA) -c $< -o $@


clean:
	rm -f *.elf *.o $(XX) 
	$(MAKE) clean -C fs
	$(MAKE) clean -C drivers
	$(MAKE) clean -C gdt
	$(MAKE) clean -C idt
