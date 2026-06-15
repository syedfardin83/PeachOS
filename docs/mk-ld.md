# Makefile and linkerscript

### Makefile and outputs

I am calling the final binary os.bin. The first sector (512 bytes) will be the signed boot sector (boot.bin), which will load the next sectors containing the kernel binary (kernel.bin). We are arbitrarily making os.bin 100 sectors long, with each sector being 512 bytes, for a total of 51.2 KB.

The kernel.bin file is built from multiple source files. Instead of compiling everything directly into kernel.bin, I am creating an intermediate object file, kernelfull.o, for debugging purposes. This file can be used by gdb to read symbols. Then the linker script is used to convert kernelfull.o into kernel.bin.

.asm → .asm.o → kernelfull.o

.c → .o → kernelfull.o

 

### Linkerscript

The .text section will contain all the code and instructions. We want to make sure that the kernel.asm code ends up first in this section, so we place it first in the file list when compiling kernelfull.o. The other assembly files are assembled into their own sections, such as section .asm, so the linker can place them in the desired order.