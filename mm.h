#ifndef _MM_H_
#define _MM_H_
#include "asm.h"
#include "ctype.h"
#define SLAB_TYPE_MAX 10
#define PAGE_MAX (1<<20)

#define PTE(PGID) ((u32)(PGID)<<12 | 0x7)

struct page_t{
	u32	used;	/*used*/
};

struct slab_t{
	size_t	size;
	void*	begin;

};
struct malloc_tab_t{
	size_t size;
	struct malloc_tab_t* nxt;
};
extern void init_mm();
extern inline void load_pt(void*);
extern int slab_init(u16,u16);
extern void* slab_alloc(u8);
extern int slab_free(void*,u8);
extern void* malloc_k(size_t);
extern int free_k(void*);
extern void* do_malloc(size_t,struct malloc_tab_t*);
extern int do_free(void*,struct malloc_tab_t*);
extern s32 page_alloc();
extern int page_free(s32);
extern struct page_t page[PAGE_MAX];
#endif//_MM_H_
