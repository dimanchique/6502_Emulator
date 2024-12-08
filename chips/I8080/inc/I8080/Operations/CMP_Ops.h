#pragma once
#include "I8080/I8080.h"

/**
 * @brief Compare Implementation
 * @details The specified byte is compared to the contents of the Accumulator. The comparison is performed
 * by internally subtracting the contents of Register from the Accumulator (leaving both unchanged)
 * and setting the condition bits according to the result.
 * @short Z,C = A - (Register or Memory)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param targetRegister Value to compare Accumulator with
 */
FORCE_INLINE void PerformComparison(Memory &memory, I8080 &cpu, const BYTE &targetRegister) {
    const BYTE comparisonResult = cpu.A - targetRegister;
    cpu.Status.UpdateStatusByValue(comparisonResult, I8080_Status_Z | I8080_Status_C);
}

/**
 * @brief Compare Accumulator
 * @details Comparison A and A is trivial by definition. All we need to do is to set the condition bits.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_A(Memory &memory, I8080 &cpu) {
    cpu.Status.Z = 1;
    cpu.Status.C = 0;
}

/**
 * @brief Compare B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_B(Memory &memory, I8080 &cpu) {
    PerformComparison(memory, cpu, cpu.B);
}

/**
 * @brief Compare C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_C(Memory &memory, I8080 &cpu) {
    PerformComparison(memory, cpu, cpu.C);
}

/**
 * @brief Compare D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_D(Memory &memory, I8080 &cpu) {
    PerformComparison(memory, cpu, cpu.D);
}

/**
 * @brief Compare E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_E(Memory &memory, I8080 &cpu) {
    PerformComparison(memory, cpu, cpu.E);
}

/**
 * @brief Compare H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_H(Memory &memory, I8080 &cpu) {
    PerformComparison(memory, cpu, cpu.H);
}

/**
 * @brief Compare L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_L(Memory &memory, I8080 &cpu) {
    PerformComparison(memory, cpu, cpu.L);
}

/**
 * @brief Compare Memory value
 * @details Memory value address is computing using paired HL as an absolute 16-bit address.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE cmpValue = cpu.ReadByte(memory, memoryAddress);
    PerformComparison(memory, cpu, cmpValue);
}

/**
 * @brief Compare Immediate value
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CPI(Memory &memory, I8080 &cpu) {
    const BYTE cmpValue = cpu.FetchByte(memory);
    PerformComparison(memory, cpu, cmpValue);
}
