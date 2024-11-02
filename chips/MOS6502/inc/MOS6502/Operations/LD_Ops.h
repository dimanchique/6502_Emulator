#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Load Implementation
 * @details Loads a byte of memory into the targetRegister setting the zero and negative flags as appropriate.
 * @short (A/X/Y),Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformLD(Memory &memory, MOS6502 &cpu, BYTE &targetRegister, const MOS6502_AddressingMode addressing) {
    const BYTE value = cpu.GetAddressingModeValue(memory, addressing);

    targetRegister = value;
    cpu.Status.UpdateStatusByValue(targetRegister, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Load Accumulator (generic)
 * @details Loads a byte of memory into the Accumulator setting the zero and negative flags as appropriate.
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformLDA(Memory &memory, MOS6502 &cpu, const MOS6502_AddressingMode addressing){
    PerformLD(memory, cpu, cpu.A, addressing);
}

/**
 * @brief Load X Register (generic)
 * @details Loads a byte of memory into the X Register setting the zero and negative flags as appropriate.
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformLDX(Memory &memory, MOS6502 &cpu, const MOS6502_AddressingMode addressing){
    PerformLD(memory, cpu, cpu.X, addressing);
}

/**
 * @brief Load Y Register (generic)
 * @details Loads a byte of memory into the Y Register setting the zero and negative flags as appropriate.
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformLDY(Memory &memory, MOS6502 &cpu, const MOS6502_AddressingMode addressing){
    PerformLD(memory, cpu, cpu.Y, addressing);
}
