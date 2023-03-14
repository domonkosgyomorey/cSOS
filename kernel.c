#define VGA8025_H
#include "vga8025.h"

void _start(){
	char hello[] = "Hello World!\n";
	vga8025_print_c_str(hello, vga8025_RED_BLACK);
}