#ifndef _TIMER_H_
#define _TIMER_H_

#define TIMER_DIVIDER 360082
#define COMMAND_REGISTER 0x43
#define CANAL0 0x40
#define CANAL1 0x41
#define CANAL2 0x42

#include "../display/display.h"
#include "../../common/types.h"
#include "../PIO/PIO_asm.h"


typedef struct timer_struct
{
	uint_t tick;
	ushort_t freq;
	uint_t divider;

} timer_struct_t;

extern void timer_init(uint32_t freq_hz);
extern void timer_handler();
extern uint_t get_ticks();
extern void sleep(uint_t ms);

#endif
