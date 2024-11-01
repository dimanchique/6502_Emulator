#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Add with Carry Implementation
 * @details This instruction adds the contents of a memory location to the accumulator together with the carry bit.
 * If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
 * @short A,Z,C,N = A+M+C
 * @param cpu MOS6502 struct instance.
 * @param value Value to add.
 */
FORCE_INLINE void PerformADC(MOS6502 &cpu, const BYTE value) {
    const bool signBitsMatch = !((cpu.A ^ value) & MOS6502_Status_N);
    const WORD addRes = cpu.A + value + cpu.Status.C;
    cpu.A = addRes;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.SetStatusBit(MOS6502_Status_C, addRes > 0xFF);
    cpu.Status.SetStatusBit(MOS6502_Status_V, signBitsMatch && ((cpu.A ^ value) & MOS6502_Status_N));
}

/**
 * @brief Add with Carry
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    PerformADC(cpu, value);
}

/**
 * @brief Add with Carry
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    PerformADC(cpu, value);
}

/**
 * @brief Add with Carry
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageIndexedValue(memory, cpu.X);
    PerformADC(cpu, value);
}

/**
 * @brief Add with Carry
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    PerformADC(cpu, value);
}

/**
 * @brief Add with Carry (generic)
 * @addressing Absolute Indexed
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param offsetValue Address offset value.
 */
FORCE_INLINE void MOS6502_ADC_ABS_Indexed(Memory &memory, MOS6502 &cpu, BYTE offsetValue) {
    const BYTE value = cpu.GetAbsIndexedValue(memory, offsetValue);
    PerformADC(cpu, value);
}

/**
 * @brief Add with Carry
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ADC_ABS_Indexed(memory, cpu, cpu.X);
}

/**
 * @brief Add with Carry
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_ADC_ABS_Indexed(memory, cpu, cpu.Y);
}

/**
 * @brief Add with Carry
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    PerformADC(cpu, value);
}

/**
 * @brief Add with Carry
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    PerformADC(cpu, value);
}
