org 0x7c00
bits 16

start:
    mov si,message ; moves the address of message in si
    call print
    jmp $

print:
    mov bx, 0
    .loop:
        lodsb ;loads the value of si in al and increments si
        cmp al,0
        je .done
        call print_char
        jmp .loop


    .done:
        ret

print_char:
    mov ah,0x0e
    int 0x10
    ret

message: db 'Hello World!', 0

times 510-($-$$) db 0
dw 0xaa55