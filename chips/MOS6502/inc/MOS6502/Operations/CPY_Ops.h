#pragma once
#include "CM_Ops.h"

/**
 * @brief Compare register Y
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPY_IM(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_IM(memory, cpu, cpu.Y);
}

/**
 * @brief Compare register Y
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPY_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_ZP(memory, cpu, cpu.Y);
}

/**
 * @brief Compare register Y
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPY_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_ABS(memory, cpu, cpu.Y);
}
