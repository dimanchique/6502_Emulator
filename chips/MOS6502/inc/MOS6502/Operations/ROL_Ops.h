#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Rotate Left Implementation
 * @details Move each of the bits in either A or M one place to the left.
 * Bit 0 is filled with the current value of the carry flag whilst the old bit 7 becomes the new carry flag value.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformROL(Memory &memory, MOS6502 &cpu, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
    const WORD address = cpu.GetAddressingModeAddress(memory, addressing, shouldCheckPageCross);

    BYTE memoryValue = cpu.ReadByte(memory, address);
    const bool carry = memoryValue & (1 << 7);
    memoryValue <<= 1;
    memoryValue |= cpu.Status.C;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Rotate Left Accumulator
 * @details Same as PerformROL, but with Accumulator as target.
 * @param memory Memory struct instance
 * @param cpu MOS6502 struct instance
 */
void MOS6502_ROL_ACC(Memory &memory, MOS6502 &cpu) {
    const bool carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.A |= cpu.Status.C;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Rotate Left
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ROL_ZP(Memory &memory, MOS6502 &cpu) {
    PerformROL(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Rotate Left
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ROL_ZPX(Memory &memory, MOS6502 &cpu) {
    PerformROL(memory, cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Rotate Left
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ROL_ABS(Memory &memory, MOS6502 &cpu) {
    PerformROL(memory, cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Rotate Left
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ROL_ABSX(Memory &memory, MOS6502 &cpu) {
    PerformROL(memory, cpu, MOS6502_AddressingMode::Absolute_X, false);
}
