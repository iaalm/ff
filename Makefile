TARGET_MACH=-m32
TARGET_ARCH=-m32
ASFLAGS=-g
CFLAGS=-g
OBJCOPY=objcopy
all:kernel.bin
run:img
	qemu-kvm -kernel img
debug:img
	gdb -x gdb_script kernel
img:kernel.bin tools/header_linker tools/head
	./tools/header_linker ./tools/head kernel.bin > img
tools/header_linker:tools/header_linker.c
	cc $^ -o $@
kernel.bin:kernel
	$(OBJCOPY) -O binary $< $@

kernel.o:kernel.c print.h asm.h mm.h

kernel:head.o kernel.o print.o mm.o asm.o
	$(LD) $^ -g -T head.ld -o $@ --Map=kernel.map

clean:
	rm -rf img kernel.bin kernel *.o tools/header_linker kernel.map
