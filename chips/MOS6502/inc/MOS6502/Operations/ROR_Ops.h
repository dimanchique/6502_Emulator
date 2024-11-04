#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Rotate Right Implementation
 * @details Move each of the bits in either A or M one place to the right.
 * Bit 7 is filled with the current value of the carry flag whilst the old bit 0 becomes the new carry flag value.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformROR(Memory &memory, MOS6502 &cpu, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
    const WORD address = cpu.GetAddressingModeAddress(memory, addressing, shouldCheckPageCross);

    BYTE memoryValue = cpu.ReadByte(memory, address);
    const bool carry = memoryValue & 1;
    memoryValue >>= 1;
    memoryValue |= cpu.Status.C << 7;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Rotate Right Accumulator
 * @details Same as PerformROR, but with Accumulator as target.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ROR_ACC(Memory &memory, MOS6502 &cpu) {
    const bool carry = cpu.A & 1;
    cpu.A >>= 1;
    cpu.A |= cpu.Status.C << 7;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Rotate Right
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ROR_ZP(Memory &memory, MOS6502 &cpu) {
    PerformROR(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Rotate Right
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ROR_ZPX(Memory &memory, MOS6502 &cpu) {
    PerformROR(memory, cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Rotate Right
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ROR_ABS(Memory &memory, MOS6502 &cpu) {
    PerformROR(memory, cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Rotate Right
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ROR_ABSX(Memory &memory, MOS6502 &cpu) {
    PerformROR(memory, cpu, MOS6502_AddressingMode::Absolute_X, false);
}
