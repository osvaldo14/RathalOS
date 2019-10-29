#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "../PIO/PIO_asm.h"
#include "../../common/types.h"
#include "../../common/func.h"

#define CURSOR_COMMAND_REGISTER 0x3d4
#define CURSOR_DATA_REGISTER 0x3d5
#define SCREEN_REGISTER 0xB8000
#define COLUMN_SIZE 25
#define LINE_SIZE 80
#define SCREEN_SIZE 80*25
#define BASE_COLOR 0x0C


/* ----- FUNCTIONS PROTO ----- */


//Initialize by cleaning the screen and put the cursor uint_t the top left.
void init_screen();

//Erase all content of the screen
void clean_screen();

//Change color of background and text
void change_color(uint8_t new_color);

//Get the color of text and background
uint16_t get_color();

//Display a caracter at the cursor current location
void display_carac(uchar_t carac);

//Display a string at the cursor current location
void display_string(uchar_t* string);

//Change the cursor current position
void change_cursor_pos(uint16_t pos);

//Get the current location of the cursor
uint16_t get_cursor_pos();

//Display a formated string
void printf(char* fmt, ...);

//Display a carac at the given position
void display_carac_at_pos(uint16_t pos, uchar_t carac);

//Display graphic to test the timer
void time_graphic(uint_t tick, uint_t freq);
void graphic_state1();
void graphic_state2();
void read_line(char* buf);


#endif