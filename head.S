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
	mov	0xb83e8,%ax
	add	$1,%ah
	mov	$'!',%al
	mov	%ax,0xb83e8
	# send EOI
	mov	$0x20,%al
	out	%al,$0x20

	iret


