#include "idt.h"
#include "config.h"
#include "memory.h"
#include "kernel.h"

extern void idt_load(struct idtr_desc*);

void idt_zero(){
    print("\nDivide By zero error!");
}

struct idt_desc idt_descriptors[PEACH_OS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

void idt_set(int interrupt_no, void* address){
    struct idt_desc* entry = &idt_descriptors[interrupt_no];
    entry->offset_1 = (uint32_t)address & 0x0000ffff;
    entry->selector = KERNEL_CODE_SELECTOR;
    entry->zero = 0x00;
    entry->type_attr = 0xee;
    entry->offest_2 = (uint32_t)address >> 16;
}

void idt_init(){
    memset(idt_descriptors,0,sizeof(idt_descriptors));
    idtr_descriptor.limit=sizeof(idt_descriptors)-1;
    idtr_descriptor.base=(uint32_t)idt_descriptors;

    idt_set(0,idt_zero);
    idt_load(&idtr_descriptor);
}
