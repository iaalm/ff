#include"asm.h"
struct pcb_t{
	u32 regs[12];
	u32 c_reg[4];		//eax ebx ecx edx
	u32 p_reg[4];		//esp ebp esi edi
	void* eip;
	u16 s_reg[6];		//cs ds ss es fs gs
	struct gdt_ptr ldt;
	u32*	pt;
	struct pcb_t *pre,*nxt;
} __attribute__((packed));

extern int fork();
