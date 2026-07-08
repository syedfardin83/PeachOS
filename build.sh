#!/bin/bash

make clean

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

make all

if [ "$1" = "r" ]; then

killall qemu-system-x86_64 2>/dev/null || true
qemu-system-x86_64 -hda ./bin/os.bin -S -gdb tcp::1234
gdb

fi
