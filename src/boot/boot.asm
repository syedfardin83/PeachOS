;Switching from real mode to protected mode
org 0x7c00
bits 16

CODE_SEG equ gdt_code-gdt_start
DATA_SEG equ gdt_data -gdt_start

_start:
    jmp short start
    nop

times 33 db 0

start:
    jmp step2

step2:
    cli
    mov ax,0x00
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov sp,0x7c00
    sti

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax,cr0
    or eax,0x1
    mov cr0,eax
    ;jmp CODE_SEG:load32
    jmp $

gdt_start:
gdt_null:
    dd 0x00
    dd 0x00

gdt_code:
    dw 0xffff
    dw 0
    db 0
    db 0x9a
    db 11001111b
    db 0

gdt_data:
    dw 0xffff
    dw 0
    db 0
    db 0x92
    db 11001111b
    db 0
   
gdt_end:

gdt_descriptor:
    dw gdt_start-gdt_end-1
    dd gdt_start



times 510-($-$$) db 0
dw 0xaa55