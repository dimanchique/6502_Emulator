#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Logical AND Implementation
 * @details A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A&M
 * @param cpu MOS6502 struct instance.
 * @param value Value to perform AND with register A.
 */
FORCE_INLINE void PerformAND(MOS6502 &cpu, const BYTE value) {
    cpu.A &= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Logical AND
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    PerformAND(cpu, value);
}

/**
 * @brief Logical AND
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    PerformAND(cpu, value);
}

/**
 * @brief Logical AND
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageIndexedValue(memory, cpu.X);
    PerformAND(cpu, value);
}

/**
 * @brief Logical AND
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    PerformAND(cpu, value);
}

/**
 * @brief Logical AND (generic)
 * @addressing Absolute Indexed
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param offsetValue Address offset value.
 */
FORCE_INLINE void MOS6502_AND_ABS_Indexed(Memory &memory, MOS6502 &cpu, BYTE offsetValue) {
    const BYTE value = cpu.GetAbsIndexedValue(memory, offsetValue);
    PerformAND(cpu, value);
}

/**
 * @brief Logical AND
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_AND_ABS_Indexed(memory, cpu, cpu.X);
}

/**
 * @brief Logical AND
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_AND_ABS_Indexed(memory, cpu, cpu.Y);
}

/**
 * @brief Logical AND
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    PerformAND(cpu, value);
}

/**
 * @brief Logical AND
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    PerformAND(cpu, value);
}
