/*
******************************************************************************
**
**  File        : linker.ld
**
**  Author      : Malek Lamari
**
**  Date        : 18/05/2021
**
**  Abstract    : Linker script for Cortex-M7
**
**  Target      : Cortex-M7
**
**  No license, use as you wish, no warranty
**
****************************************************************************
*/

/* Entry Point */
ENTRY(core_SysEntry)

MEMORY
{
  rom      (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
  ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

STACK_SIZE = 0x2000;

/* Section Definitions */
SECTIONS
{
	.isr_vector :
	{
    	. = ALIGN(4);
    	KEEP(*(.isr_vector))
    	. = ALIGN(4);
  	} > rom
  	
    .text :
    {
        . = ALIGN(4);
        _stext = .;
        *(.text)
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    } > rom
    
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } > rom

    .data :
    {
    	. = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > ram AT >rom
    
    . = ALIGN(4);
    
    /* .bss section which is used for uninitialized data */
    .bss (NOLOAD) :
    {
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > ram

    /* stack section */
    .stack (NOLOAD):
    {
    	. = ALIGN(8);
        _sstack = .;
        . = . + STACK_SIZE;
        . = ALIGN(8);
        _estack = .;
    } > ram

	.ARM.attributes 0 : { *(.ARM.attributes) }
}
