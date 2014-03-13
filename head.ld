OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
	. = 0x100000;
	.text		: {
			*(.head)
			*(.text)
	}
	.data		: {
			*(.data*)
	}
	.bss		: { *(.bss) }
	.stack		: {
		_stack_top_ = .;
		_stack_buttun_ = (_stack_top_ + 4096);
		. = _stack_buttun_;
	}
	_end_kernel = .;
}
