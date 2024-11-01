#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Exclusive OR Implementation
 * @details An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A^M
 * @param cpu MOS6502 struct instance.
 * @param value Value to perform XOR with register A.
 */
FORCE_INLINE void PerformEOR(MOS6502 &cpu, const BYTE value) {
    cpu.A ^= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Exclusive OR
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    PerformEOR(cpu, value);
}

/**
 * @brief Exclusive OR
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    PerformEOR(cpu, value);
}

/**
 * @brief Exclusive OR
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageIndexedValue(memory, cpu.X);
    PerformEOR(cpu, value);
}

/**
 * @brief Exclusive OR
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    PerformEOR(cpu, value);
}

/**
 * @brief Exclusive OR (generic)
 * @addressing Absolute Indexed
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param offsetValue Address offset value.
 */
FORCE_INLINE void MOS6502_EOR_ABS_Indexed(Memory &memory, MOS6502 &cpu, BYTE offsetValue) {
    const BYTE value = cpu.GetAbsIndexedValue(memory, offsetValue);
    PerformEOR(cpu, value);
}

/**
 * @brief Exclusive OR
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_EOR_ABS_Indexed(memory, cpu, cpu.X);
}

/**
 * @brief Exclusive OR
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_EOR_ABS_Indexed(memory, cpu, cpu.Y);
}

/**
 * @brief Exclusive OR
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    PerformEOR(cpu, value);
}

/**
 * @brief Exclusive OR
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory, false);
    PerformEOR(cpu, value);
}
