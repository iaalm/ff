#ifndef _ASM_H_
#define _ASM_H_
#include"ctype.h"
inline void outb(u16 port,u8 value){
	asm volatile ( "outb	%0,%1"::"a"(value),"dN"(port));
}
inline u8 inb(u16 port){
	u8 value;
	asm volatile ( "inb	%1,%0":"=a"(value):"dN"(port));
	return value;
}
#define GDT_ENTRY(flags,base,limit)
#define IDT_ENTRY(flags,selecter,offset)	\
	((((u64)offset) & 0x00000000ffff0000) << (48 - 16))	\
	|((((u64)flags) & 0x000000000000ffff) << 32)		\
	|(((selecter) & 0x000000000000ffff) << 16)	\
	|(((u64)offset) & 0x000000000000ffff)
struct gdt_ptr {
u16 len;
u32 ptr;
} __attribute__((packed));
#endif//_ASM_H_
