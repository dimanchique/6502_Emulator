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
    MOS6502_ST_ZP(memory, cpu, cpu.Y);
}

/**
 * @brief Store Y Register
 * @addressing Zero Page,X
 * @details Stores the contents of the Y register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STY_ZPX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.Y, cpu.X);
}

/**
 * @brief Store Y Register
 * @addressing Absolute
 * @details Stores the contents of the Y register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STY_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.Y);
}
