#ifndef _MM_H_
#define _MM_H_
#include "asm.h"
#define SLAB_TYPE_MAX 10
struct p_page_t{
	u32	used;	/*used*/
};

struct slab_t{
	size_t	size;
	void*	begin;

};
extern int slab_init(u16,u16);
extern void* slab_malloc_k(u8);
extern int slab_free_k(void*,u8);
extern struct p_page_t p_page[1<<20];
#endif//_MM_H_
