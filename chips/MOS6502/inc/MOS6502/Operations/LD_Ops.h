#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Load Implementation
 * @details Loads a byte of memory into the targetRegister setting the zero and negative flags as appropriate.
 * @short (A/X/Y),Z,N = M
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 * @param value Value to load.
 */
FORCE_INLINE void PerformLD(MOS6502 &cpu, BYTE &targetRegister, const BYTE &value) {
    targetRegister = value;
    cpu.Status.UpdateStatusByValue(targetRegister, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Load (generic)
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 */
FORCE_INLINE void MOS6502_LD_IM(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const BYTE data = cpu.FetchByte(memory);
    PerformLD(cpu, targetRegister, data);
}

/**
 * @brief Load (generic)
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 */
FORCE_INLINE void MOS6502_LD_ZP(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const BYTE data = cpu.GetZeroPageValue(memory);
    PerformLD(cpu, targetRegister, data);
}

/**
 * @brief Load (generic)
 * @addressing Zero Page Indexed
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 * @param offsetValue Address offset value.
 */
FORCE_INLINE void MOS6502_LD_ZP_Indexed(Memory &memory, MOS6502 &cpu, BYTE &targetRegister, BYTE offsetValue) {
    const BYTE data = cpu.GetZeroPageIndexedValue(memory, offsetValue);
    PerformLD(cpu, targetRegister, data);
}

/**
 * @brief Load (generic)
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 */
FORCE_INLINE void MOS6502_LD_ABS(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const BYTE data = cpu.GetAbsValue(memory);
    PerformLD(cpu, targetRegister, data);
}

/**
 * @brief Load (generic)
 * @addressing Absolute Indexed
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 * @param offsetValue Address offset value.
 */
FORCE_INLINE void MOS6502_LD_ABS_Indexed(Memory &memory, MOS6502 &cpu, BYTE &targetRegister, BYTE offsetValue) {
    const BYTE data = cpu.GetAbsIndexedValue(memory, offsetValue);
    PerformLD(cpu, targetRegister, data);
}
