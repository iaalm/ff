#define PAGE_FAULT 14
#define TIMER 0x20

extern u64 idt[256];
extern void timer_irq();
extern void p();
extern void pf();
extern void gp();
extern void df();
extern void timer_irq();
extern void udef_fun();
