#pragma once
#include "CPU6502.h"

inline void ExecuteCL(U32 &cycles, CPU6502 &cpu, const BYTE statusFlag) {
    cpu.Status.ResetFlag(statusFlag);
    CPU6502::DoTick(cycles);
}

void CPU6502_CLC_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CLD_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CLI_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CLV_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
