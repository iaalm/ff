ff
==

A test-used operation system kernel running on x86_32 platform in protected mode. 

## Finished

+ Process Scheduling

+ Memory management with slab allocator

+ Timer Manager

## Compile

Make sure you have installed *make* and *gcc* .

Compile it with the following command.

	make

then the kernel will located at ./img 

##Install

###Virtual Machine
If you have qemu on your computer ,you can run the following command to boot this kernel in virtual machine.

	make run

###Real Machine

This kernel is compliant with the **multiboot specification** , so that you can boot it just like a linux kernel.

##Debug
A simple way to debug this kernel is running this command

	make debug
it will use the *gdb_script* as debug script. 
