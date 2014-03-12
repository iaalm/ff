#define PAGE_FAULT 14
#define TIMER 0x20

extern u64 idt[256];
extern void p();
extern void pf();
extern void udef_fun();
