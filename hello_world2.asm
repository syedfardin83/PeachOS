org 0 ; org actually sets an offset for all functions in the code
bits 16

jmp 0x7c0:start

handle_zero:
    mov bx,0
    mov ah, 0x0e
    mov al,'A'
    int 0x10
    iret

start:
    cli ; Disable interrupts
    mov ax,0x7c0
    mov ds,ax
    mov es,ax
    mov ax, 0x00
    mov ss,ax
    mov sp,0x7c00
    sti

    ;Changing the interrupt vector table
    mov word[ss:0x00], handle_zero
    mov word[ss:0x02], 0x7c0

    int 0

    mov si,message ; moves the address of message in si
    call print
    jmp $

print:
    mov bx, 0
    .loop:
        lodsb ; (ds:si) loads the value of si in al and increments si
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