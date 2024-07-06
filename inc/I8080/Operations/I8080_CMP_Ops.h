#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericCompareRegister(Memory &memory, I8080 &cpu, const BYTE &targetRegister) {
    const BYTE comparedValue = cpu.A - targetRegister;
    cpu.Status.UpdateStatusByValue(comparedValue, I8080_Status_Z | I8080_Status_S);
}

inline void I8080_CMP_A(Memory &memory, I8080 &cpu) {
    cpu.Status.Z = 1;
    cpu.Status.C = 0;
}

inline void I8080_CMP_B(Memory &memory, I8080 &cpu) {
    GenericCompareRegister(memory, cpu, cpu.B);
}

inline void I8080_CMP_C(Memory &memory, I8080 &cpu) {
    GenericCompareRegister(memory, cpu, cpu.C);
}

inline void I8080_CMP_D(Memory &memory, I8080 &cpu) {
    GenericCompareRegister(memory, cpu, cpu.D);
}

inline void I8080_CMP_E(Memory &memory, I8080 &cpu) {
    GenericCompareRegister(memory, cpu, cpu.E);
}

inline void I8080_CMP_H(Memory &memory, I8080 &cpu) {
    GenericCompareRegister(memory, cpu, cpu.H);
}

inline void I8080_CMP_L(Memory &memory, I8080 &cpu) {
    GenericCompareRegister(memory, cpu, cpu.L);
}

inline void I8080_CMP_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
    const BYTE cmpValue = cpu.ReadByte(memory, memoryAddress);
    GenericCompareRegister(memory, cpu, cmpValue);
}

inline void I8080_CPI(Memory &memory, I8080 &cpu) {
    const BYTE cmpValue = cpu.FetchByte(memory);
    GenericCompareRegister(memory, cpu, cmpValue);
}