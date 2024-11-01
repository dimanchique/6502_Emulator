#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Arithmetic Shift Left Implementation
 * @details This operation shifts all the bits of the accumulator or memory contents one bit left.
 * Bit 0 is set to 0 and bit 7 is placed in the carry flag.
 * The effect of this operation is to multiply the memory contents by 2 (ignoring 2's complement considerations),
 * setting the carry if the result will not fit in 8 bits.
 * @short A,Z,C,N = M*2 or M,Z,C,N = M*2
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param address Address to write back shifted value.
 */
FORCE_INLINE void PerformASL(Memory &memory, MOS6502 &cpu, const WORD address) {
    BYTE memoryValue = cpu.ReadByte(memory, address);
    const bool carry = memoryValue & (1 << 7);
    memoryValue <<= 1;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Arithmetic Shift Left Accumulator
 * @details Same as PerformASL, but with Accumulator as target.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ASL_ACC(Memory &memory, MOS6502 &cpu) {
    const bool carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Arithmetic Shift Left
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ASL_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.FetchByte(memory);
    PerformASL(memory, cpu, address);
}

/**
 * @brief Arithmetic Shift Left
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ASL_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.GetZeroPageIndexedAddress(memory, cpu.X);
    PerformASL(memory, cpu, address);
}

/**
 * @brief Arithmetic Shift Left
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ASL_ABS(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.FetchWord(memory);
    PerformASL(memory, cpu, address);
}

/**
 * @brief Arithmetic Shift Left
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ASL_ABSX(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.GetAbsIndexedAddress(memory, cpu.X, false);
    PerformASL(memory, cpu, address);
}
