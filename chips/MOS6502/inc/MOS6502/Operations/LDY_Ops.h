#pragma once
#include "LD_Ops.h"

/**
 * @brief Load Y Register
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_IM(Memory &memory, MOS6502 &cpu) {
    PerformLDY(memory, cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Load Y Register
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ZP(Memory &memory, MOS6502 &cpu) {
    PerformLDY(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Load Y Register
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ZPX(Memory &memory, MOS6502 &cpu) {
    PerformLDY(memory, cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Load Y Register
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ABS(Memory &memory, MOS6502 &cpu) {
    PerformLDY(memory, cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Load Y Register
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ABSX(Memory &memory, MOS6502 &cpu) {
    PerformLDY(memory, cpu, MOS6502_AddressingMode::Absolute_X);
}
