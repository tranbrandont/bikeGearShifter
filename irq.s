        .text
        .align 1
        .global __irq_generic
        .syntax unified

__irq_generic:
        push {lr}

        /* Thread state saves only make sense if this     */
        /* interrupt interrupted from thread-mode         */
        /* If this is a stacked interrupt, skip the save. */
        mov  r0, lr
        ldr  r1, .L1+8
        cmp  r1, r0
        bne  .L10

        /* Save the current thread's state to its stack   */
        mrs  r0,  psp
        mov  r1,  sp
        mov  sp,  r0
        push {r4, r5, r6, r7}
        mov  r4,  r8
        mov  r5,  r9
        mov  r6,  r10
        mov  r7,  r11
        push {r4, r5, r6, r7}
        mov   r0,  sp
        mov   sp,  r1

        ldr  r1, .L1
        ldr  r1, [r1]
        str  r0, [r1,#4]

.L10:   /* Dispatch to an actual thread handler, if any */
        mrs  r0, psr
        movs r1, 0x3F
        ands r0, r1
        lsls r0, #2
        ldr  r1, .L1+4
        adds r0, r1
        ldr  r0, [r0]
        tst  r0, r0
        beq  .L0
        
        blx  r0
        
.L0:    /* The reverse of the entry: check to see if this  */
        /* not a stacked interrupt and restore thread ctx. */
        ldr  r0, [sp]
        ldr  r1, .L1+8
        cmp  r1, r0
        bne  .L11

        /* restore thread context */
        ldr  r1, .L1
        ldr  r1, [r1]
        ldr  r0, [r1,#4]

        ldm  r0!, {r4,r5,r6,r7}
        mov  r8,  r4
        mov  r9,  r5
        mov  r10, r6
        mov  r11, r7
        ldm  r0!, {r4,r5,r6,r7}
        msr  psp, r0
.L11:
        pop  {pc}
        .align 2
.L1:
        .word CURCTX
        .word __irq_handlers
        .word 0xFFFFFFFD

        
        .align 1
        .global __reset
__reset:
        /* Reset uses the main (aka, interrupt) stack by default */
        /* Switch to the __main__ thread's program stack         */
        /* See Section 28.4.1.2 for more information             */
        ldr  r0,  .L3
        ldr  r0,  [r0]
        msr  psp, r0
        mrs  r0,  control
        movs r1,  #2
        orrs r0,  r1
        msr  control, r0

        /* copy data from flash to sram                      */
        /* This is here to ensure that we use registers and  */
        /* not local variables that are stored on the stack, */
        /* which is in the data segment that we are copying. */
        ldr  r0, .L3+4
        ldr  r1, .L3+8
        ldr  r2, .L3+12
        b    .L5

.L4:
        ldr  r3, [r0]
        str  r3, [r1]
        adds r0, #4
        adds r1, #4
        
.L5:        
        cmp r1, r2
        bne .L4

        /* Since we are here, let's finish initializing the */
        /* runtime enviornment.  Zero-out BSS.              */
        ldr  r0, .L3+16
        ldr  r2, .L3+20
        eors r3, r3
        b    .L7
.L6:     
        str  r3, [r0]
        adds r0, #4
.L7:
        cmp  r0, r2
        bne  .L6

        /* Let's give reset a completely constructed and         */
        /* initalized system.  Run the module constructors.      */
        /* Using r6 and r7 because they are saved by the callee. */
        ldr  r6, .L3+24
        ldr  r7, .L3+28
        b    .L9
.L8:
        ldr  r0, [r6]
        blx  r0
        adds r6, #4
.L9:
        cmp  r6, r7
        bne  .L8

        /* Now that everything is setup, let's just call reset. */
        bl   reset
        .align 2
.L3:
        .word __PSP             // 0 Offsets
        .word __DATA_LMA        // 4
        .word __DATA_VMA        // 8
        .word __DATA_END        //12
        .word __BSS_VMA         //16
        .word __BSS_END         //20
        .word __INIT_VMA        //24
        .word __INIT_END        //28
        
