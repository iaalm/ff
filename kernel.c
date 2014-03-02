#include "asm.h"
#include "print.h"
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
}
extern void p();
void setup_idt(){
	u32 i;
	asm volatile("movl %%cs,%0":"=r"(i));
	putl_k(i);
	putl_k(p);
	u64 entry = IDT_ENTRY(0x8e00,i,(u32)p);
	putl_k(entry & 0xffffffff);
	putl_k(entry >> 32);

	for(i = 0;i < 256;i++)
		idt[i] = entry;

	struct gdt_ptr ptr= {256 * 8,idt};
	asm volatile("lidtl %0"::"m"(ptr));


}
void kernel(){
	//init_8259A();
	setup_idt();
	asm volatile("int $0x80");
	while(1);
}
