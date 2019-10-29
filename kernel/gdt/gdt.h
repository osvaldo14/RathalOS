#ifndef _GDT_H_
#define _GDT_H_

#include "../../common/types.h"

#define GDT_INDEX_TO_SELECTOR(idx) ((idx) << 3)

// Structure of a GDT descriptor. There are 2 types of descriptors: segments and TSS.
// Section 3.4.5 of Intel 64 & IA32 architectures software developer's manual describes
// segment descriptors while section 6.2.2 describes TSS descriptors.
typedef struct gdt_entry_st {
	uint16_t lim15_0;
	uint16_t base15_0;
	uint8_t base23_16;

	uint8_t type : 4;
	uint8_t s : 1;
	uint8_t dpl : 2;
	uint8_t present : 1;

	uint8_t lim19_16 : 4;
	uint8_t avl : 1;
	uint8_t l : 1;
	uint8_t db : 1;
	uint8_t granularity : 1;

	uint8_t base31_24;
} __attribute__((packed)) gdt_entry_t;

extern gdt_entry_t gdt_table[24];

// Structure describing a pointer to the GDT descriptor table.
// This format is required by the lgdt instruction.
typedef struct gdt_ptr_st {
	uint16_t limit;    // Limit of the table (ie. its size)
	uint32_t base;     // Address of the first entry
} __attribute__((packed)) gdt_ptr_t;

extern void gdt_init();
extern uint_t gdt_entry_to_selector(gdt_entry_t *entry);
extern void gdt_load(gdt_ptr_t *gdt_ptr);
extern gdt_entry_t gdt[100];

extern gdt_entry_t gdt_make_null_segment();
extern gdt_entry_t gdt_make_code_segment(uint32_t base, uint32_t limit, uint8_t dpl);
extern gdt_entry_t gdt_make_data_segment(uint32_t base, uint32_t limit, uint8_t dpl);

struct tss_st;

extern gdt_entry_t gdt_make_tss(struct tss_st *tss, uint8_t dpl);
extern gdt_entry_t gdt_make_ldt(uint32_t base, uint32_t limit, uint8_t dpl);

#endif
