#pragma once
#include "CM_Ops.h"

/**
 * @brief Compare register X
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPX_IM(Memory &memory, MOS6502 &cpu) {
    PerformCPX(memory, cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Compare register X
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPX_ZP(Memory &memory, MOS6502 &cpu) {
    PerformCPX(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Compare register X
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPX_ABS(Memory &memory, MOS6502 &cpu) {
    PerformCPX(memory, cpu, MOS6502_AddressingMode::Absolute);
}
