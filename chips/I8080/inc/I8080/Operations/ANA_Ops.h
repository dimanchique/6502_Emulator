#pragma once
#include "I8080/I8080.h"

/**
 * @brief Logical AND Implementation
 * @details A logical AND is performed, bit by bit, on the Accumulator contents using the contents of a given byte (register of memory).
 * @short A,S,P,Z = A&(Register or Memory)
 * @param cpu I8080 struct instance.
 * @param value Value to perform AND with.
 */
FORCE_INLINE void PerformANA(I8080 &cpu, const BYTE value) {
    cpu.A &= value;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
}

/**
 * @brief Logical AND with register A
 * @details Instruction semantic: A=A&A. Register A stays the same.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ANA_A(Memory &memory, I8080 &cpu) {
    PerformANA(cpu, cpu.A);
}

/**
 * @brief Logical AND with register B
 * @details Instruction semantic: A=A&B.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ANA_B(Memory &memory, I8080 &cpu) {
    PerformANA(cpu, cpu.B);
}

/**
 * @brief Logical AND with register C
 * @details Instruction semantic: A=A&C.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ANA_C(Memory &memory, I8080 &cpu) {
    PerformANA(cpu, cpu.C);
}

/**
 * @brief Logical AND with register D
 * @details Instruction semantic: A=A&D.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ANA_D(Memory &memory, I8080 &cpu) {
    PerformANA(cpu, cpu.D);
}

/**
 * @brief Logical AND with register E
 * @details Instruction semantic: A=A&E.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ANA_E(Memory &memory, I8080 &cpu) {
    PerformANA(cpu, cpu.E);
}

/**
 * @brief Logical AND with register H
 * @details Instruction semantic: A=A&H.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ANA_H(Memory &memory, I8080 &cpu) {
    PerformANA(cpu, cpu.H);
}

/**
 * @brief Logical AND with register L
 * @details Instruction semantic: A=A&L.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ANA_L(Memory &memory, I8080 &cpu) {
    PerformANA(cpu, cpu.L);
}

/**
 * @brief Logical AND with memory value
 * @details Instruction semantic: A=A&Memory. Memory value address is computing using paired HL as an absolute 16-bit address.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ANA_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE value = cpu.ReadByte(memory, memoryAddress);
    PerformANA(cpu, value);
}
