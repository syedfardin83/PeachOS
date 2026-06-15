# BIOS

When a computer is first powered on, the x86 processor starts in 16-bit real mode and begins executing BIOS firmware, which is written by the computer manufacturer and stored in firmware memory. Its main function is to initialize the hardware, perform some basic checks, and then search for a bootable drive.

A bootable drive contains a 512-byte boot sector with a specific signature at the end. This is called the boot signature. If such a drive is found, the BIOS loads that 512-byte sector into memory, and the processor starts executing that code. In practice, that code is usually called the bootloader, and its job is to load the main kernel from the hard drive into memory and then jump to it.

Power on —> BIOS —> Bootloader —> Kernel