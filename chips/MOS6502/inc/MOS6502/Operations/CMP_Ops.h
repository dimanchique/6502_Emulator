#pragma once
#include "CM_Ops.h"

/**
 * @brief Compare Accumulator
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_IM(Memory &memory, MOS6502 &cpu) {
    PerformCMP(memory, cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Compare Accumulator
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ZP(Memory &memory, MOS6502 &cpu) {
    PerformCMP(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Compare Accumulator
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ZPX(Memory &memory, MOS6502 &cpu) {
    PerformCMP(memory, cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Compare Accumulator
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ABS(Memory &memory, MOS6502 &cpu) {
    PerformCMP(memory, cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Compare Accumulator
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ABSX(Memory &memory, MOS6502 &cpu) {
    PerformCMP(memory, cpu, MOS6502_AddressingMode::Absolute_X);
}

/**
 * @brief Compare Accumulator
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ABSY(Memory &memory, MOS6502 &cpu) {
    PerformCMP(memory, cpu, MOS6502_AddressingMode::Absolute_Y);
}

/**
 * @brief Compare Accumulator
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_INDX(Memory &memory, MOS6502 &cpu) {
    PerformCMP(memory, cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Compare Accumulator
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_INDY(Memory &memory, MOS6502 &cpu) {
    PerformCMP(memory, cpu, MOS6502_AddressingMode::Indirect_Y);
}
