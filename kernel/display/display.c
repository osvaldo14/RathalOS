#include "display.h"


//Global value for the current color
uint8_t CURRENT_COLOR = BASE_COLOR;
static int state = 1;

void init_cursor();

//Initialize by cleaning the screen and put the cursor in the top left.
void init_screen(){
	clean_screen();
	init_cursor();

	/*Put the cursor in the init position*/

	change_cursor_pos(0);

}

void init_cursor(){

	//activate cursor 
	
	//uint8_t cursor_data = inb(CURSOR_DATA_REGISTER);
	outb(CURSOR_COMMAND_REGISTER, 0xA);
	outb(CURSOR_DATA_REGISTER, 0xE);
	
	// set cursor style
	
	//cursor_data = inb(CURSOR_DATA_REGISTER);
	outb(CURSOR_COMMAND_REGISTER, 0xB);
	outb(CURSOR_DATA_REGISTER, 0x1F);
	

}

//Erase all content of the screen
void clean_screen(){
	//Pointing the the first pixel of the screen
	uint16_t *p = (uint16_t *)SCREEN_REGISTER;

	/*Loop to clean the screen*/
	for (uint_t i = 0; i < SCREEN_SIZE; i++)
	{
		*p = 0x0C00;
		p++;
	}
}

//Change color of background and text
void change_color(uint8_t new_color){
	CURRENT_COLOR = new_color;
}

//Get the color of text and background
uint16_t get_color(){
	//first 8 bites are the color and background
	return CURRENT_COLOR;
}

//Display a caracter at the cursor current location
void display_carac(uchar_t carac){
	uint16_t cursor_pos = get_cursor_pos();
	switch(carac){
		case 0xA : cursor_pos += 80 - (cursor_pos % 80); break;
		default : {
			//Pointer at the cursor position in screen
			uint16_t *p = (uint16_t*)SCREEN_REGISTER + cursor_pos;
			//write the carac
			*p = (CURRENT_COLOR << 8) | carac;
			//inc the pos cursor by one
			cursor_pos++;
		}
		
		change_cursor_pos(cursor_pos);  

	}
}

//Display a string at the cursor current location
void display_string(uchar_t* string){
	uint_t i = 0;
	while(string[i]){
		display_carac(string[i]);
		i++;
	}
}

//Change the cursor current position
void change_cursor_pos(uint16_t pos){
	if(pos < (SCREEN_SIZE - 1)){
		outb(CURSOR_COMMAND_REGISTER, 0xE);
		outb(CURSOR_DATA_REGISTER, (uchar_t)(pos >> 8));
		outb(CURSOR_COMMAND_REGISTER,0xF);
		outb(CURSOR_DATA_REGISTER, (uchar_t)pos);
	} else {
		// we are at the bottom of the screen
		// copy every line into the line above
		for(uint8_t y = 1; y < COLUMN_SIZE; y++){
			for(uint8_t x = 0; x < LINE_SIZE; x++){
				//Pointer at the cursor position in screen
				uint16_t *p = (uint16_t*)SCREEN_REGISTER + y * LINE_SIZE + x;
				uint16_t *new_p = (uint16_t*)SCREEN_REGISTER + (y - 1) * LINE_SIZE + x;
				//write the carac
				*new_p = *p;
			}
		}
		// clear the last line
		for(uint8_t x = 0; x < LINE_SIZE; x++){
			display_carac_at_pos(SCREEN_SIZE - LINE_SIZE + x, 0x00);
		}
		change_cursor_pos(SCREEN_SIZE - LINE_SIZE);
	}
}

//Get the current location of the cursor
uint16_t get_cursor_pos(){
	uint16_t pos;

	outb(CURSOR_COMMAND_REGISTER, 0xE);

	//Read the first 8 bites
	pos = inb(CURSOR_DATA_REGISTER) << 8;

	outb(CURSOR_COMMAND_REGISTER,0xF);

	//Read the last 8 bites
	pos |= inb(CURSOR_DATA_REGISTER);

	return pos;
}

// https://www.geeksforgeeks.org/implement-itoa/
void print_int( int num, int base ){
	int i = 0;
	char ret[11];

	if( num == 0 ){
		ret[i] = '0';
		ret[++i] = '\0';
	}

	while( num != 0 ){
		int digit = num % base;
		ret[i++] = ( digit > 9 ) ? ( digit - 10 ) + 'a' : digit + '0';
		num /= base;
	}

	ret[i] = '\0';

	for(int j = i; i >= 0; i--){
		display_carac(ret[i]);
	}
}

/*
	Function to print a formated string
*/
void printf(char* fmt, ...){
	// reading head 
	uchar_t* rh = fmt;
	//arg counter
	int cnt = 0;
	do {
		if(*rh == '%'){
			switch(*(++rh)){
				case 'c' : display_carac((int)*(&fmt + ++cnt));break;
				case 's' : printf(*(&fmt + ++cnt));break;
				case 'd' : {
					int num = (int)*(&fmt + ++cnt);
					print_int(num, 10);	
					break;
				}
				case 'x' : {
					int num = (int)*(&fmt + ++cnt);
					print_int(num, 16);	
					break;
				}
				case '\0': break;
				default : break;
			}
		} else if(*rh == 0x0A){
			uint16_t newpos = get_cursor_pos();
			newpos += 80 - (newpos % 80);
			change_cursor_pos(newpos);
		} else {
			display_carac(*rh);
		} 
		
	} while(*++rh != '\0');
}


void time_graphic(uint_t tick, uint_t freq){
	// if freq = 1 -> 18.2 Hz
	if((tick % freq) == 0){		
		state = 1 - state;
		switch (state){
			case 0: 
				graphic_state1();
				break;
			case 1: 
				graphic_state2();
				break;
		}
	}
}

void display_carac_at_pos(uint16_t pos, uchar_t carac){
	uint16_t *p = (uint16_t*)SCREEN_REGISTER + pos;
	*p = (CURRENT_COLOR << 8) | carac;
}


void graphic_state1(){
	uint16_t *p = (uint16_t *)SCREEN_REGISTER + (78);
	*p = 0x0C09;
}

void graphic_state2(){
	uint16_t *p = (uint16_t *)SCREEN_REGISTER + (78);
	*p = 0x0C07;
}

// with help from zaffini and vanino
void read_line(char* buf){
	int counter = 0;

	uint16_t pos = get_cursor_pos();
	uint16_t line_start = pos-(pos%LINE_SIZE);
	uint16_t current_register = SCREEN_REGISTER + line_start + 1;
	char current_char = current_register & 0xFF;


	while(current_char != 0 && counter < LINE_SIZE){
		current_char = current_register & 0xFF;
		buf[counter] = current_char;
		current_register++;
		counter++;
	}

	buf[counter-1] = '\0';	

}