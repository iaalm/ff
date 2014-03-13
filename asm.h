#ifndef _ASM_H_
#define _ASM_H_
#include"ctype.h"
extern inline void outb(u16,u8);
extern inline u8 inb(u16);
extern inline u16 ds(void);
extern inline u16 cs(void);
extern inline void sti();
extern inline void cli();

#define GDT_ENTRY(flags,base,limit)		\
		(((((u64)base) & 0xffff) << 48)			| \
		((((u64)limit) & 0xffff)<< 32)			| \
		((base) & 0xff000000)	 			| \
		(((flags) & 0xf0ff) << 8)			| \
		((limit) & 0xf0000)				| \
		(((base) & 0xff0000) >> 16))


#define IDT_ENTRY(flags,selecter,offset)	\
	(((((u64)offset) & 0x00000000ffff0000) << (48 - 16))	| \
	((((u64)flags) & 0x000000000000ffff) << 32)		| \
	(((selecter) & 0x000000000000ffff) << 16)		| \
	(((u64)offset) & 0x000000000000ffff))

#define OFFSET(base,offset,target) asm volatile ("mov %1,%0\nadd %2,%0":"=&r"(target):"r"(base),"r"(offset))
//#define OFFSET(base,offset,target) target=(void*)(((u32)(base))+((u32)(offset)))

struct gdt_ptr {
u16 len;
u32 ptr;
} __attribute__((packed));

struct pte_t{

} __attribute__((packed));

struct pde_t{

} __attribute__((packed));

extern struct boot_params_t *boot_params_p;
extern void *_end_kernel;
#endif//_ASM_H_
