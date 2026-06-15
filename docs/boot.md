# Boot.asm

This is a simple bootloader that switches the processor into 32-bit protected mode and reads the kernel binary from the hard drive starting at sector 2, using the ATA I/O ports. We start reading from sector 2 to the address 0x0100000, which makes sure that the final os.bin will include the kernel image after the boot sector. In other words, we load the kernel binary so that it starts at 0x0100000.

## Global Descriptor Table (GDT)

The GDT is an array of 8-byte entries, each describing a specific memory segment. Because the CPU can access only the segments described in the GDT, memory remains protected and the code cannot access critical areas such as BIOS memory.

In this project, I have set the base address of both the data segment and the code segment to 0, so that I can use absolute addresses wherever required.