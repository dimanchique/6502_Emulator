#pragma once
#include "LD_Ops.h"

/**
 * @brief Load X Register
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_IM(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_IM(memory, cpu, cpu.X);
}

/**
 * @brief Load X Register
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP(memory, cpu, cpu.X);
}

/**
 * @brief Load X Register
 * @addressing Zero Page,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_ZPY(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP_Indexed(memory, cpu, cpu.X, cpu.Y);
}

/**
 * @brief Load X Register
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS(memory, cpu, cpu.X);
}

/**
 * @brief Load X Register
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS_Indexed(memory, cpu, cpu.X, cpu.Y);
}
