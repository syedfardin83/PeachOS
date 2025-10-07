org 0x7c00
bits 16

start:
    mov ah, 0x0e
    mov al, 'A'
    mov bx, 0
    int 0x10

    jmp $

times 510-($-$$) db 0 ; If 510 bytes are not used, fill rest with 0. (Assembler directive)
dw 0xaa55 ; boot signature