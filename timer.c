#include "ctype.h"
#include "mm.h"
#include "timer.h"

static struct timer head;
static int slab_id;
static u64 tc;
static void add_tc(){
	tc++;
}
void do_timer(){
	struct timer* i;
	LKLIST_FOREACH(&head,i)
		if(--(i->now) == 0){
			i->now = i->count;
			i->cb();
		}
}
void init_timer(){
	slab_id = slab_init(sizeof(struct timer),10);
	tc = 0;
	head.nxt = head.pre = NULL;
	head.now = 1;
	head.count = 1;
	head.cb = add_tc;
}
struct timer* add_timer(void(*call_back)(),u32 time){
	struct timer* t = slab_alloc(slab_id);
	t->count = time;
	t->now = time;
	t->cb = call_back;
	LKLIST_ADD(&head,t);
	return t;
}

void del_timer(struct timer* t){
	LKLIST_DEL(t);
	slab_free(t,slab_id);
}
u64 get_tc(){
	return tc;
}
