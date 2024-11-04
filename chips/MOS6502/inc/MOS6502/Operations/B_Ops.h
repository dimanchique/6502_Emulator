#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Branch Implementation
 * @details If the checkFlag is equal to expectedValue then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param checkFlag Status flag to check.
 * @param expectedValue Expected value of status flag.
 */
FORCE_INLINE void PerformB(Memory &memory, MOS6502 &cpu, const BYTE checkFlag, const bool expectedValue) {
    const SBYTE offset = (SBYTE)cpu.FetchByte(memory);
    if (checkFlag == expectedValue) {
        cpu.cycles++;
        if (IsPageCrossed(cpu.PC, cpu.PC + offset))
            cpu.cycles++;
        cpu.PC += offset;
    }
}

/**
 * @brief Branch if Carry Clear
 * @details If the carry flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @addressing Relative
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BCC_REL(Memory &memory, MOS6502 &cpu) {
    PerformB(memory, cpu, cpu.Status.C, false);
}

/**
 * @brief Branch if Carry Set
 * @details If the carry flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @addressing Relative
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BCS_REL(Memory &memory, MOS6502 &cpu) {
    PerformB(memory, cpu, cpu.Status.C, true);
}

/**
 * @brief Branch if Equal
 * @details If the zero flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @addressing Relative
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BEQ_REL(Memory &memory, MOS6502 &cpu) {
    PerformB(memory, cpu, cpu.Status.Z, true);
}

/**
 * @brief Branch if Not Equal
 * @details If the zero flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @addressing Relative
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BNE_REL(Memory &memory, MOS6502 &cpu) {
    PerformB(memory, cpu, cpu.Status.Z, false);
}

/**
 * @brief Branch if Minus
 * @details If the negative flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @addressing Relative
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BMI_REL(Memory &memory, MOS6502 &cpu) {
    PerformB(memory, cpu, cpu.Status.N, true);
}

/**
 * @brief Branch if Positive
 * @details If the negative flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @addressing Relative
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BPL_REL(Memory &memory, MOS6502 &cpu) {
    PerformB(memory, cpu, cpu.Status.N, false);
}

/**
 * @brief Branch if Overflow Clear
 * @details If the overflow flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @addressing Relative
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BVC_REL(Memory &memory, MOS6502 &cpu) {
    PerformB(memory, cpu, cpu.Status.V, false);
}

/**
 * @brief Branch if Overflow Set
 * @details If the overflow flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @addressing Relative
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BVS_REL(Memory &memory, MOS6502 &cpu) {
    PerformB(memory, cpu, cpu.Status.V, true);
}
