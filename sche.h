#include"asm.h"
struct pcb_t{
	u32 regs[16];
	struct gdt_ptr ldt;
	u32*	pt;
	struct pcb_t *pre,*nxt;
} __attribute__((packed));

extern int fork();
