#include "key_map.h"
#include "../x86.h"
#include "../../common/types.h"

static uchar_t map[128]; // 128 pressable keys
static uchar_t shift_map[128]; // shift + key

void init_keymap() {
	// initialize all map entries to empty first
	// then fill the used key codes

	for( uint_t i = 0; i<128; i++ ){
		map[i] = 0; //empty
		shift_map[i] = 0; //empty
	}

	// regular keymap
	map[0x01] = 0x02; // ESC
	map[0x02] = '1';
	map[0x03] = '2';
	map[0x04] = '3';
	map[0x05] = '4';
	map[0x06] = '5';
	map[0x07] = '6';
	map[0x08] = '7';
	map[0x09] = '8';
	map[0x0A] = '9';
	map[0x0B] = '0';

	map[0x10] = 'q';
	map[0x11] = 'w';
	map[0x12] = 'e';
	map[0x13] = 'r';
	map[0x14] = 't';
	map[0x15] = 'z';
	map[0x16] = 'u';
	map[0x17] = 'i';
	map[0x18] = 'o';
	map[0x19] = 'p';
	map[0x1e] = 'a';
	map[0x1f] = 's';
	map[0x20] = 'd';
	map[0x21] = 'f';
	map[0x22] = 'g';
	map[0x23] = 'h';
	map[0x24] = 'j';
	map[0x25] = 'k';
	map[0x26] = 'l';
	map[0x2c] = 'y';
	map[0x2d] = 'x';
	map[0x2e] = 'c';
	map[0x2f] = 'v';
	map[0x30] = 'b';
	map[0x31] = 'n';
	map[0x32] = 'm';

	map[0x27] = 0x82; // é
	map[0x28] = 0x85; // à
	map[0x1A] = 0x8A; // è
	map[0x0c] = '\'';
	map[0x33] = ',';
	map[0x34] = '.';
	map[0x35] = '-';
	map[0x56] = '<';
	map[0x1B] = 0x21; // "

	map[0x4b] = 0x1B; // left
	map[0x4d] = 0x1A; // right
	map[0x48] = 0x18; // up
	map[0x50] = 0x19; // down

	map[0x1C] = 0x0D; // enter (carriage return)
	map[0x0e] = 0x08; // backspace


	// shifted keymap
	shift_map[0x01] = 0x1B; // ESC
	shift_map[0x02] = '+';
	shift_map[0x03] = '"';
	shift_map[0x04] = '*';
	shift_map[0x05] = 0x80; // ç
	shift_map[0x06] = '%';
	shift_map[0x07] = '&';
	shift_map[0x08] = '/';
	shift_map[0x09] = '(';
	shift_map[0x0A] = ')';
	shift_map[0x0B] = '=';

	shift_map[0x10] = 'Q';
	shift_map[0x11] = 'W';
	shift_map[0x12] = 'E';
	shift_map[0x13] = 'R';
	shift_map[0x14] = 'T';
	shift_map[0x15] = 'Z';
	shift_map[0x16] = 'U';
	shift_map[0x17] = 'I';
	shift_map[0x18] = 'O';
	shift_map[0x19] = 'P';
	shift_map[0x1e] = 'A';
	shift_map[0x1f] = 'S';
	shift_map[0x20] = 'D';
	shift_map[0x21] = 'F';
	shift_map[0x22] = 'G';
	shift_map[0x23] = 'H';
	shift_map[0x24] = 'J';
	shift_map[0x25] = 'K';
	shift_map[0x26] = 'L';
	shift_map[0x2c] = 'Y';
	shift_map[0x2d] = 'X';
	shift_map[0x2e] = 'C';
	shift_map[0x2f] = 'V';
	shift_map[0x30] = 'B';
	shift_map[0x31] = 'N';
	shift_map[0x32] = 'M';

	shift_map[0x27] = 0x94; // ö
	shift_map[0x28] = 0x84; // ä
	shift_map[0x1a] = 0x81; // ü
	shift_map[0x0c] = '?';
	shift_map[0x33] = ';';
	shift_map[0x34] = ':';
	shift_map[0x35] = '_';
	shift_map[0x1b] = 0x22; // !

	shift_map[0x1c] = 0x0d; // enter (carriage return)
	shift_map[0x0e] = 0x08; // backspace

}

uchar_t scan2char( uchar_t key_code, bool shift ){
	if ( !shift ) {
		return map[ key_code ];
	} else {
		return shift_map[ key_code ];
	}
}
