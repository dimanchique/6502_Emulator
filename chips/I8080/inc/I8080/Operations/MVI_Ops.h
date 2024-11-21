#pragma once
#include "I8080/I8080.h"

/**
 * @brief Move Immediate Data Implementation
 * @details The byte of immediate data is stored in the specified register.
 * @short Register = MemoryImmediate
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param targetRegister Register for storing new value.
 */
FORCE_INLINE void PerformMVI(Memory &memory, I8080 &cpu, BYTE &targetRegister) {
    const BYTE immediateValue = cpu.FetchByte(memory);
    targetRegister = immediateValue;
}

/**
 * @brief Move Immediate Data to Accumulator
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MVI_A(Memory &memory, I8080 &cpu) {
    PerformMVI(memory, cpu, cpu.A);
}

/**
 * @brief Move Immediate Data to B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MVI_B(Memory &memory, I8080 &cpu) {
    PerformMVI(memory, cpu, cpu.B);
}

/**
 * @brief Move Immediate Data to C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MVI_C(Memory &memory, I8080 &cpu) {
    PerformMVI(memory, cpu, cpu.C);
}

/**
 * @brief Move Immediate Data to D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MVI_D(Memory &memory, I8080 &cpu) {
    PerformMVI(memory, cpu, cpu.D);
}

/**
 * @brief Move Immediate Data to E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MVI_E(Memory &memory, I8080 &cpu) {
    PerformMVI(memory, cpu, cpu.E);
}

/**
 * @brief Move Immediate Data to H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MVI_H(Memory &memory, I8080 &cpu) {
    PerformMVI(memory, cpu, cpu.H);
}

/**
 * @brief Move Immediate Data to L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MVI_L(Memory &memory, I8080 &cpu) {
    PerformMVI(memory, cpu, cpu.L);
}

/**
 * @brief Move Immediate Data to Memory location
 * @details The byte of immediate data is stored in the specified memory byte formed using HL register.
 * @short Memory = MemoryImmediate
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MVI_M(Memory &memory, I8080 &cpu) {
    const BYTE immediateValue = cpu.FetchByte(memory);
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    cpu.WriteByte(memory, immediateValue, memoryAddress);
}
