[BIT 32]
main:
	;clear bss
	mov	sp,STACK_BUTTUN
	mov	eax,kernel_start
	push	eax
	ret

[.SECTION bss]
STACK_BUTTUN:
	times 512 db 0
STACK_TOP:
