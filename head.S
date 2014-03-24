	.code32
	.section .head
	.globl	_start
_start:
	mov	%esi,boot_params_p
	mov	$_stack_buttun_, %esp
	mov	$kernel, %eax
	push	%eax
	ret	
	.globl	init_process
init_process:
	mov	$tss,%eax
	mov	%ss,0x8(%eax)
	mov	%esp,0x4(%eax)
	//mov	%ax,%cs
	mov	$0x2b,%ax	//actually ring3 need its own stack
	push	%ax
	push	%esp
	mov	$0x20,%ax
	push	%ax
	push	$process
	lret

	.globl boot_params_p
boot_params_p:	.long	0
	.globl	tss
tss:
	.long	0	//back
	.long	0	//esp0
	.long	0	//ss0
	.long	0	//esp1
	.long	0	//ss1
	.long	0	//esp2
	.long	0	//ss2
	.long	0	//cr3
	.long	0	//eip
	.long	0	//eflags
	.long	0	//eax
	.long	0	//ecx
	.long	0	//edx
	.long	0	//ebx
	.long	0	//esp
	.long	0	//ebp
	.long	0	//esi
	.long	0	//edi
	.long	0	//es
	.long	0	//cs
	.long	0	//ss
	.long	0	//ds
	.long	0	//fs
	.long	0	//gs
	.long	0	//ldt
	.short	0	//debug
	.short	0	//i/o map
