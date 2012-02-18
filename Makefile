CFLAGS=-Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32 -std=c99

all: kernel

clean:
	rm -f *.o
	rm -f kernel.bin

run: kernel
	qemu -kernel kernel.bin

kernel: linker.ld loader.o kernel.o textmode.o standard.o
	ld -T linker.ld -o kernel.bin loader.o kernel.o textmode.o standard.o -melf_i386

loader.o: loader.s
	nasm -f elf -o loader.o loader.s

kernel.o: standard.h kernel.c
	gcc $(CFLAGS) -o kernel.o -c kernel.c

texmode.o: standard.h textmode.c
	gcc $(CFLAGS) -o textmode.o -c textmode.c

standard.o: standard.h standard.c
	gcc $(CFLAGS) -o standard.o -c standard.c
