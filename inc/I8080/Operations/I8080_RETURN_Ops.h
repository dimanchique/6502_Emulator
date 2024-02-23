#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_RET(Memory &memory, I8080 &cpu) {
    cpu.PopProgramCounterOffStack(memory);
}

FORCE_INLINE void GenericReturn_Conditional(Memory &memory, I8080 &cpu, const bool& conditionFlag) {
    if (conditionFlag)
        cpu.PopProgramCounterOffStack(memory);
}

FORCE_INLINE void I8080_RC(Memory &memory, I8080 &cpu) {
    GenericReturn_Conditional(memory, cpu, cpu.Status.C);
}

FORCE_INLINE void I8080_RNC(Memory &memory, I8080 &cpu) {
    GenericReturn_Conditional(memory, cpu, !cpu.Status.C);
}

FORCE_INLINE void I8080_RM(Memory &memory, I8080 &cpu) {
    GenericReturn_Conditional(memory, cpu, cpu.Status.S);
}

FORCE_INLINE void I8080_RP(Memory &memory, I8080 &cpu) {
    GenericReturn_Conditional(memory, cpu, !cpu.Status.S);
}

FORCE_INLINE void I8080_RZ(Memory &memory, I8080 &cpu) {
    GenericReturn_Conditional(memory, cpu, cpu.Status.Z);
}

FORCE_INLINE void I8080_RNZ(Memory &memory, I8080 &cpu) {
    GenericReturn_Conditional(memory, cpu, !cpu.Status.Z);
}

FORCE_INLINE void I8080_RPE(Memory &memory, I8080 &cpu) {
    GenericReturn_Conditional(memory, cpu, cpu.Status.P);
}

FORCE_INLINE void I8080_RPO(Memory &memory, I8080 &cpu) {
    GenericReturn_Conditional(memory, cpu, !cpu.Status.P);
}
