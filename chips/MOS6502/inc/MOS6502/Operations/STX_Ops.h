#pragma once
#include "ST_Ops.h"

/**
 * @brief Store X Register
 * @addressing Zero Page
 * @details Stores the contents of the X register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STX_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.X);
}

/**
 * @brief Store X Register
 * @addressing Zero Page,Y
 * @details Stores the contents of the X register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STX_ZPY(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.X, cpu.Y);
}

/**
 * @brief Store X Register
 * @addressing Absolute
 * @details Stores the contents of the X register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STX_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.X);
}
