#pragma once
#include "I8080/I8080.h"

/**
 * @brief Decrement Register Implementation
 * @details The specified register is decremented by one.
 * @short Register,S,P,Z = Reg-1
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to decrement.
 */
FORCE_INLINE void PerformDCR(I8080 &cpu, BYTE &targetRegister) {
    const BYTE targetCopy = targetRegister;
    targetRegister = (BYTE)(targetRegister + 0xFF); // +(-1) is better than -1
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(targetRegister, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(targetCopy, 0xFF);
}

/**
 * @brief Decrement Accumulator
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_A(Memory &memory, I8080 &cpu) {
    PerformDCR(cpu, cpu.A);
}

/**
 * @brief Decrement B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_B(Memory &memory, I8080 &cpu) {
    PerformDCR(cpu, cpu.B);
}

/**
 * @brief Decrement C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_C(Memory &memory, I8080 &cpu) {
    PerformDCR(cpu, cpu.C);
}

/**
 * @brief Decrement D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_D(Memory &memory, I8080 &cpu) {
    PerformDCR(cpu, cpu.D);
}

/**
 * @brief Decrement E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_E(Memory &memory, I8080 &cpu) {
    PerformDCR(cpu, cpu.E);
}

/**
 * @brief Decrement H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_H(Memory &memory, I8080 &cpu) {
    PerformDCR(cpu, cpu.H);
}

/**
 * @brief Decrement L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_L(Memory &memory, I8080 &cpu) {
    PerformDCR(cpu, cpu.L);
}

/**
 * @brief Decrement Memory value
 * @details The specified memory byte is decremented by one.
 * @short Mem,S,P,Z = Memory-1
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    BYTE memoryValue = cpu.ReadByte(memory, memoryAddress);
    const BYTE memoryCopy = memoryValue;
    memoryValue = (BYTE)(memoryValue + 0xFF); // +(-1) is better than -1
    cpu.WriteByte(memory, memoryValue, memoryAddress);
    cpu.Status.UpdateStatusByValue(memoryValue, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(memoryCopy, 0xFF);
}
