#include "../../common/syscall_nb.h"
#include "../../common/types.h"
#include "../../common/func.h"
#include "../display/display.h"
#include "../drivers/keyboard.h"
#include "../drivers/shell_drivers.h"
#include "../drivers/timer.h"
#include "../task/task.h"
#include "../gdt/gdt.h"
#include "../fs/fs.h"


#define UNUSED(x) ((void)(x))

int syscall_puts(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	display_string((char*)arg1);
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_exec(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg2 = (uint32_t)exec((char*)arg1);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_keypressed(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg1 = keypressed();
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_getc(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int *)arg1 = getc();
	UNUSED(arg1);
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_file_stat(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int *)arg3 = file_stat((char*)arg1, (stat_t*)arg2);
	UNUSED(arg4);	
	return 0;
}

int syscall_file_open(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg2 = file_open((char*)arg1);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_file_read(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg4 = file_read((int)arg1,(void*)arg2,(uint_t)arg3);	
	return 0;
}

int syscall_file_close(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	file_close((int)arg1);
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_file_seek(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg3 = file_seek((int)arg1,(uint_t)arg2);
	UNUSED(arg4);	
	return 0;
}

int syscall_file_remove(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg2 = file_remove((char*)arg1);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_file_iterator(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(file_iterator_t*)arg1 = file_iterator();
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_file_has_next(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg2 = file_has_next((file_iterator_t*)arg1);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_file_next(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	file_next((char*)arg1, (file_iterator_t*)arg2);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_get_ticks(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg1 = get_ticks();
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_putc(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	display_carac(*(char*)arg1);
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_printf(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	char** argv = (char**)arg2;
	printf((char*)arg1,*argv );
	UNUSED(arg3);
	UNUSED(arg4);	
	return 0;
}

int syscall_srand(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);	
	//srand((uint_t)arg1);
	return 0;
}

int syscall_rand(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	UNUSED(arg1);
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);
	//rand();	
	return 0;
}

int syscall_sleep(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	sleep((uint_t)arg1);
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);
	return 0;
}

int syscall_exit(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	UNUSED(arg1);
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);
	exit();
	return 0;
}


int syscall_strlen(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg2 = strlen((char*)arg1);
	UNUSED(arg3);
	UNUSED(arg4);
	return 0;
}

int syscall_strcmp(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	*(int*)arg3 = strcmp((char*)arg1,(char*)arg2);
	UNUSED(arg4);
	return 0;
}

int syscall_read_string(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	read_string((char*)arg1);
	UNUSED(arg2);
	UNUSED(arg3);
	UNUSED(arg4);
	return 0;
}


int (*func_syscalls[23])(uint32_t, uint32_t, uint32_t, uint32_t) = {
	&syscall_puts,
	&syscall_exec,
	&syscall_keypressed,
	&syscall_getc,
	&syscall_file_stat,
	&syscall_file_open,
	&syscall_file_read,
	&syscall_file_close,
	&syscall_file_seek,
	&syscall_file_remove,
	&syscall_file_iterator,
	&syscall_file_has_next,
	&syscall_file_next,
	&syscall_get_ticks,
	&syscall_putc,
	&syscall_printf,
	&syscall_srand,
	&syscall_rand,
	&syscall_sleep,
	&syscall_exit,
	&syscall_strlen,
	&syscall_strcmp,
	&syscall_read_string
};

// System call handler: call the appropriate system call according to the nb argument.
// Called by the assembly code _syscall_handler
int syscall_handler(syscall_t nb, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t caller_tss_selector) {
	// voir cours Adressage_memoire_et_protection.pdf page 17 pour plus de détail
	gdt_entry_t descriptor = task_table[(caller_tss_selector >> 3) - 4].task_ldt[1];
	// base de la tache dans la memoire
	int base = (((uint32_t)(descriptor.base31_24)) << 24) | (((uint32_t)(descriptor.base23_16)) << 16) | (uint32_t)descriptor.base15_0;
	return (*func_syscalls[nb])(base + arg1, base + arg2, base + arg3, base + arg4);
}

