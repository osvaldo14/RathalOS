#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "../../common/types.h"
#include "../PIO/PIO_asm.h"
#include "../display/display.h"
#include "key_map.h"

#define KEYBOARD_DATA_REGISTER 0x60
#define KEYBOARD_STATE_REGISTER 0x64
#define KEY_BUFFER_SIZE 256
#define ESC 0x02
#define ENTER 0x0D

extern void keyboard_init();
extern void keyboard_handler();
extern int getc();
extern int keypressed();

#endif
