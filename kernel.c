#define VGA_80x25_H
#include "vga_80x25.h"

void _start(){
	char hello[] = "Hello World!\n";
	VGA_80x25_print_c_str(hello, RED_ON_BLACK);
}