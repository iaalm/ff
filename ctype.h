#ifndef _CTYPE_H_
#define _CTYPE_H_

#define NULL (0)
typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef u32 size_t;
struct boot_params;

#define LKLIST_ADD(pos,item) do{		\
	(item)->nxt = (pos)->nxt;	\
	(item)->pre = (pos);		\
	(pos)->nxt->pre = (item);	\
	(pos)->nxt = (item);		\
}while(0)

#define LKLIST_DEL(pos) do{			\
	(pos)->pre->nxt = (pos)->nxt;	\
	(pos)->nxt->pre	= (pos)->pre;	\
}while(0)

#define LKLIST_FOREACH(head,i) for(i = (head);i->nxt != (head) && i != NULL;i = i->nxt) 

#endif//_CTYPE_H_
