#pragma once
#include "I8080/I8080.h"

/**
 * @brief Subtract Register or Memory From Accumulator
 * @details The specified byte is subtracted from the accumulator using two's complement arithmetic.
 * @short A,C,Z,S,P,AC = A+(-(Register or Memory))
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to subtract from Accumulator.
 */
FORCE_INLINE void PerformSUB(I8080 &cpu, const BYTE &targetRegister) {
    const BYTE initialAccumulator = cpu.A;
    const BYTE initialSrc = ~targetRegister;
    const WORD subResult = (cpu.A + initialSrc + 1) ^ 0x100;
    cpu.Status.C = ((subResult & 0x0100) != 0);
    cpu.A = subResult & 0xFF;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_P);
    cpu.Status.S = subResult > 0xFF;
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, targetRegister);
}

/**
 * @brief Subtract Accumulator From Accumulator (special case)
 * @details The two's compliment content of the Accumulator plus the content of the Carry bit is subtracted from the contents of the Accumulator.
 * @short A,C,Z,S,P,AC = A+(-A)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SUB_A(Memory &memory, I8080 &cpu) {
    const BYTE initialAccumulator = cpu.A;
    cpu.Status.C = 0;
    cpu.A = 0; // because A - A always 0
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, initialAccumulator);
}

/**
 * @brief Subtract B From Accumulator
 * @short A,C,Z,S,P,AC = A+(-B)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SUB_B(Memory &memory, I8080 &cpu) {
    PerformSUB(cpu, cpu.B);
}

/**
 * @brief Subtract C From Accumulator
 * @short A,C,Z,S,P,AC = A+(-C)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SUB_C(Memory &memory, I8080 &cpu) {
    PerformSUB(cpu, cpu.C);
}

/**
 * @brief Subtract D From Accumulator
 * @short A,C,Z,S,P,AC = A+(-D)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SUB_D(Memory &memory, I8080 &cpu) {
    PerformSUB(cpu, cpu.D);
}

/**
 * @brief Subtract E From Accumulator
 * @short A,C,Z,S,P,AC = A+(-E)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SUB_E(Memory &memory, I8080 &cpu) {
    PerformSUB(cpu, cpu.E);
}

/**
 * @brief Subtract H From Accumulator
 * @short A,C,Z,S,P,AC = A+(-H)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SUB_H(Memory &memory, I8080 &cpu) {
    PerformSUB(cpu, cpu.H);
}

/**
 * @brief Subtract L From Accumulator
 * @short A,C,Z,S,P,AC = A+(-L)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SUB_L(Memory &memory, I8080 &cpu) {
    PerformSUB(cpu, cpu.L);
}

/**
 * @brief Subtract Memory From Accumulator
 * @short A,C,Z,S,P,AC = A+(-Memory)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SUB_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE subValue = cpu.ReadByte(memory, memoryAddress);
    PerformSUB(cpu, subValue);
}

/**
 * @brief Subtract Immediate From Accumulator
 * @short A,C,Z,S,P,AC = A+(-Memory) (immediate value)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SUI(Memory &memory, I8080 &cpu) {
    const BYTE subValue = cpu.FetchByte(memory);
    PerformSUB(cpu, subValue);
}
