#pragma once
#include "I8080/I8080.h"

/**
 * @brief Add Register or Memory To Accumulator With Carry Implementation
 * @details The specified byte plus the content of the Carry bit is added to the contents of the Accumulator.
 * @short A,C,Z,S,P,AC = A+Carry+(Register or Memory)
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to add to Accumulator.
 */
FORCE_INLINE void PerformAddWithCarry(I8080 &cpu, const BYTE &targetRegister) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = cpu.A + targetRegister + cpu.Status.C;
    const BYTE cachedCarry = cpu.Status.C;
    cpu.Status.C = addResult > 0xFF;
    cpu.A = addResult;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, targetRegister, cachedCarry);
}

/**
 * @brief Add Accumulator To Accumulator With Carry (special case)
 * @details The content of the Accumulator plus the content of the Carry bit is added to the contents of the Accumulator.
 * @short A,C,Z,S,P,AC = A+Carry+A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ADC_A(Memory &memory, I8080 &cpu) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = (cpu.A << 1) + cpu.Status.C;
    const BYTE cachedCarry = cpu.Status.C;
    cpu.Status.C = addResult > 0xFF;
    cpu.A = addResult;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, initialAccumulator, cachedCarry);
}

/**
 * @brief Add B To Accumulator With Carry
 * @short A,C,Z,S,P,AC = A+Carry+B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ADC_B(Memory &memory, I8080 &cpu) {
    PerformAddWithCarry(cpu, cpu.B);
}

/**
 * @brief Add C To Accumulator With Carry
 * @short A,C,Z,S,P,AC = A+Carry+C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ADC_C(Memory &memory, I8080 &cpu) {
    PerformAddWithCarry(cpu, cpu.C);
}

/**
 * @brief Add D To Accumulator With Carry
 * @short A,C,Z,S,P,AC = A+Carry+D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ADC_D(Memory &memory, I8080 &cpu) {
    PerformAddWithCarry(cpu, cpu.D);
}

/**
 * @brief Add E To Accumulator With Carry
 * @short A,C,Z,S,P,AC = A+Carry+E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ADC_E(Memory &memory, I8080 &cpu) {
    PerformAddWithCarry(cpu, cpu.E);
}

/**
 * @brief Add H To Accumulator With Carry
 * @short A,C,Z,S,P,AC = A+Carry+H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ADC_H(Memory &memory, I8080 &cpu) {
    PerformAddWithCarry(cpu, cpu.H);
}

/**
 * @brief Add L To Accumulator With Carry
 * @short A,C,Z,S,P,AC = A+Carry+L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ADC_L(Memory &memory, I8080 &cpu) {
    PerformAddWithCarry(cpu, cpu.L);
}

/**
 * @brief Add Memory To Accumulator With Carry
 * @short A,C,Z,S,P,AC = A+Carry+Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ADC_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE addValue = cpu.ReadByte(memory, memoryAddress);
    PerformAddWithCarry(cpu, addValue);
}

/**
 * @brief Add Immediate To Accumulator With Carry
 * @short A,C,Z,S,P,AC = A+Carry+Memory (immediate value)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ACI(Memory &memory, I8080 &cpu) {
    const BYTE addValue = cpu.FetchByte(memory);
    PerformAddWithCarry(cpu, addValue);
}
