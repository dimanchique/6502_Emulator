#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Decrement Memory Implementation
 * @details Subtracts one from the value held at a specified memory location
 * setting the zero and negative flags as appropriate.
 * @short M,Z,N = M-1
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformDEC(Memory &memory, MOS6502 &cpu, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
    const WORD address = cpu.GetAddressingModeAddress(memory, addressing, shouldCheckPageCross);

    BYTE memoryValue = cpu.ReadByte(memory, address);
    memoryValue--;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Decrement Memory
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_DEC_ZP(Memory &memory, MOS6502 &cpu) {
    PerformDEC(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Decrement Memory
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_DEC_ZPX(Memory &memory, MOS6502 &cpu) {
    PerformDEC(memory, cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Decrement Memory
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_DEC_ABS(Memory &memory, MOS6502 &cpu) {
    PerformDEC(memory, cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Decrement Memory
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_DEC_ABSX(Memory &memory, MOS6502 &cpu) {
    PerformDEC(memory, cpu, MOS6502_AddressingMode::Absolute_X, false);
}

/**
 * @brief Decrement X Register
 * @addressing Implied
 * @short X,Z,N = X-1
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_DEX_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.X--;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.X, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Decrement Y Register
 * @addressing Implied
 * @short Y,Z,N = Y-1
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_DEY_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.Y--;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.Y, MOS6502_Status_Z | MOS6502_Status_N);
}
