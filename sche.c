#include "mm.h"
#include "sche.h"

static u8 slab_id;
//static pcb_t *init_pcb;
struct pcb_t *current;
extern void process_2();
void init_sche(){
	slab_id = slab_init(sizeof(struct pcb_t),4);
	current = slab_alloc(slab_id);
	current->nxt = current->pre = slab_alloc(slab_id);
	current->nxt->pre = current->pre->nxt = current;
	current->nxt->regs[0] = 0x2b;
	current->nxt->regs[1] = 0x2b;
	current->nxt->regs[2] = 0x2b;
	current->nxt->regs[3] = 0x2b;
	current->nxt->regs[11] = process_2;	//eip
	current->nxt->regs[12] = 0x23;		//cs
	current->nxt->regs[13] = 695;		//eflags
	current->nxt->regs[14] = 0x10008000;	//esp
	current->nxt->regs[15] = 0x2b;		//ss
}
int fork(){
	return 0;
}
void nxt_proc(){
	current = current->nxt;
}
