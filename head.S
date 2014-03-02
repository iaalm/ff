	.code32
	.section .head
	.globl	_start
_start:
	movl	$_stack_buttun_, %esp
	movl	$kernel, %eax
	pushl	%eax
	ret
	.globl	p
p:
	mov	$0x0c,%ah
	mov	$'!',%al
	mov	%ax,0xb83e8
	iret


