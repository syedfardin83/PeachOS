#include "kernel.h"
#include "idt.h"
#include "io.h"
#include "kheap.h"
#include "paging.h"
#include "./disk/disk.h"

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

// will be called by kernel.asm
struct paging_4gb_chunk* kernel_chunk=0;
void kernel_main(){
    terminal_initialize();
    print("\nTerminal initalized.");

    //  Kernel Heap
    kheap_init();
    print("\nKheap initialized.");

    // Initialize IDT
    idt_init();

    //  Paging setup
    kernel_chunk= paging_new_4gb(PAGING_IS_WRITABLE|PAGING_IS_PRESENT|PAGING_ACCESS_FROM_ALL);
    paging_switch(kernel_chunk->entries);

    char* ptr1 = kzalloc(4096);
    paging_set(kernel_chunk->entries,(void*)0x1000,(uint32_t)ptr1 | PAGING_ACCESS_FROM_ALL | PAGING_IS_PRESENT | PAGING_IS_WRITABLE);

    paging_enable();

    enable_interrupts(); 
    
    char buf[512];
    disk_read_sector(0,1,buf);

    int a = 10;
    a++;

}