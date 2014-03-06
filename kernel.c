#include "asm.h"
#include "print.h"
#include "ctype.h"
u64 idt[256];
inline void iodelay(){
	asm volatile ("nop\nnop\nnop\nnop\nnop");
}

void init_8259A(){
	outb(0x20,0x11);
	iodelay();
	outb(0xa0,0x11);
	iodelay();
	outb(0x21,0x20);
	iodelay();
	outb(0xa1,0x28);
	iodelay();
	outb(0x21,0x04);
	iodelay();
	outb(0xa1,0x02);
	iodelay();
	outb(0x21,0x01);
	iodelay();
	outb(0xa1,0x01);
	iodelay();
	outb(0x21,0xfe);
	iodelay();
	outb(0xa1,0xff);
	iodelay();
	sti();
}
extern void p();
void setup_idt(){
	u32 i;
	u64 entry = IDT_ENTRY(0x8e00,cs(),(u32)p);

	for(i = 0;i < 256;i++)
		idt[i] = entry;

	struct gdt_ptr ptr = {sizeof(idt),(u32)idt};
	asm volatile("lidtl %0"::"m"(ptr));
}
void print_mem_info(){
	u32* mem;
	int i;
	OFFSET(boot_params_p,0x2d0,mem);
	do{
			printf_k("%08x - %08x : %10d : %08x",*(mem+0),*(mem+0)+*(mem+2),*(mem+2),*(mem+4));
		putc_k('\n');
		mem += 5;
	}while(*mem);
}
void kernel(){
	setup_idt();
	init_8259A();
	clean_screen();
	putl_k((u32)boot_params_p);
	print_mem_info();

	//asm volatile("int $0xff");
	while(1);
}
