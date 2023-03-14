#ifdef VGA8025_H

#define IO_H
#include "io.h"

#define UTILS_H
#include "utils.h"

#define vga8025_CTR_REG 0x3D4
#define vga8025_DATA_REG 0x3D5
#define vga8025_LOFFSET 0xF
#define vga8025_HOFFSET 0xE

#define vga8025_VID_ADDR 0xB8000

#define vga8025_ROWS 25
#define vga8025_COLS 80

#define vga8025_BLACK_BLACK      0b00000000
#define vga8025_BLUE_BLACK       0b00000001
#define vga8025_GREEN_BLACK      0b00000010
#define vga8025_CYAN_BLACK       0b00000011
#define vga8025_RED_BLACK        0b00000100
#define vga8025_MAGENTA_BLACK    0b00000101
#define vga8025_BROWN_BLACK      0b00000110
#define vga8025_GRAY_BLACK       0b00000111
#define vga8025_GRAY2_BLACK      0b00001000
#define vga8025_LBLUE_BLACK      0b00001001
#define vga8025_LGREEN_BLACK     0b00001010
#define vga8025_LCYAN_BLACK      0b00001011
#define vga8025_LRED_BLACK       0b00001100
#define vga8025_LMAGENTA_BLACK   0b00001101
#define vga8025_LYELLOW_BLACK    0b00001110
#define vga8025_WHITE_BLACK      0b00001111

void vga8025_set_cursor(int offset) {
    offset /= 2;
    io_byte_out(vga8025_CTR_REG, vga8025_HOFFSET);
    io_byte_out(vga8025_DATA_REG, (unsigned char) (offset>>8));
    io_byte_out(vga8025_CTR_REG, vga8025_LOFFSET);
    io_byte_out(vga8025_DATA_REG, (unsigned char) (offset&0xff));
}

int vga8025_get_cursor() {
    io_byte_out(vga8025_CTR_REG, vga8025_HOFFSET);
    int offset = io_byte_in(vga8025_DATA_REG)<< 8;
    io_byte_out(vga8025_CTR_REG, vga8025_LOFFSET);
    offset += io_byte_in(vga8025_DATA_REG);
    return offset*2;
}

int vga8025_get_col(int offset){
    return offset%(2*vga8025_COLS);
}

int vga8025_get_row(int offset){
    return offset/(2*vga8025_COLS);
}

int vga8025_get_offset(int row, int col){
    return 2*(row*vga8025_COLS+col);
}

void vga8025_putc(char chr, int offset, unsigned char color) {
    unsigned char *videomem = (unsigned char *)vga8025_VID_ADDR;
    videomem[offset] = chr;
    videomem[offset+1] = color;
}

void vga8025_print_c_str(char *c_str, unsigned char color){
    unsigned int offset = vga8025_get_cursor();
    int i = 0;
    while(c_str[i]!='\0'){
        if(c_str[i]=='\n'){
            offset = vga8025_get_offset(vga8025_get_row(offset)+1, 0);
        }else{
            vga8025_putc(c_str[i], offset, color);
            offset += 2;
        }
        ++i;
    }
    vga8025_set_cursor(offset);
}

void vga8025_scroll_down(){
    for(int i = 0; i < vga8025_ROWS-1; ++i){
        memncpy((char *)(vga8025_VID_ADDR+vga8025_get_offset(0, i+1)), (char *)(vga8025_VID_ADDR+vga8025_get_offset(0, i)), vga8025_COLS);
    }
}

#endif // VGA8025_H