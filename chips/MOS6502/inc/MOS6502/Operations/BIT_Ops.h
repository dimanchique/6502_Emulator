#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Bit Test Implementation
 * @details This instructions is used to test if one or more bits are set in a target memory location.
 * The mask pattern in A is ANDed with the value in memory to set or clear the zero flag, but the result is not kept.
 * Bits 7 and 6 of the value from memory are copied into the N and V flags.
 * @short A & M, N = M7, V = M6
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformBIT(Memory &memory, MOS6502 &cpu, const MOS6502_AddressingMode addressing) {
    const BYTE mask = cpu.GetAddressingModeValue(memory, addressing);

    const BYTE value = cpu.A & mask;
    cpu.Status.Z = value == 0;
    cpu.Status.V = (mask >> 6) & 1;
    cpu.Status.N = (mask >> 7) & 1;
}

/**
 * @brief Bit Test
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BIT_ZP(Memory &memory, MOS6502 &cpu) {
    PerformBIT(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Bit Test
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BIT_ABS(Memory &memory, MOS6502 &cpu) {
    PerformBIT(memory, cpu, MOS6502_AddressingMode::Absolute);
}
