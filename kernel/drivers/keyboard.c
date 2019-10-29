#include "keyboard.h"

static uchar_t fifo_buffer[ KEY_BUFFER_SIZE ];
static uchar_t head;
static uchar_t tail;
static uchar_t size;

static bool shift;

void keyboard_init() {
	init_keymap();
	head = 0;
	tail = 0;
	shift = false;
}

void keyboard_handler() {
	// check if keyboard buffer is full
	if( !inb(KEYBOARD_STATE_REGISTER) & 0x1 )
		return;

	// get the scancode from keyboard buffer
	uchar_t scan_code = inb(KEYBOARD_DATA_REGISTER);

	// check if a key was released 
	if( ((scan_code >> 7) & 1) ){
		// check if the key is shift
		if (scan_code == 0xaa || scan_code == 0xb6)
			shift = false;
		return;
	}

	// check if shift was pressed
	if( scan_code == 0x2a || scan_code == 0x36 ){
		shift = true;
		return;
	}

	// if all checks failed, make sure the buffer has room to add the new key
	if(size >= KEY_BUFFER_SIZE){
		printf("KEYBOARD_BUFFER_OVERFLOW");
		return;
	}

	// add the key to the buffer
	fifo_buffer[head++] = scan2char( scan_code, shift );
	// 
	head = head % KEY_BUFFER_SIZE;

	size++;
	


}

int getc() {
	// wait for a key to be pressed
	while( size == 0 ){}
	int ret = fifo_buffer[tail++];
	tail = tail % KEY_BUFFER_SIZE;
	size--;
	return ret;

}

// Non-blocking call. Return 1 if a key is pressed
int keypressed() {
	return inb(KEYBOARD_STATE_REGISTER) & 0x1;
}

