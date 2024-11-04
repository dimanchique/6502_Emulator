#pragma once
#include "ST_Ops.h"

/**
 * @brief Store Y Register
 * @addressing Zero Page
 * @details Stores the contents of the Y register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STY_ZP(Memory &memory, MOS6502 &cpu) {
    PerformSTY(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Store Y Register
 * @addressing Zero Page,X
 * @details Stores the contents of the Y register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STY_ZPX(Memory &memory, MOS6502 &cpu) {
    PerformSTY(memory, cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Store Y Register
 * @addressing Absolute
 * @details Stores the contents of the Y register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STY_ABS(Memory &memory, MOS6502 &cpu) {
    PerformSTY(memory, cpu, MOS6502_AddressingMode::Absolute);
}
