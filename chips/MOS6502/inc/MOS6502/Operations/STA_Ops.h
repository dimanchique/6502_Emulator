#pragma once
#include "ST_Ops.h"

/**
 * @brief Store Accumulator
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.A);
}

/**
 * @brief Store Accumulator
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ZPX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.A, cpu.X);
}

/**
 * @brief Store Accumulator
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.A);
}

/**
 * @brief Store Accumulator
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.A, cpu.X);
}

/**
 * @brief Store Accumulator
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.A, cpu.Y);
}

/**
 * @brief Store Accumulator
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_INDX(Memory &memory, MOS6502 &cpu) {
    const WORD targetAddress = cpu.GetIndXAddress(memory);
    cpu.WriteByte(memory, cpu.A, targetAddress);
}

/**
 * @brief Store Accumulator
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_INDY(Memory &memory, MOS6502 &cpu) {
    const WORD targetAddress = cpu.GetIndYAddress(memory, false);
    cpu.WriteByte(memory, cpu.A, targetAddress);
    cpu.cycles++; // extra cycle required
}
