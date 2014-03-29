struct timer{
	u32 now;
	u32 count;
	void (*cb)();
	struct timer *nxt,*pre;
};

extern void init_timer();
extern struct timer* add_timer(void(*)(),u32);
extern void del_timer(struct timer*);
extern u64 get_tc();
