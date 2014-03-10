#include"ctype.h"
inline void outb(u16 port,u8 value){
	asm volatile ( "outb	%0,%1"::"a"(value),"dN"(port));
}
inline u8 inb(u16 port){
	u8 value;
	asm volatile ( "inb	%1,%0":"=a"(value):"dN"(port));
	return value;
}
inline u16 ds(void)
{
	u16 seg;
	asm("movw %%ds,%0" : "=rm" (seg));
	return seg;
}
inline u16 cs(void)
{
	u16 seg;
	asm("movw %%cs,%0" : "=rm" (seg));
	return seg;
}
inline void sti(){
	asm volatile ("sti");
}
inline void cli(){
	asm volatile ("cli");
}


