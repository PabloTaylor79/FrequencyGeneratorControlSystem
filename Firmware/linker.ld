/**
 * Linker script for STM32H743 microcontroller
 * Memory layout and section definitions
 */

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
  RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 1024K
  CCRAM (rwx) : ORIGIN = 0x30000000, LENGTH = 256K
}

ENTRY(Reset_Handler)

SECTIONS
{
  /* Vectors section */
  .vectors :
  {
    KEEP(*(.vectors))
  } > FLASH

  /* Code section */
  .text :
  {
    *(.text*)
    *(.rodata*)
    *(.constdata)
    
    KEEP(*(.init))
    KEEP(*(.fini))
  } > FLASH

  /* ARM exception unwind info */
  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > FLASH
  
  .ARM :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } > FLASH

  /* Initialized data section */
  .data :
  {
    __data_start__ = .;
    *(vtable)
    *(.data*)
    __data_end__ = .;
  } > RAM AT > FLASH

  __data_load_start__ = LOADADDR(.data);
  __data_load_end__ = __data_load_start__ + SIZEOF(.data);

  /* Uninitialized data section */
  .bss :
  {
    __bss_start__ = .;
    *(.bss*)
    *(COMMON)
    __bss_end__ = .;
  } > RAM

  __bss_size__ = __bss_end__ - __bss_start__;

  /* Stack and heap */
  .stack (NOLOAD) :
  {
    . = ALIGN(8);
    __stack_bottom__ = .;
    . += 0x10000; /* 64KB stack */
    __stack_top__ = .;
  } > RAM

  .heap (NOLOAD) :
  {
    . = ALIGN(8);
    __heap_bottom__ = .;
    . += 0x40000; /* 256KB heap */
    __heap_top__ = .;
  } > RAM
}