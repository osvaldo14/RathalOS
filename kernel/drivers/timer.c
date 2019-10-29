#include "timer.h"

timer_struct_t timer;

void timer_init(uint32_t freq_hz) {
	timer.tick = 0;
	timer.freq = freq_hz;
	timer.divider = TIMER_DIVIDER / ((freq_hz*100) / 1820); // if freq = 1 -> 18.2 Hz
	outb(COMMAND_REGISTER, 0x36);
	outb(CANAL0, (uchar_t)timer.divider);
	outb(CANAL0, timer.divider >> 8);
}

void timer_handler() {
	timer.tick++;
	time_graphic(timer.tick, timer.freq);
}

uint_t get_ticks() {
	return timer.tick;
}

void sleep(uint_t ms) {
	uint_t total = get_ticks() + timer.freq * (ms/1000);
	while(get_ticks() < total);
}
