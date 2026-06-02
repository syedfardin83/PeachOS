[BITS 32]
global _start
extern kernel_main

DATA_SEG equ 0x10
CODE_SEG equ 0x08

_start:
    mov ax,DATA_SEG
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    mov ebp,0x00200000
    mov esp,ebp

    ;enable the A20 line
    in al, 0x92
    or al, 2
    out 0x92, al

    ;Remapping PIC
    mov al, 00010001b
    out 0x20, al ; Put Master PIC in config mode

    mov al, 0x20 ; Set IRQ 0 to 0x20
    out 0x21, al 

    mov al,00000001b
    out 0x21, al

    sti

    call kernel_main ; jumps to kernel c code

    jmp $

times 512-($-$$) db 0
