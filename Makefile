# These are the elf intermidiate files which will contain debugging info as well
FILES = ./build/kernel.asm.o ./build/io/io.asm.o ./build/kernel.o ./build/idt/idt.asm.o ./build/idt/idt.o ./build/memory/memory.o ./build/memory/heap/heap.o ./build/memory/heap/kheap.o ./build/memory/paging/paging.asm.o ./build/memory/paging/paging.o ./build/disk/disk.o ./build/string/string.o ./build/fs/pparser.o ./build/disk/streamer.o
INCLUDES = -I./src -I./src/idt -I./src/memory -I./src/io -I./src/memory/heap -I./src/memory/paging -I./src/disk -I./src/string -I./src/fs
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fno-omit-frame-pointer -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc -m32

all: ./bin/boot.bin ./bin/kernel.bin
#combining boot.bin and kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=1048576 count=16 >>./bin/os.bin

	sudo mount -t vfat ./bin/os.bin /mnt/d
	sudo cp ./hello.txt /mnt/d
	sudo umount /mnt/d

./bin/boot.bin: ./src/boot/boot.asm
# nasm converts boot.asm to boot.bin
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin 

./bin/kernel.bin: $(FILES)
#combining all object files to single intermidiate elf
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
#generating the final binary (linking happens here)
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

./build/kernel.asm.o: ./src/kernel.asm
# nasm converts kernel.asm to elf file which has debugger flags and linking info
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o

./build/kernel.o : ./src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o

./build/idt/idt.asm.o: ./src/idt/idt.asm
# nasm converts idt.asm to elf file which has debugger flags and linking info
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o

./build/idt/idt.o : ./src/idt/idt.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/idt/idt.c -o ./build/idt/idt.o

./build/memory/memory.o : ./src/memory/memory.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/memory.c -o ./build/memory/memory.o

./build/io/io.asm.o: ./src/io/io.asm
# nasm converts io.asm to elf file which has debugger flags and linking info
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o

./build/memory/heap/heap.o : ./src/memory/heap/heap.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/heap/heap.c -o ./build/memory/heap/heap.o

./build/memory/heap/kheap.o : ./src/memory/heap/kheap.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/heap/kheap.c -o ./build/memory/heap/kheap.o

./build/memory/paging/paging.asm.o: ./src/memory/paging/paging.asm
	nasm -f elf -g ./src/memory/paging/paging.asm -o ./build/memory/paging/paging.asm.o

./build/memory/paging/paging.o : ./src/memory/paging/paging.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/paging/paging.c -o ./build/memory/paging/paging.o

./build/disk/disk.o : ./src/disk/disk.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/disk/disk.c -o ./build/disk/disk.o

./build/string/string.o : ./src/string/string.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/string/string.c -o ./build/string/string.o

./build/fs/pparser.o : ./src/fs/pparser.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/fs/pparser.c -o ./build/fs/pparser.o

./build/disk/streamer.o : ./src/disk/streamer.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/disk/streamer.c -o ./build/disk/streamer.o

clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/os.bin
	rm -rf $(FILES)
	rm -rf ./build/kernelfull.o