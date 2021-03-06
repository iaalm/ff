#include "asm.h"
#include "interrupt.h"
#include "print.h"
#include "ctype.h"
#include "mm.h"
#include "timer.h"
#include "sche.h"
u64 gdt[6];
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
	idt[TIMER] = IDT_ENTRY(0x8e00,cs(),(u32)timer_irq);
	//idt[TIMER] = IDT_ENTRY(0x8e00,cs(),(u32)p);
}
void setup_gdt(){
	gdt[0] = GDT_ENTRY(0x0000, 0, 0x00000);
	gdt[1] = GDT_ENTRY(0x0089, (u32)&tss, 103);
	gdt[2] = GDT_ENTRY(0xc09a, 0, 0xfffff);
	gdt[3] = GDT_ENTRY(0xc092, 0, 0xfffff);
	gdt[4] = GDT_ENTRY(0xc0fa, 0, 0xfffff);
	gdt[5] = GDT_ENTRY(0xc0f2, 0, 0xfffff);

	struct gdt_ptr ptr = {sizeof(gdt),(u32)gdt};
	asm volatile("lgdtl %0" :: "m" (ptr));
}
void setup_idt(){
	u32 i;
	u64 entry = IDT_ENTRY(0x8e00,cs(),(u32)udef_fun);

	for(i = 0;i < 256;i++)
		idt[i] = entry;
	idt[8] = IDT_ENTRY(0x8e00,cs(),(u32)df);
	idt[13] = IDT_ENTRY(0x8e00,cs(),(u32)gp);

	struct gdt_ptr ptr = {sizeof(idt),(u32)idt};
	asm volatile("lidtl %0"::"m"(ptr));
}

void timer(){
	puts_k("!!!");
	putl_k(get_tc() & 0xffffffff);
}
void kernel(){
	setup_gdt();
	setup_idt();
	clean_screen();
	init_timer();
	add_timer(timer,10);
	init_mm();
	init_sche();
	init_8259A();
	init_2process();
	init_process();
}


void process(){
	int i;
	while(1){
		printf_k("1");
		for(i = 0;i < 5000000;i++)
			asm ("nop");
	}
}

void process_2(){
	int i;
	while(1){
		printf_k("2");
		for(i = 0;i < 5000000;i++)
			asm ("nop");
	}
}
void init_2process(){
	u32* i= 0x10000000;
	while(i <= 0x10010000){
		*i = 0;
		i++;
	}
}

