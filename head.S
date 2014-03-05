	.code32
	.section .head
	.globl	_start
_start:
	mov	%esi,boot_params_p
	mov	$_stack_buttun_, %esp
	mov	$kernel, %eax
	push	%eax
	ret
	.globl boot_params_p
boot_params_p:	.long	0
	.globl	p
p:
	mov	0xb87d0,%ax
	add	$1,%ah
	mov	$'!',%al
	mov	%ax,0xb87d0
	# send EOI
	mov	$0x20,%al
	out	%al,$0x20

	iret


