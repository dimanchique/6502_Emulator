#pragma once
#include "ST_Ops.h"

/**
 * @brief Store Accumulator
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ZP(Memory &memory, MOS6502 &cpu) {
    PerformSTA(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Store Accumulator
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ZPX(Memory &memory, MOS6502 &cpu) {
    PerformSTA(memory, cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Store Accumulator
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABS(Memory &memory, MOS6502 &cpu) {
    PerformSTA(memory, cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Store Accumulator
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABSX(Memory &memory, MOS6502 &cpu) {
    PerformSTA(memory, cpu, MOS6502_AddressingMode::Absolute_X, false);
}

/**
 * @brief Store Accumulator
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABSY(Memory &memory, MOS6502 &cpu) {
    PerformSTA(memory, cpu, MOS6502_AddressingMode::Absolute_Y, false);
}

/**
 * @brief Store Accumulator
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_INDX(Memory &memory, MOS6502 &cpu) {
    PerformSTA(memory, cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Store Accumulator
 * @addressing (Indirect),Y
 * @todo fix cycles count mismatch
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_INDY(Memory &memory, MOS6502 &cpu) {
    PerformSTA(memory, cpu, MOS6502_AddressingMode::Indirect_Y, false);
    cpu.cycles++; // extra cycle required
}
