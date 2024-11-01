#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Subtract with Carry Implementation
 * @details This instruction subtracts the contents of a memory location to the accumulator
 * together with the not of the carry bit.
 * If overflow occurs the carry bit is clear, this enables multiple byte subtraction to be performed.
 * @short A,Z,C,N = A-M-(1-C)
 * @param cpu MOS6502 struct instance.
 * @param value Value to subtract.
 */
FORCE_INLINE void PerformSBC(MOS6502 &cpu, const BYTE value) {
    const bool signBitsMatch = !((cpu.A ^ value) & MOS6502_Status_N);
    const WORD subRes = cpu.A - value - (1 - cpu.Status.C);
    cpu.A = subRes;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.SetStatusBit(MOS6502_Status_C, subRes > 0xFF);
    cpu.Status.SetStatusBit(MOS6502_Status_V, signBitsMatch && ((cpu.A ^ value) & MOS6502_Status_N));
}

/**
 * @brief Subtract with Carry
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    PerformSBC(cpu, value);
}

/**
 * @brief Subtract with Carry
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu MOS6502 struct instance
 */
void MOS6502_SBC_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    PerformSBC(cpu, value);
}

/**
 * @brief Subtract with Carry
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageIndexedValue(memory, cpu.X);
    PerformSBC(cpu, value);
}

/**
 * @brief Subtract with Carry
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    PerformSBC(cpu, value);
}

/**
 * @brief Subtract with Carry
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_ABSX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsIndexedValue(memory, cpu.X);
    PerformSBC(cpu, value);
}

/**
 * @brief Subtract with Carry
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_ABSY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsIndexedValue(memory, cpu.Y);
    PerformSBC(cpu, value);
}

/**
 * @brief Subtract with Carry
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    PerformSBC(cpu, value);
}

/**
 * @brief Subtract with Carry
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    PerformSBC(cpu, value);
}
