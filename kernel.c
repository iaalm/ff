#include "asm.h"
#include "interrupt.h"
#include "print.h"
#include "ctype.h"
#include "mm.h"
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
	iodelay(); outb(0xa1,0x02);
	iodelay();
	outb(0x21,0x01);
	iodelay();
	outb(0xa1,0x01);
	iodelay();
	outb(0x21,0xfe);
	iodelay();
	outb(0xa1,0xff);
	iodelay();
	idt[TIMER] = IDT_ENTRY(0x8e00,cs(),(u32)p);
	sti();
}
void setup_idt(){
	u32 i;
	u64 entry = IDT_ENTRY(0x8e00,cs(),(u32)udef_fun);

	for(i = 0;i < 256;i++)
		idt[i] = entry;

	struct gdt_ptr ptr = {sizeof(idt),(u32)idt};
	asm volatile("lidtl %0"::"m"(ptr));
}

void kernel(){
	setup_idt();
	clean_screen();
	mm_init();
	init_8259A();
	int id = slab_init(4,4);
	void *p;
	putl_k((u32)slab_alloc(id));
	putl_k((u32)(p = malloc_k(1234)));
	putl_k((u32)free_k(p));
	putl_k((u32)(p = malloc_k(1234)));
	putl_k((u32)free_k(p));
	//*(int*)0xf0000000 = 0;	//cause pf interrupt
	//asm volatile("int $0xff");
	while(1);
}
