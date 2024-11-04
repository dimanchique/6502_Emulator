#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Increment Memory Implementation
 * @details Adds one to the value held at a specified memory location setting the zero and negative flags as appropriate.
 * @short M,Z,N = M+1
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformINC(Memory &memory, MOS6502 &cpu, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
    const WORD address = cpu.GetAddressingModeAddress(memory, addressing, shouldCheckPageCross);

    BYTE memoryValue = cpu.ReadByte(memory, address);
    memoryValue++;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Increment Memory
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_INC_ZP(Memory &memory, MOS6502 &cpu) {
    PerformINC(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Increment Memory
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_INC_ZPX(Memory &memory, MOS6502 &cpu) {
    PerformINC(memory, cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Increment Memory
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_INC_ABS(Memory &memory, MOS6502 &cpu) {
    PerformINC(memory, cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Increment Memory
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_INC_ABSX(Memory &memory, MOS6502 &cpu) {
    PerformINC(memory, cpu, MOS6502_AddressingMode::Absolute_X, false);
}

/**
 * @brief Increment X Register
 * @addressing Implied
 * @short X,Z,N = X+1
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_INX_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.X++;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.X, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Increment Y Register
 * @addressing Implied
 * @short Y,Z,N = Y+1
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_INY_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.Y++;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.Y, MOS6502_Status_Z | MOS6502_Status_N);
}
