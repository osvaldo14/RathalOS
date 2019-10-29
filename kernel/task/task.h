#ifndef _TASK_H_
#define _TASK_H_

#include "../gdt/gdt.h"
// IMPORTANT: by default (if IOMAP is 0) all ports are accessibles from ring 3!
// Set to 1 if iomap is needed (forbid or allow access to IO ports from user mode).
// It requires an extra 8KB in the TSS to store the ports bitmap.
#define IOMAP 0
#define GDT_RESERVED_ENTRIES	4
#define MAX_TASK_COUNT			10
#define TASK_FAILURE			-1
#define TASK_SUCCESS			1


// Task-State Segment (TSS) structure.
typedef struct tss_st {
	uint16_t previous_task_link, reserved0;
	uint32_t esp0;
	uint16_t ss0, reserved1;
	uint32_t esp1;
	uint16_t ss1, reserved2;
	uint32_t esp2;
	uint16_t ss2, reserved3;
	uint32_t cr3;
	uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	uint16_t es, reserved4;
	uint16_t cs, reserved5;
	uint16_t ss, reserved6;
	uint16_t ds, reserved7;
	uint16_t fs, reserved8;
	uint16_t gs, reserved9;
	uint16_t ldt_selector, reserved10;
	uint16_t reserved11;
	uint16_t iomap_base_addr;  // adresse (relative to byte 0 of the TSS) of the IO permission bitmap
#if IOMAP
	uint8_t iomap[8192];       // IO permission bitmap for ports 0 to 0xFFFF
#endif
} __attribute__ ((packed)) tss_t;

typedef struct task_st{
	// TSS of the task
	tss_t task_tss;
	//TSS selector
	uint16_t tss_selector;
	// LDT of the task
	gdt_entry_t task_ldt[2];
	// Allocate 16KB of address space for the task
	uint8_t task_addr_space[16834] __attribute__((aligned(4096)));
	// Allocate 4KB of kernel stack for the task
	uint8_t task_kernel_stack[4096];
	//Used or unused
	uint_t status;
}__attribute__ ((packed)) task_t;

extern task_t task_table[MAX_TASK_COUNT];

void task_setup();
int exec(char* filename);

#endif
