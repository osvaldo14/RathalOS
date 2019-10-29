#ifndef _IDT_H_
#define _IDT_H_

// Structure of an IDT descriptor. There are 3 types of descriptors:
// a task-gate, an interrupt-gate, and a trap-gate.
// See 5.11 of Intel 64 & IA32 architectures software developer's manual for more details.
// For task gates, offset must be 0.
typedef struct idt_entry_st {
	uint16_t offset15_0;   // only used by trap and interrupt gates
	uint16_t selector;     // segment selector for trap and interrupt gates; TSS segment selector for task gates
	uint16_t reserved : 8;
	uint16_t type : 5;
	uint16_t dpl : 2;
	uint16_t p : 1;

	uint16_t offset31_16;  // only used by trap and interrupt gates
} __attribute__((packed)) idt_entry_t;

// Structure describing a pointer to the IDT gate table.
// This format is required by the lidt instruction.
typedef struct idt_ptr_st {
	uint16_t limit;   // Limit of the table (ie. its size)
	uint32_t base;    // Address of the first entry
} __attribute__((packed)) idt_ptr_t;

extern void idt_init();
extern void idt_load();

extern void _exception0();
extern void _exception1();
extern void _exception2();
extern void _exception3();
extern void _exception4();

extern void _exception5();
extern void _exception6();
extern void _exception7();
extern void _exception8();
extern void _exception9();

extern void _exception10();
extern void _exception11();
extern void _exception12();
extern void _exception13();
extern void _exception14();

extern void _exception15();
extern void _exception16();
extern void _exception17();
extern void _exception18();
extern void _exception19();

extern void _exception20();

extern void _IRQexception0();
extern void _IRQexception1();
extern void _IRQexception2();
extern void _IRQexception3();
extern void _IRQexception4();

extern void _IRQexception5();
extern void _IRQexception6();
extern void _IRQexception7();
extern void _IRQexception8();
extern void _IRQexception9();

extern void _IRQexception10();
extern void _IRQexception11();
extern void _IRQexception12();
extern void _IRQexception13();
extern void _IRQexception14();

extern void _IRQexception15();

#endif
