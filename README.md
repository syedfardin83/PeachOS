# PeachOS

A custom, bare-metal 32-bit x86 Protected Mode operating system built completely from scratch to explore low-level systems architecture, hardware-software interfacing, and kernel development.

This project is based on a *Udemy course* by [Daniel McCarthy - "*Developing a multi-threaded kernel from scratch*"](https://www.udemy.com/course/developing-a-multithreaded-kernel-from-scratch/)

Other sources:
https://wiki.osdev.org/

---

## 🚀 Project Vision

PeachOS is a deep-dive engineering journey to strip away modern operating system abstractions and interface directly with raw silicon. Developed entirely on a Fedora Linux host environment using a custom-built, cross-compiled toolchain (`i686-elf-gcc`), this project completely bypasses standard runtime environments to implement fundamental operating system mechanics—ranging from custom MBR boot sectors to physical motherboard hardware interrupt routing.

---

## 🛠️ System Architecture & Docs

The current documentation is organized in the `docs/` folder:

- [CPU, Assembly, and Binary](docs/general.md)
- [BIOS and Boot Flow](docs/bios.md)
- [Bootloader and GDT](docs/boot.md)
- [Makefile and Linker Script](docs/mk-ld.md)

---

## 📋 Core Kernel Features

- [x] 512-Byte Bootloader with `0xAA55` Master Boot Record (MBR) Signature
- [x] Real Mode to 32-bit Protected Mode CPU Hardware Transition
- [x] Global Descriptor Table (GDT) Segment Mapping & Control Register Overhaul
- [x] Interrupt Descriptor Table (IDT) Wrapper Gates (Assembly Assembly -> C Handshake)
- [x] Dual Intel 8259 PIC Hardware Vector Remapping (Base Shift to `0x20`)
- [x] Subsystem Integration: Video Text Buffer Screen Pointer & PS/2 Keyboard Driver
- [x] Heap implimentation and dynamic memory allocation
- [ ] Memory Management: Paging Engine & Two-Tier Address Translation Tables
- [ ] Multitasking: Hardware Task State Segments (TSS) & Kernel Context Switcher

---

## 💻 Quick Start & Compilation

Because compiling a bare-metal kernel requires strict isolation from your host operating system's standard C libraries, PeachOS relies on a cross-compilation environment.

### 1. Development Prerequisites
Ensure your development environment contains a compiled `i686-elf-gcc` cross-compiler target and the `QEMU` system emulator. 

### 2. Build and Execute
Cloning and running the kernel utilizes an automated `Makefile` compilation pipeline:

```bash
# Clone the repository
git clone https://github.com/syedfardin83/PeachOS.git
cd PeachOS

# Compile assembly wrappers, compile C subsystems, and link into a flat binary image
./build.sh

# Flash the resulting os.bin image straight into QEMU for emulation
qemu-system-x86_64 -hda ./bin/os.bin