#ifndef IDT_H
#define IDT_H
#include <stdint.h>

void idt_init();

struct idt_desc{

    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offest_2;

} __attribute__((packed)) ;

struct idtr_desc{

    uint16_t limit; //size of idt
    uint32_t base;   //base addr of start of idt

} __attribute__((packed)) ;

void enable_interrupts();
void disable_interrupts();

#endif