#include "mm.h"
#include "sche.h"

static u8 slab_id;
//static pcb_t *init_pcb;
struct pcb_t *current;

void init_sche(){
	slab_id = slab_init(sizeof(struct pcb_t),4);
	current = slab_alloc(slab_id);
	current->nxt = current->pre = current;
}
int fork(){
	return 0;
}
void nxt_proc(){
	return ;
}
