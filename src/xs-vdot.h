#include <stdint.h>

static inline int64_t xs_vdot(int64_t a, int64_t b) {
    int64_t result;
    asm volatile(
        ".insn r 0x0b, 0, 0, %0, %1, %2"
        : "=r" (result)
        : "r" (a), "r" (b)
        : "memory"
    );
    return result;
}