#include "mm.h"
#include "interrupt.h"
struct page_t page[PAGE_MAX];
static struct slab_t slab[SLAB_TYPE_MAX];
//static void* brk_k = &_end_kernel;
static u8 slab_index = 0;
static u32* pt_k;
static struct malloc_tab_t malloc_tab_k = {(u32)&_end_kernel,NULL};

inline void load_pt(void* pt){
	asm volatile ("mov %0,%%cr3\nmov %%cr0,%0\nor $0x80000000,%0\nmov %0,%%cr0"::"r"(pt));
}

void mark_unavail_mem(){
	int i,j;
	u32 *mem;
	mem = (void*)boot_params_p + 0x2d0;
	do{
		if(*(mem+4) != 1){
			j = (*(mem+0)+*(mem+2) + 4095) >> 12;
			for(i = (*(mem)) >> 12;i < j;i++)
				page[i].used = 0xff;
		}
		mem += 5;
	}while(*mem);
}

void init_mm(){
	int i,pde_count,pte_count;
	OFFSET(&_end_kernel,0xfff,pte_count);
	pte_count >>= 12;
	pt_k =(u32*)(pte_count << 12);
	pde_count = (pte_count + 1023) >> 10;

	for(i = 0;i < pde_count;i++){
		pt_k[i] = PTE(pte_count+i+1);
	}
	while(i < 1024)
		pt_k[i++] = 0;

	for(i = 0;i < pte_count;i++){
		pt_k[1024+i] = PTE(i);
		page[i].used = 1;
	}
	while(i < pde_count + pte_count + 1)
		page[i++].used = 1;

	while(i < PAGE_MAX)
		page[i++].used = -1;

	for(i = pte_count;i < (pde_count << 10);i++)
		pt_k[1024+i] = 0;

	mark_unavail_mem();
	load_pt(pt_k);

	idt[PAGE_FAULT] = IDT_ENTRY(0x8e00,cs(),(u32)pf);
}

int slab_init(u16 size,u16 max){
	void **ptr,*nxt,*end;
	if(slab_index == SLAB_TYPE_MAX || size < sizeof(void*))
		return -1;
	slab[slab_index].size = size;
	slab[slab_index].begin = malloc_k(size*max);
	OFFSET(slab[slab_index].begin,size*max,end);
	ptr = slab[slab_index].begin;
	do{
		OFFSET(ptr,(u32)size,nxt);
		*ptr = nxt;
		ptr = nxt;
	}while((void*)ptr < end);
	OFFSET(ptr,(s32)-size,ptr);
	*ptr = NULL;
	return slab_index++;
}
void* slab_alloc(u8 type){
	void* ptr;
	if(type >= slab_index || (ptr = slab[type].begin) == NULL)
		return NULL;
	slab[type].begin = *(void**)ptr;
	return ptr;
}
int slab_free(void* ptr,u8 type){
	if(type >= slab_index)
		return -1;
	*(void**)ptr = slab[type].begin;
	slab[type].begin = ptr;
	return 0;
}
s32 page_alloc(){
	int i;
	for(i = 0;i < PAGE_MAX;i++)
		if(page[i].used == -1){
			page[i].used = 0;
			return i;
		}
	return -1;
}
int page_free(s32 pgid){
	if(pgid < 0 || pgid > PAGE_MAX || page[pgid].used != 0)
		return -1;
	page[pgid].used = -1;
	return 0;
}
void* malloc_k(size_t size){
	return do_malloc(size,&malloc_tab_k);
}
int free_k(void* ptr){
	return do_free(ptr,&malloc_tab_k);
}
void* do_malloc(size_t size,struct malloc_tab_t* head){
	struct malloc_tab_t *idx;
	size += sizeof(void*);
	for(idx = head->nxt;idx != NULL;idx = idx -> nxt)
		if(idx -> size >= size)
			break;
	if(idx == NULL){
		idx = (struct malloc_tab_t *)(head->size);
		head->size += size;
	}
	idx->size = size;
	return ((void*)idx + sizeof(void*));
}
int do_free(void* ptr,struct malloc_tab_t* head){
	ptr -= sizeof(void*);
	struct malloc_tab_t *idx,*oidx=head;
	//merge
	if(ptr+((struct malloc_tab_t *)ptr)->size == (void*)head->size){
		head->size = (u32)ptr;
		return 0;
	}
	for(idx = head->nxt;idx != NULL;oidx = idx,idx = idx -> nxt){
		if((void*)idx + idx->size == ptr || ptr+((struct malloc_tab_t*)ptr)->size == idx){
			((struct malloc_tab_t*)ptr)->size += idx->size;
			oidx->nxt = idx->nxt;
			break;
		}
	}
	//insert
	oidx = head;
	for(idx = head->nxt;idx != NULL;oidx = idx,idx = idx -> nxt){
		if(idx -> size > ((struct malloc_tab_t*)ptr)->size)
			break;
	}
	((struct malloc_tab_t*)ptr)->nxt = oidx->nxt;
	oidx->nxt = ptr;
	return 0;
}
void do_page_fault(u32 addr){
	if(!(pt_k[addr >> 22] & 1)){	//check pde
		pt_k[addr >> 22] = PTE(page_alloc());
	}
	((u32*)(pt_k[addr>>22] & 0xfffff000))[(addr>>12)&0x3ff] = PTE(page_alloc());
}
