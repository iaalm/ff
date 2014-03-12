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
