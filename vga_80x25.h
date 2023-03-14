#ifdef VGA_80x25_H

#define IO_H
#include "io.h"

#define VGA_CONTROL_REGISTER 0x3D4
#define VGA_DATA_REGISTER 0x3D5
#define VGA_OFFSET_LOW 0xF
#define VGA_OFFSET_HIGH 0xE

#define VIDEO_ADDRESS 0xB8000

#define MAX_ROWS 25
#define MAX_COLS 80

#define BLACK_ON_BLACK      0b00000000
#define BLUE_ON_BLACK       0b00000001
#define GREEN_ON_BLACK      0b00000010
#define CYAN_ON_BLACK       0b00000011
#define RED_ON_BLACK        0b00000100
#define MAGENTA_ON_BLACK    0b00000101
#define BROWN_ON_BLACK      0b00000110
#define GRAY_ON_BLACK       0b00000111
#define GRAY2_ON_BLACK      0b00001000
#define LBLUE_ON_BLACK      0b00001001
#define LGREEN_ON_BLACK     0b00001010
#define LCYAN_ON_BLACK      0b00001011
#define LRED_ON_BLACK       0b00001100
#define LMAGENTA_ON_BLACK   0b00001101
#define LYELLOW_ON_BLACK    0b00001110
#define WHITE_ON_BLACK      0b00001111

void VGA_80x25_set_cursor(int offset) {
    offset /= 2;
    io_byte_out(VGA_CONTROL_REGISTER, VGA_OFFSET_HIGH);
    io_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset>>8));
    io_byte_out(VGA_CONTROL_REGISTER, VGA_OFFSET_LOW);
    io_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset&0xff));
}

int VGA_80x25_get_cursor() {
    io_byte_out(VGA_CONTROL_REGISTER, VGA_OFFSET_HIGH);
    int offset = io_byte_in(VGA_DATA_REGISTER)<< 8;
    io_byte_out(VGA_CONTROL_REGISTER, VGA_OFFSET_LOW);
    offset += io_byte_in(VGA_DATA_REGISTER);
    return offset*2;
}

int VGA_80x25_get_col(int offset){
    return offset%(2*MAX_COLS);
}

int VGA_80x25_get_row(int offset){
    return offset/(2*MAX_COLS);
}

int VGA_80x25_get_offset(int row, int col){
    return 2*(row*MAX_COLS+col);
}

void VGA_80x25_putc(char chr, int offset, unsigned char color) {
    unsigned char *videomem = (unsigned char *)VIDEO_ADDRESS;
    videomem[offset] = chr;
    videomem[offset+1] = color;
}

void VGA_80x25_print_c_str(char *c_str, unsigned char color){
    unsigned int offset = VGA_80x25_get_cursor();
    int i = 0;
    VGA_80x25_putc(c_str[0], offset, WHITE_ON_BLACK);
    while(c_str[i]!='\0'){
        if(c_str[i]=='\n'){
            offset = VGA_80x25_get_offset(VGA_80x25_get_row(offset)+1, 0);
        }else{
            VGA_80x25_putc(c_str[i], offset, WHITE_ON_BLACK);
            offset += 2;
        }
        ++i;
    }
    VGA_80x25_set_cursor(offset);
}

#endif // VGA_80x25_H