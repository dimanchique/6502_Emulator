#pragma once

#include "I8086/I8086.h"
#include "Adressing.h"

FORCE_INLINE void PerformXCHG_AX(I8086 &cpu, WORD* regPtr) {
    WORD tmp = cpu.AX;
    cpu.AX = *regPtr;
    *regPtr = tmp;
}

void I8086_XCHG_CX_AX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.CX);
}

void I8086_XCHG_DX_AX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.DX);
}

void I8086_XCHG_BX_AX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.BX);
}

void I8086_XCHG_SP_AX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.SP);
}

void I8086_XCHG_BP_AX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.BP);
}

void I8086_XCHG_SI_AX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.SI);
}

void I8086_XCHG_DI_AX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.DI);
}
