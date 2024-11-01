#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Logical Shift Right Implementation
 * @details Each of the bits in A or M is shift one place to the right.
 * The bit that was in bit 0 is shifted into the carry flag. Bit 7 is set to zero.
 * @short A,C,Z,N = A/2 or M,C,Z,N = M/2
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param address Address to write back shifted value.
 */
FORCE_INLINE void PerformLSR(Memory &memory, MOS6502 &cpu, const WORD address) {
    BYTE memoryValue = cpu.ReadByte(memory, address);
    const bool carry = memoryValue & 1;
    memoryValue >>= 1;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Logical Shift Right Accumulator
 * @details Same as PerformLSR, but with Accumulator as target.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ACC(Memory &memory, MOS6502 &cpu) {
    const bool carry = cpu.A & 1;
    cpu.A >>= 1;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Logical Shift Right
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.FetchByte(memory);
    PerformLSR(memory, cpu, address);
}

/**
 * @brief Logical Shift Right
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.GetZeroPageIndexedAddress(memory, cpu.X);
    PerformLSR(memory, cpu, address);
}

/**
 * @brief Logical Shift Right
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ABS(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.FetchWord(memory);
    PerformLSR(memory, cpu, address);
}

/**
 * @brief Logical Shift Right
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ABSX(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.GetAbsIndexedAddress(memory, cpu.X, false);
    PerformLSR(memory, cpu, address);
}
