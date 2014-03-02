TARGET_MACH=-m32
TARGET_ARCH=-m32
OBJCOPY=objcopy
all:kernel.bin
run:kernel.bin tools/header_linker tools/head
	./tools/header_linker ./tools/head kernel.bin > img
	qemu-kvm -kernel img
tools/header_linker:tools/header_linker.c
	cc $^ -o $@
kernel.bin:kernel
	$(OBJCOPY) -O binary $< $@

kernel.o:kernel.c print.h asm.h

kernel:head.o kernel.o print.o
	$(LD) $^ -T head.ld -o $@ 

clean:
	rm -rf img kernel.bin kernel *.o tools/header_linker
