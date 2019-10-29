#include "shell_drivers.h"
#include "keyboard.h"
#include "../display/display.h"
#include "../x86.h"
#include "../fs/fs.h"


// with help from zaffini and vanino
void read_string(char *buffer) {

    uchar_t key;

    do {
        key = getc();
        if (key == ESC)
            exit();
        else if (key == ENTER){
            read_line(buffer);
        }
        else
            display_carac(key);
    } while (key != ENTER);
}

void exit() {
    printf("\nSHUTTING DOWN. GOODBYE.\n");
    halt();
}
