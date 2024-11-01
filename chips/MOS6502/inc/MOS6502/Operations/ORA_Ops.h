#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Logical Inclusive OR Implementation
 * @details An inclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A|M
 * @param cpu MOS6502 struct instance.
 * @param value Value to perform OR with register A.
 */
FORCE_INLINE void PerformORA(MOS6502 &cpu, const BYTE value) {
    cpu.A |= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    PerformORA(cpu, value);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    PerformORA(cpu, value);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageIndexedValue(memory, cpu.X);
    PerformORA(cpu, value);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    PerformORA(cpu, value);
}

/**
 * @brief Logical Inclusive OR (generic)
 * @addressing Absolute Indexed
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param offsetValue Address offset value.
 */
FORCE_INLINE void MOS6502_ORA_ABS_Indexed(Memory &memory, MOS6502 &cpu, BYTE offsetValue) {
    const BYTE value = cpu.GetAbsIndexedValue(memory, offsetValue);
    PerformORA(cpu, value);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ORA_ABS_Indexed(memory, cpu, cpu.X);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_ORA_ABS_Indexed(memory, cpu, cpu.Y);
}

/**
 * @brief Logical Inclusive OR
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    PerformORA(cpu, value);
}

/**
 * @brief Logical Inclusive OR
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    PerformORA(cpu, value);
}
