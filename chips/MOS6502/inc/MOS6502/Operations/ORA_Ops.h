#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Logical Inclusive OR Implementation
 * @details An inclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A|M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformORA(Memory &memory, MOS6502 &cpu, const MOS6502_AddressingMode addressing) {
    const BYTE value = cpu.GetAddressingModeValue(memory, addressing);

    cpu.A |= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_IM(Memory &memory, MOS6502 &cpu) {
    PerformORA(memory, cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ZP(Memory &memory, MOS6502 &cpu) {
    PerformORA(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ZPX(Memory &memory, MOS6502 &cpu) {
    PerformORA(memory, cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABS(Memory &memory, MOS6502 &cpu) {
    PerformORA(memory, cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABSX(Memory &memory, MOS6502 &cpu) {
    PerformORA(memory, cpu, MOS6502_AddressingMode::Absolute_X);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABSY(Memory &memory, MOS6502 &cpu) {
    PerformORA(memory, cpu, MOS6502_AddressingMode::Absolute_Y);
}

/**
 * @brief Logical Inclusive OR
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_INDX(Memory &memory, MOS6502 &cpu) {
    PerformORA(memory, cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Logical Inclusive OR
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_INDY(Memory &memory, MOS6502 &cpu) {
    PerformORA(memory, cpu, MOS6502_AddressingMode::Indirect_Y);
}
