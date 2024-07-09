#include <stdint.h>

inline void mld(volatile int64_t * loadAddr, int offset, int type, int mreg) {
    __asm__ volatile (
       //.insn i opcode6, func3, rd,  rs1,    simm12
        ".insn i 0x2b, %[type], x%[reg], %[rs1], %[offset]"
        :"=r"(mreg)
        :[rs1]"r"(loadAddr),[type]"i"(type), [offset]"i"(offset), [reg]"i"(mreg)
    );
}

inline void mst(volatile int64_t * storeAddr, int offset, int type, int mreg) {
    __asm__ volatile (
        //.insn s opcode6, func3, rs2, simm12(rs1)
        ".insn s 0x2b, %[type], x%[rs2], %[offset](%[rs1])"
        :"=r"(mreg)
        :[rs1]"r"(storeAddr), [type]"i"(type), [offset]"i"(offset), [rs2]"i"(mreg)

    );
}

inline void mmul(int m1, int m2, int mrd) {
    __asm__ volatile (
       // .insn r opcode6, func3, func7,      rd,     rs1,       rs2
        ".insn r     0x2b,     0,     0, x%[rd], x%[rs1],    x%[rs2]"
        :"=r"(mrd)
        :[rd]"i"(mrd), [rs1]"i"(m2), [rs2]"i"(m1)
    );

}

inline void mtest(int mrd, int mrs1, int mrs2) {
    __asm__ volatile (
       // .insn r opcode6, func3, func7,      rd,     rs1,       rs2
        ".insn r     0x2b,     1,     0, x%[rd], x%[rs1],    x%[rs2]"
        :"=r"(mrd)
        :[rd]"i"(mrd), [rs1]"i"(mrs1), [rs2]"i"(mrs2)
    );

}

inline void mload(volatile int64_t * loadAddr_1, volatile int64_t * loadAddr_2, int mrd) {
    mld(loadAddr_1, 0, 7, mrd);
    mld(loadAddr_2, 0, 7, mrd+8);
}

inline void mstore(volatile int64_t * storeAddr_1, volatile int64_t * storeAddr_2, int mrs) {
    mst(storeAddr_1, 0, 3, mrs);
    mst(storeAddr_2, 0, 3, mrs+8);
}