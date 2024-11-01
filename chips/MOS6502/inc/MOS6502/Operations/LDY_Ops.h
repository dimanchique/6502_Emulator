#pragma once
#include "LD_Ops.h"

/**
 * @brief Load Y Register
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_IM(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_IM(memory, cpu, cpu.Y);
}

/**
 * @brief Load Y Register
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP(memory, cpu, cpu.Y);
}

/**
 * @brief Load Y Register
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ZPX(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP_Indexed(memory, cpu, cpu.Y, cpu.X);
}

/**
 * @brief Load Y Register
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS(memory, cpu, cpu.Y);
}

/**
 * @brief Load Y Register
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS_Indexed(memory, cpu, cpu.Y, cpu.X);
}
