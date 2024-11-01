#pragma once
#include "LD_Ops.h"

/**
 * @brief Load Accumulator
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_IM(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_IM(memory, cpu, cpu.A);
}

/**
 * @brief Load Accumulator
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP(memory, cpu, cpu.A);
}

/**
 * @brief Load Accumulator
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ZPX(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP_Indexed(memory, cpu, cpu.A, cpu.X);
}

/**
 * @brief Load Accumulator
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS(memory, cpu, cpu.A);
}

/**
 * @brief Load Accumulator
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS_Indexed(memory, cpu, cpu.A, cpu.X);
}

/**
 * @brief Load Accumulator
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS_Indexed(memory, cpu, cpu.A, cpu.Y);
}

/**
 * @brief Load Accumulator
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE data = cpu.GetIndXAddressValue(memory);
    PerformLD(cpu, cpu.A, data);
}

/**
 * @brief Load Accumulator
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE data = cpu.GetIndYAddressValue(memory);
    PerformLD(cpu, cpu.A, data);
}
