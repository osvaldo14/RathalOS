#include "boot/multiboot.h"
#include "display/display.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "drivers/timer.h"
#include "drivers/pic.h"
#include "drivers/keyboard.h"
#include "x86.h"
#include "task/task.h"
#include "../user/wrapper.h"


#include "drivers/ide.h"



int kernel_main(multiboot_info_t *infos){

	multiboot_uint32_t memory_info = infos->mem_upper;


	init_screen();
	printf("Screen initialized \n");

	gdt_init();
	idt_init();
	printf("GDT & IDT initialized \n");

	keyboard_init();
	printf("Keyboard initialized \n");
	timer_init( 100 );

	printf("Timer initialized \n");

	pic_init();
	sti();

	files_system_init();

	printf("\nWelcome to RathalOS by Osvalles Pinter & Gildo Guggo \n");

	char * lama = "splash.txt";

	stat_t * stats;

	char buffer[1024];
	int fd = file_open(lama);

	exec("shell");

}
