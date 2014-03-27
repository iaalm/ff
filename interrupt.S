	.globl	timer_irq
timer_irq:
		sub	$32,%esp	//del it!!
//store
	pushal
	push	%ds
	push	%es
	push	%fs
	push	%gs
	movl	%esp,%esi
	movl	$current,%edi
	movl	$12,%ecx
	rep;	movsb
	call	nxt_proc
	//restore
	movl	%esp,%edi
	movl	$current,%esi
	movl	$12,%ecx
	rep;	movsb
	pop	%gs
	pop	%fs
	pop	%es
	pop	%ds
	popal
	add	$32,%esp	//del it!!

	iret
	.globl	p
p:
	push	%ax
	mov	0xb87d0,%ax
	add	$1,%ah
	mov	$'!',%al
	mov	%ax,0xb87d0
	# send EOI
	mov	$0x20,%al
	out	%al,$0x20
	pop	%ax

	iret
	
	.globl	pf
pf:
	add	$4,%esp		//ignore the error code
	push	%eax
	mov	0x70,%ah
	mov	$'P',%al
	mov	%ax,0xb87d4

	mov	%cr0,%eax
	and	$0x7fffffff,%eax
	mov	%eax,%cr0
	mov	%cr2,%eax
	push	%eax
	call	do_page_fault
	pop	%eax
	mov	%cr0,%eax
	or	$0x80000000,%eax
	mov	%eax,%cr0

	pop	%eax
	iret
	.globl gp
gp:
	push	%ax
	mov	0xb87f2,%ax
	add	$1,%ah
	mov	$'G',%al
	mov	%ax,0xb87f2
	pop	%ax

	iret

	.globl df
df:
	push	%ax
	mov	0xb87f4,%ax
	add	$1,%ah
	mov	$'D',%al
	mov	%ax,0xb87f4
	pop	%ax

	iret

	.globl udef_fun
udef_fun:
	push	%ax
	mov	0xb87f0,%ax
	add	$1,%ah
	mov	$'U',%al
	mov	%ax,0xb87f0
	pop	%ax

	iret

