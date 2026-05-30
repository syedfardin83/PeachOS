#include "kernel.h"

#include <stdint.h>
#include <stddef.h>

uint16_t* video_mem = 0;
uint16_t terminal_x=0;
uint16_t terminal_y=0;

uint16_t terminal_make_color(char c, char color){
    return (color<<8)|c;
}

void terminal_putchar(int x, int y, char c, char color){
    video_mem[y*VGA_WIDTH+x] = terminal_make_color(c,color);
}

void terminal_writechar(char c, char color){
    if(c=='\n'){
        terminal_x=0;
        terminal_y++;
        return;
    }
    terminal_putchar(terminal_x,terminal_y,c,color);
    terminal_x++;
    if(terminal_x>=VGA_WIDTH){
        terminal_x=0;
        terminal_y++;
    }
}

void terminal_initialize(){
    video_mem = (uint16_t*)0xb8000;

    for(int y=0;y<VGA_HEIGHT;y++){
        for(int x=0;x<VGA_WIDTH;x++){
            terminal_putchar(x,y,' ',0);
        }
    }
}

size_t strlen(const char* str){
    size_t len=0;
    while(str[len]) len++;
    return len;
}

void print(const char* str){
    size_t len = strlen(str);
    for(int i=0;i<len;i++){
        terminal_writechar(str[i],15);
    }
}

void kernel_main(){
    terminal_initialize();

    print("Hello world!\nThis is a test.");
}