#pragma once
#include "I8080/I8080.h"

/**
 * @brief AC setter for XOR instruction. Service function
 * @details Custom logic to update Auxiliary Carry flag during perform XRA (XOR) instruction.
 * All we need to do is to take a fourth bit of old value and compare it with a fourth bit of a new (result) value.
 * @param cpu I8080 struct instance.
 * @param oldValue Value before XOR is performed.
 * @param newValue Value after XOR is performed.
 */
FORCE_INLINE void SetAuxiliaryCarryFlagOfXOR(I8080 &cpu, const BYTE &oldValue, const BYTE &newValue) {
    const bool oldAuxiliaryCarry = oldValue & 0b00001000;
    const bool newAuxiliaryCarry = newValue & 0b00001000;
    cpu.Status.AC = oldAuxiliaryCarry ^ newAuxiliaryCarry;
}

/**
 * @brief XOR Accumulator with given value
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param cpu I8080 struct instance.
 * @param value Value to XOR with.
 */
FORCE_INLINE void PerformXRA(I8080 &cpu, const BYTE value) {
    const BYTE targetCopy = cpu.A;
    cpu.A ^= value;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    SetAuxiliaryCarryFlagOfXOR(cpu, targetCopy, cpu.A);
}

/**
 * @brief XOR Accumulator with Immediate value
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XRI(Memory &memory, I8080 &cpu) {
    const BYTE targetCopy = cpu.A;
    const BYTE memoryValue = cpu.FetchByte(memory);
    cpu.A ^= memoryValue;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    SetAuxiliaryCarryFlagOfXOR(cpu, targetCopy, cpu.A);
}

/**
 * @brief XOR Accumulator with A
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XRA_A(Memory &memory, I8080 &cpu) {
    PerformXRA(cpu, cpu.A);
}

/**
 * @brief XOR Accumulator with B
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XRA_B(Memory &memory, I8080 &cpu) {
    PerformXRA(cpu, cpu.B);
}

/**
 * @brief XOR Accumulator with C
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XRA_C(Memory &memory, I8080 &cpu) {
    PerformXRA(cpu, cpu.C);
}

/**
 * @brief XOR Accumulator with D
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XRA_D(Memory &memory, I8080 &cpu) {
    PerformXRA(cpu, cpu.D);
}

/**
 * @brief XOR Accumulator with E
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XRA_E(Memory &memory, I8080 &cpu) {
    PerformXRA(cpu, cpu.E);
}

/**
 * @brief XOR Accumulator with H
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XRA_H(Memory &memory, I8080 &cpu) {
    PerformXRA(cpu, cpu.H);
}

/**
 * @brief XOR Accumulator with L
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XRA_L(Memory &memory, I8080 &cpu) {
    PerformXRA(cpu, cpu.L);
}

/**
 * @brief XOR Accumulator with Memory value
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XRA_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE value = cpu.ReadByte(memory, memoryAddress);
    PerformXRA(cpu, value);
}
