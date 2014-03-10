#include "mm.h"
struct p_page_t p_page[1<<20];
static struct slab_t slab[SLAB_TYPE_MAX];
static void* slab_tail = &_end_kernel;
static u8 slab_index = 0;
int slab_init(u16 size,u16 max){
	void **ptr,*nxt;
	if(slab_index == SLAB_TYPE_MAX || size < sizeof(void*))
		return -1;
	slab[slab_index].size = size;
	slab[slab_index].begin = slab_tail;
	//slab[slab_index].count = size;
	slab_tail += size * max;
	//check page
	ptr = slab[slab_index].begin;
	do{
		OFFSET(ptr,(u32)size,nxt);
		*ptr = nxt;
		ptr = nxt;
	}while((void*)ptr < slab_tail);
	OFFSET(ptr,(s32)-size,ptr);
	*ptr = NULL;
	return slab_index++;
}
void* slab_malloc_k(u8 type){
	void* ptr;
	if(type >= slab_index || (ptr = slab[type].begin) == NULL)
		return NULL;
	slab[type].begin = *(void**)ptr;
	return ptr;
}
int slab_free_k(void* ptr,u8 type){
	if(type >= slab_index)
		return -1;
	*(void**)ptr = slab[type].begin;
	slab[type].begin = ptr;
	return 0;
}
void* do_malloc_k(size_t size);
void do_free_k(void* ptr,size_t size);
