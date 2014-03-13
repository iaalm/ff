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
	pop	%eax	#clean stack why?
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
