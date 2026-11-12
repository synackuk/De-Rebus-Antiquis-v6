.thumb
.syntax unified
.text

.global _start
.code 16

_start:
    @ Reset the SP.
    ldr.w sp, =SAFE_SP

    @ Disable interrupts.
    ldr r3, =DISABLE_INTERRUPTS
    blx r3

    @ Patch Diags handler type 5 (diags) -> 0 (unknown)
    mov r0, #0x94c
    ldr r1, =0x48312100
    str r1, [r0]

    @ Patch mov r0, 'diag' -> mov r0, 'ibob'
    ldr r1, =0x7062F646
    str r1, [r0, #0x8]
    ldr r1, =0x1062F6C6
    str r1, [r0, #0xC]

    @ Disable signature checks
    ldr r0, =0x1ae74
    movw r1, #0x2000
    b after

# This block must be 0.
.space 0x8

after:
    movt r1, #0x6018
    str r1, [r0]

    @ Patch fsboot handler -> diags handler
    ldr r0, =0x46004

    mov r1, #0x941
    str r1, [r0]

    @ Run nettoyeur
    ldr r0, =NETTOYEUR
    blx r0

    @ WTF?
    ldr r7, =WTF
    blx r7

    @ Disable the cache.
    ldr r7, =ARM_CPU_QUIESCE
    blx r7
    
    @ Restart iBoot.
    ldr r7, =LOAD_ADDR
    bx r7

.align 4
.pool
.set SAFE_SP,                0x9fff8000
.set DISABLE_INTERRUPTS,     0x9ff36e6d
.set ARM_CPU_QUIESCE,        0x9ff21e69
.set WTF,                    0x9ff016c9
.set NETTOYEUR,              0x9FF4A06D
.set LOAD_ADDR,              0x9ff00000
