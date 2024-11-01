#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Compare Implementation
 * @details This instruction compares the contents of the targetRegister with memoryValue
 * and sets the zero and carry flags as appropriate.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to compare with.
 * @param memoryValue Memory value to compare.
 */
FORCE_INLINE void PerformCM(MOS6502 &cpu, const BYTE &targetRegister, const BYTE memoryValue) {
    const BYTE compareResult = targetRegister - memoryValue;
    cpu.Status.UpdateStatusByValue(compareResult, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.SetStatusBit(MOS6502_Status_C, targetRegister >= memoryValue);
}

/**
 * @brief Compare (generic)
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to compare with.
 */
FORCE_INLINE void MOS6502_CM_IM(Memory &memory, MOS6502 &cpu, const BYTE &targetRegister) {
    const BYTE value = cpu.FetchByte(memory);
    PerformCM(cpu, targetRegister, value);
}

/**
 * @brief Compare (generic)
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to compare with.
 */
FORCE_INLINE void MOS6502_CM_ZP(Memory &memory, MOS6502 &cpu, const BYTE &targetRegister) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    PerformCM(cpu, targetRegister, value);
}

/**
 * @brief Compare (generic)
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to compare with.
 */
FORCE_INLINE void MOS6502_CM_ZPX(Memory &memory, MOS6502 &cpu, const BYTE &targetRegister) {
    const BYTE value = cpu.GetZeroPageIndexedValue(memory, cpu.X);
    PerformCM(cpu, targetRegister, value);
}

/**
 * @brief Compare (generic)
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to compare with.
 */
FORCE_INLINE void MOS6502_CM_ABS(Memory &memory, MOS6502 &cpu, const BYTE &targetRegister) {
    const BYTE value = cpu.GetAbsValue(memory);
    PerformCM(cpu, targetRegister, value);
}

/**
 * @brief Compare (generic)
 * @addressing Absolute Indexed
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to compare with.
 * @param offsetValue Address offset value.
 */
FORCE_INLINE void MOS6502_CM_ABS_Indexed(Memory &memory, MOS6502 &cpu, const BYTE &targetRegister, const BYTE offsetValue) {
    const BYTE value = cpu.GetAbsIndexedValue(memory, offsetValue);
    PerformCM(cpu, targetRegister, value);
}
