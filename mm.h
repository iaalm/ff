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
extern void mm_init();
extern inline void load_pt(void*);
extern int slab_init(u16,u16);
extern void* slab_malloc_k(u8);
extern int slab_free_k(void*,u8);
extern void* malloc_k(size_t);
extern int free_k(void*);
extern s32 page_alloc();
extern int page_free(s32);
extern struct page_t page[PAGE_MAX];
#endif//_MM_H_
