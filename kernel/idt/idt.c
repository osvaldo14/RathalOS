#include "../../common/types.h"
#include "idt.h"
#include "../x86.h"
#include "../display/display.h"
#include "../../common/func.h"
#include "../drivers/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/pic.h"
#include "../task/task.h"
//#include "../syscalls/syscall.c"

// CPU context used when saving/restoring context from an interrupt
typedef struct regs_st {
	uint32_t gs, fs, es, ds;
	uint32_t ebp, edi, esi;
	uint32_t edx, ecx, ebx, eax;
	uint32_t number, error_code;
	uint32_t eip, cs, eflags, esp, ss;
} regs_t;

static idt_ptr_t idt_ptr;

// Build and return an IDT entry.
// selector is the code segment selector to access the ISR
// offset is the address of the ISR (for task gates, offset must be 0)
// type indicates the IDT entry type
// dpl is the privilege level required to call the associated ISR
static idt_entry_t idt_build_entry(uint16_t selector, uint32_t offset, uint8_t type, uint8_t dpl) {
	idt_entry_t entry;
	entry.offset15_0 = offset & 0xffff;
	entry.selector = selector;
	entry.reserved = 0;
	entry.type = type;
	entry.dpl = dpl;
	entry.p = 1;
	entry.offset31_16 = (offset >> 16) & 0xffff;
	return entry;
}

// Exception handler
void exception_handler(regs_t *regs) {
	// prints a message with the exception type as well as its number and stops the OS
	change_color(0x0A);
	switch(regs->number){
		case 0: printf("DIVIDE ERROR");
		break;
		case 1: printf("RESERVED");
		break;
		case 2: printf("NMI INTERRUPT");
		break;
		case 3: printf("BREAKPOINT");
		break;
		case 4: printf("OVERFLOW");
		break;
		case 5: printf("BOUND RANGE EXCEEDED");
		break;
		case 6: printf("INVALID OPCODE");
		break;
		case 7: printf("DIVICE NOT AVAILABLE");
		break;
		case 8: printf("DOUBLE FAULT");
		break;
		case 9: printf("COPROCESSOR SEGMENT OVERRUN");
		break;
		case 10: printf("INVALID TSS");
		break;
		case 11: printf("SEGMENT NOT PRESENT");
		break;
		case 12: printf("STACK SEGMENT FAULT");
		break;
		case 13: printf("GENERAL PROTECTION");
		break;
		case 14: printf("PAGE FAULT");
		break;
		case 15: printf("INTEL RESERVED");
		break;
		case 16: printf("X87 FPU");
		break;
		case 17: printf("ALIGNMENT CHECK");
		break;
		case 18: printf("MACHINE CHECK");
		break;
		case 19: printf("SIMD FLOATING POINT EXCEPTION");
		break;
		case 20: printf("VIRTUALIZATION EXCEPTION");
		break;
	}
	change_color(0x0C);
	halt();
}

// IRQ handler
void irq_handler(regs_t *regs) {
	// handles timer and keyboard interrupts and ignore others
	change_color(0x0A);
	switch(regs->number){
		case 0: 
				timer_handler();
				break;
		case 1: 
				keyboard_handler();
				break;
		case 2: printf("IQR EXCEPTION NUMBER 2");
				break;
		case 3: printf("IQR EXCEPTION NUMBER 3");
				break;
		case 4: printf("IQR EXCEPTION NUMBER 4");
				break;
		case 5: printf("IQR EXCEPTION NUMBER 5");
				break;
		case 6: printf("IQR EXCEPTION NUMBER 6");
				break;
		case 7: printf("IQR EXCEPTION NUMBER 7");
				break;
		case 8: printf("IQR EXCEPTION NUMBER 8");
				break;
		case 9: printf("IQR EXCEPTION NUMBER 9");
				break;
		case 10: printf("IQR EXCEPTION NUMBER 10");
				break;
		case 11: printf("IQR EXCEPTION NUMBER 11");
				break;
		case 12: printf("IQR EXCEPTION NUMBER 12");
				break;
		case 13: printf("IQR EXCEPTION NUMBER 13");
				break;
		case 14: // raised when hard drive is loaded in OS
				break; 
		case 15: printf("IQR EXCEPTION NUMBER 15");
				break;
	}
	change_color(0x0C);
	pic_eoi(regs->number);
}

void idt_init() {
	idt_entry_t idt[256];
	memset(idt,0,sizeof(idt_entry_t));

	idt[0] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception0,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[1] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception1,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[2] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception2,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[3] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception3,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[4] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception4,TYPE_INTERRUPT_GATE,DPL_KERNEL);

	idt[5] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception5,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[6] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception6,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[7] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception7,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[8] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception8,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[9] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception9,TYPE_INTERRUPT_GATE,DPL_KERNEL);

	idt[10] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception10,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[11] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception11,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[12] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception12,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[13] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception13,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[14] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception14,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	
	idt[15] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception15,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[16] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception16,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[17] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception17,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[18] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception18,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[19] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception19,TYPE_INTERRUPT_GATE,DPL_KERNEL);

	idt[20] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_exception20,TYPE_INTERRUPT_GATE,DPL_KERNEL);



	idt[32] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception0,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[33] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception1,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[34] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception2,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[35] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception3,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[36] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception4,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[37] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception5,TYPE_INTERRUPT_GATE,DPL_KERNEL);

	idt[38] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception6,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[39] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception7,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[40] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception8,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[41] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception9,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[42] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception10,TYPE_INTERRUPT_GATE,DPL_KERNEL);

	idt[43] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception11,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[44] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception12,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[45] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception13,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[46] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception14,TYPE_INTERRUPT_GATE,DPL_KERNEL);
	idt[47] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR,(uint_t)_IRQexception15,TYPE_INTERRUPT_GATE,DPL_KERNEL);

	idt_ptr.base = (uint32_t)&idt;
	idt_ptr.limit = sizeof(idt) - 1; 

	// IDT entry 48: used for system calls
	extern void _syscall_handler();  // Implemented in interrupt_asm.s
	idt[48] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_syscall_handler, TYPE_TRAP_GATE, DPL_USER);

	idt_load(&idt_ptr);

}
