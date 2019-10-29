#include "../../common/types.h"
#include "../../common/func.h"
#include "task.h"
#include "../x86.h"
#include "../fs/fs.h"

// task array
task_t task_table[MAX_TASK_COUNT];

// TSS of the task
// static tss_t task_tss;
// LDT of the task
// static gdt_entry_t task_ldt[2];
// Allocate 16KB of address space for the task
// static uint8_t task_addr_space[16834] __attribute__((aligned(4096)));
// Allocate 4KB of kernel stack for the task
// static uint8_t task_kernel_stack[4096];

void task_ltr(uint16_t tss_selector);


// inspired by MM Zaffini & Vanino's "work"
// Setup the memory space and context for a task
// gdt[4] stores the task's TSS descriptor
// gdt[5] stores the task's LDT descriptor
void task_setup() {


	for(int index = 0; index < 10; index ++){
		memset(&task_table[index].task_tss, 0, sizeof(tss_t));

		// Add the task's TSS and LDT to the GDT
		gdt_table[GDT_RESERVED_ENTRIES + (2 * index)	] = gdt_make_tss(&task_table[index].task_tss, DPL_KERNEL);
		gdt_table[GDT_RESERVED_ENTRIES + (2 * index) + 1] = gdt_make_ldt((uint32_t)task_table[index].task_ldt, sizeof(task_table[index].task_ldt)-1, DPL_KERNEL);
		
		int gdt_tss_sel = gdt_entry_to_selector(&gdt_table[GDT_RESERVED_ENTRIES + (2 * index)    ]);
		int gdt_ldt_sel = gdt_entry_to_selector(&gdt_table[GDT_RESERVED_ENTRIES + (2 * index) + 1]);

		// Define code and data segments in the LDT; both segments are overlapping
		int ldt_code_idx = 0;  // Index of code segment descriptor in the LDT
		int ldt_data_idx = 1;  // Index of data segment descriptor in the LDT

		uint_t limit = sizeof(task_table[index].task_addr_space);  // Limit for both code and data segments
		task_table[index].task_ldt[ldt_code_idx] = gdt_make_code_segment(*task_table[index].task_addr_space, limit / 4096, DPL_USER);
		task_table[index].task_ldt[ldt_data_idx] = gdt_make_data_segment(*task_table[index].task_addr_space, limit / 4096, DPL_USER);

		// Initialize the TSS fields
		// The LDT selector must point to the task's LDT
		task_table[index].task_tss.ldt_selector = gdt_ldt_sel;
		task_table[index].tss_selector = gdt_tss_sel;

		// Setup code and stack pointers
		task_table[index].task_tss.eip = 0;
		task_table[index].task_tss.esp = task_table[index].task_tss.ebp = limit;  // stack pointers

		// Code and data segment selectors are in the LDT
		task_table[index].task_tss.cs = GDT_INDEX_TO_SELECTOR(ldt_code_idx) | DPL_USER | LDT_SELECTOR;
		task_table[index].task_tss.ds = task_table[index].task_tss.es = task_table[index].task_tss.fs = task_table[index].task_tss.gs = task_table[index].task_tss.ss = GDT_INDEX_TO_SELECTOR(ldt_data_idx) | DPL_USER | LDT_SELECTOR;
		
		task_table[index].task_tss.eflags = (1 << 9);  // Activate hardware interrupts (bit 9)

		// Task's kernel stack
		task_table[index].task_tss.ss0 = GDT_KERNEL_DATA_SELECTOR;
		task_table[index].task_tss.esp0 = (uint32_t)(task_table[index].task_kernel_stack) + sizeof(task_table[index].task_kernel_stack);
	}
}

extern void task_switch(uint16_t tss_selector);

int exec(char* filename){
	stat_t stats;
	int success = file_stat(filename, &stats);
	if(success){
		int fd = file_open(filename);
		int index = 0;
		while(task_table[index].status && index < MAX_TASK_COUNT){
			index++;
		}

		if(index >= MAX_TASK_COUNT){
			return TASK_FAILURE;
		} else {
			task_table[index].status = 1;
			file_read(fd, task_table[index].task_addr_space, stats.size);
			file_close(fd);
			task_switch(task_table[index].tss_selector);
			return TASK_SUCCESS;
		}
	} else {
		return TASK_FAILURE;
	}
}

