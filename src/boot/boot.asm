;Switching from real mode to protected mode
org 0x7c00
bits 16

CODE_SEG equ gdt_code-gdt_start
DATA_SEG equ gdt_data -gdt_start


jmp short start
nop

OEMIdentifier       db 'THEOS123'
BytesPerSector      dw 0x200
SectorsPerCluster   db 0x80
ReservedSectors     dw 200 ; kernel will be stored here
FATCopies           db 0x002
RootDirEntries      dw 0x40
NumSectors          dw 0x00
MediaType           db 0xF8
SectorsPerFat       dw 0x100
SectorsPerTrack     dw 0x20
NumberOfHeads       dw 0x40
HiddenSectors       dd 0x00
SectorsBig          dd 0x773594


;Extended BPB (Dos 4.0)
DriveNumber             db 0x80
WinNTBit                db 0x00
Signature               db 0x29
VolumeID                dd 0xD105
VolumeIDString          db 'PEACHOS BOO'
SystemIDString          db 'FAT16   '



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
    jmp CODE_SEG:load32

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

[bits 32]
load32:
    mov eax,1
    mov ecx,100
    mov edi,0x0100000
    call ata_lba_read
    jmp CODE_SEG:0x0100000 ; jumps to kernel asm code

ata_lba_read:
    mov ebx,eax ;Backup LBA
    shr eax,24
    or eax,0xe0
    mov dx,0x01f6
    out dx, al

    mov eax, ecx
    mov dx,0x1f2
    out dx,al

    mov eax, ebx
    mov dx,0x1f3
    out dx, al

    mov dx, 0x1f4
    mov eax,ebx
    shr eax,8
    out dx,al

    mov dx,0x1f5
    mov eax, ebx
    shr eax,16
    out dx,al

    mov dx,0x1f7
    mov al,0x20
    out dx,al
     
.next_sector:
    push ecx

.try_again:
    mov dx,0x1f7
    in al,dx
    test al, 8
    jz .try_again

    mov ecx, 256
    mov dx,0x1f0
    rep insw
    pop ecx
    loop .next_sector
    ret

times 510-($-$$) db 0
dw 0xaa55