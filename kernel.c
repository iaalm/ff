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
/*
void get_and_print_memory_inf(){
	u32 mem_info[200],*len;
	asm volatile(	"mov $0xeb20,%%ax\n"
			"mov $0,%%ebx\n"
			//"mov %0,%%di\n"
			"mov $20,%%ecx\n"
			"mov $0x534d4150,%%edx\n"
			"loop:\n"
			"int $0x15\n"
			"add $20,%%edi\n"
			"mov $0xeb20,%%ax\n"
			"cmp $0,%%ebx\n"
			"jne loop\n"
			"mov di,%0"
			://"=r"(mem_info)
			:"r"(len)
			:"%eax","%ebx","%ecx","%edx","memory");
	putl_k(len-mem_info);
}
*/
void kernel(){
	setup_idt();
	init_8259A();
	//putl_k((u32)boot_params_p);
	//asm volatile("int $0xff");
	while(1);
}
