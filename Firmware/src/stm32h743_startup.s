/**
 * STM32H743 startup code
 * Cortex-M7 initialization and vector table
 */

  .syntax unified
  .cpu cortex-m7
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* Linker provided symbols */
.extern __data_load_start__
.extern __data_load_end__
.extern __data_start__
.extern __data_end__
.extern __bss_start__
.extern __bss_end__
.extern __stack_top__
.extern main

/* Vector table */
.section .vectors, "ax"
.align 2
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word __stack_top__           /* 0x0000  Top of Stack */
  .word Reset_Handler           /* 0x0004  Reset Handler */
  .word NMI_Handler             /* 0x0008  NMI Handler */
  .word HardFault_Handler       /* 0x000C  Hard Fault Handler */
  .word MemManage_Handler       /* 0x0010  Memory Manage Fault Handler */
  .word BusFault_Handler        /* 0x0014  Bus Fault Handler */
  .word UsageFault_Handler      /* 0x0018  Usage Fault Handler */
  .word 0                       /* 0x001C  Reserved */
  .word 0                       /* 0x0020  Reserved */
  .word 0                       /* 0x0024  Reserved */
  .word 0                       /* 0x0028  Reserved */
  .word SVC_Handler             /* 0x002C  SVCall Handler */
  .word DebugMon_Handler        /* 0x0030  Debug Monitor Handler */
  .word 0                       /* 0x0034  Reserved */
  .word PendSV_Handler          /* 0x0038  PendSV Handler */
  .word SysTick_Handler         /* 0x003C  SysTick Handler */
  
  /* External interrupts (IRQ0-135) */
  .rept 136
  .word Default_Handler
  .endr

/* Reset handler */
.section .text.Reset_Handler, "ax"
.thumb_func
.type Reset_Handler, %function
Reset_Handler:
  /* Disable interrupts */
  cpsid i
  
  /* Set stack pointer from linker script value */
  ldr sp, =__stack_top__
  
  /* Copy data from flash to RAM */
  ldr r0, =__data_load_start__
  ldr r1, =__data_load_end__
  ldr r2, =__data_start__
  
  cmp r0, r1
  beq data_copy_done
  
data_copy_loop:
  ldm r0!, {r3, r4, r5, r6, r7, r8, r9, r10}
  stm r2!, {r3, r4, r5, r6, r7, r8, r9, r10}
  cmp r0, r1
  blt data_copy_loop

data_copy_done:
  /* Zero out BSS section */
  ldr r0, =__bss_start__
  ldr r1, =__bss_end__
  mov r2, #0
  
  cmp r0, r1
  beq bss_zero_done
  
bss_zero_loop:
  stm r0!, {r2}
  cmp r0, r1
  blt bss_zero_loop

bss_zero_done:
  /* Call main */
  bl main
  
  /* Infinite loop if main returns */
  b .

.size Reset_Handler, . - Reset_Handler

/* Default exception handler */
.section .text.Default_Handler, "ax"
.thumb_func
.type Default_Handler, %function
Default_Handler:
  b .
.size Default_Handler, . - Default_Handler

/* Exception handlers - weakly linked */
.weak NMI_Handler
.weak HardFault_Handler
.weak MemManage_Handler
.weak BusFault_Handler
.weak UsageFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler

NMI_Handler:
HardFault_Handler:
MemManage_Handler:
BusFault_Handler:
UsageFault_Handler:
SVC_Handler:
DebugMon_Handler:
PendSV_Handler:
SysTick_Handler:
  b .

.end