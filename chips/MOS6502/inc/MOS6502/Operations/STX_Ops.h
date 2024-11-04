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
    PerformSTX(memory, cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Store X Register
 * @addressing Zero Page,Y
 * @details Stores the contents of the X register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STX_ZPY(Memory &memory, MOS6502 &cpu) {
    PerformSTX(memory, cpu, MOS6502_AddressingMode::ZeroPage_Y);
}

/**
 * @brief Store X Register
 * @addressing Absolute
 * @details Stores the contents of the X register into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STX_ABS(Memory &memory, MOS6502 &cpu) {
    PerformSTX(memory, cpu, MOS6502_AddressingMode::Absolute);
}
