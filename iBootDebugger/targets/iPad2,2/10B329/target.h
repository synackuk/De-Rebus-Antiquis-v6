#ifndef TARGET_H
#define TARGET_H

#define SP_MOVW INSNW_MOVW_SP_0
#define SP_MOVT INSNW_MOVT_SP_8010

#define READP_BP_OFF 0x1a136
#define READP_SAFE_REG R12

#define MEMALIGN_START_BP_OFF 0x1a37e
#define MEMALIGN_START_SAFE_REG R3

#define MEMALIGN_LOOP_BP_OFF 0x1a3ae
#define MEMALIGN_LOOP_SAFE_REG R7

#define MEMALIGN_END_BP_OFF 0x1a4ca
#define MEMALIGN_END_SAFE_REG R7

/* Don't define any of this for the iBoot payload generator. */
#ifndef DEBUG_IBOOT_BUILDER

#define IBOOT_BASE_ADDR 0x9ff00000

/* A SP Offset near the BIN list, used to reduce the garbage from memalign breakpoints. */
#define SP_NEAR_BIN_LIST 0x9ff4a3f0

/* Registers for common handlers */
#define READP_SP_REG "r12"
#define STACK_DUMP_SP_REG "r3"

typedef int(*printf_t)(const char* fmt, ...);

const printf_t printf = (printf_t)0x9ff359ed;


__attribute__((always_inline)) static inline void fix_printf() {
	/* These offsets must be fixed or printf calls will fail. */
    *(uint32_t*)0x9ff4b064 = 0x9ff56e00;
    *(uint32_t*)0x9ff4a784 = 0x3;
    *(uint32_t*)0x9ff4a778 = 0x1;
}


__attribute__((always_inline)) static inline void memalign_start_handler() {
    register unsigned reg_r0 __asm("r0");
    uint32_t r0 = reg_r0;
    register unsigned reg_sp __asm("r3"); /* Contains the SP. */
    uint32_t sp = reg_sp;
    register unsigned reg_r8 __asm("r8"); /* Heap bin table */
    uint32_t r8 = reg_r8;
    uint32_t sb = 0x20 - r0;
    uint32_t inferred = r8 + (sb << 2);
    uint32_t r4 = inferred + 0x28; /* Next Bin */

    if(sp > SP_NEAR_BIN_LIST) {
        return;
    }

    fix_printf();
    printf("_memalign: sp=%p, r8=%p, sb=%p, r4=>%p(%p) = %p\n", sp, r8, sb, r4, sp - r4, *(uint32_t*)r4);

}

__attribute__((always_inline)) static inline void memalign_loop_handler() {
    register unsigned int reg_sp __asm("r7"); /* Contains the SP. */
    uint32_t sp = reg_sp;
    register unsigned int reg_r0 __asm("r0"); /* Current Chunk */
    uint32_t r0 = reg_r0;
    register unsigned int reg_r1 __asm("r1"); /* Required Chunk Size */
    uint32_t r1 = reg_r1;
    register unsigned int reg_r2 __asm("r2");
    uint32_t r2 = reg_r2;
    register unsigned int reg_r3 __asm("r3"); /* Chunk end */
    uint32_t r3 = reg_r3;
    register unsigned int reg_r4 __asm("r4"); /* Next bin */
    uint32_t r4 = reg_r4;
    register unsigned int reg_ip __asm("ip");
    uint32_t ip = reg_ip;
    register unsigned int reg_r5 __asm("r5"); /* Bitmask */
    uint32_t r5 = reg_r5;
    uint32_t old_r2 = (*(uint32_t*)(r0 + 0x4)) << 5;/* Actual Chunk Size */
    uint32_t sl = r2 - 0x20; /* Aligned chunk start */
    uint32_t r6 = r3 - sl; /* Remaining bytes */

    if(sp > SP_NEAR_BIN_LIST) {
        return;
    }

    printf("_memalign: sp=%p, r0=%p, r1=%p, r2=%p, r3=%p, r4=>(%p), sl=%p, r6=%p, ip=%p, r5=%p rd=%p wr=%p(%p)\n", sp, r0, r1, old_r2, r3, r4, sl, r6, ip, r5, *(uint32_t*)(r0 + 0x20), *(uint32_t*)(r0 + 0x24), **(uint32_t**)(r0 + 0x24));
}

__attribute__((always_inline)) static inline void memalign_end_handler() {
    register unsigned int reg_sp __asm("r7"); /* Contains the SP */
    uint32_t sp = reg_sp;
    register unsigned int reg_r8 __asm("r8"); /* Heap bin table */
    uint32_t r8 = reg_r8;
    uint32_t lr = *(uint32_t*)(sp + 0x18); /* The LR */

    if(sp > SP_NEAR_BIN_LIST) {
        return;
    }

    printf("_memalign: sp=%p, r8=%p, lr=%p\n", sp, r8, lr);
}

#endif

#endif