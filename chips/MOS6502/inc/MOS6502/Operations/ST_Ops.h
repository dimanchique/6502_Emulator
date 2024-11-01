#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Store (generic)
 * @addressing Zero Page
 * @details Stores the contents of the targetRegister into memory.
 * @short M = (A/X/Y)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to store from.
 */
FORCE_INLINE void MOS6502_ST_ZP(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const BYTE targetAddress = cpu.FetchByte(memory);
    cpu.WriteByte(memory, targetRegister, targetAddress);
}

/**
 * @brief Store (generic)
 * @addressing Zero Page Indexed
 * @details Stores the contents of the targetRegister into memory.
 * @short M = (A/X/Y)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to store from.
 * @param offsetValue Address offset value.
 */
FORCE_INLINE void MOS6502_ST_ZP(Memory &memory, MOS6502 &cpu, BYTE &targetRegister, BYTE offsetValue) {
    const BYTE targetAddress = cpu.GetZeroPageIndexedAddress(memory, offsetValue);
    cpu.WriteByte(memory, targetRegister, targetAddress);
}

/**
 * @brief Store (generic)
 * @addressing Absolute
 * @details Stores the contents of the targetRegister into memory.
 * @short M = (A/X/Y)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to store from.
 */
FORCE_INLINE void MOS6502_ST_ABS(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const WORD targetAddress = cpu.FetchWord(memory);
    cpu.WriteByte(memory, targetRegister, targetAddress);
}

/**
 * @brief Store (generic)
 * @addressing Absolute (generic)
 * @details Stores the contents of the targetRegister into memory.
 * @short M = (A/X/Y)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to store from.
 * @param offsetValue Address offset value.
 */
FORCE_INLINE void MOS6502_ST_ABS(Memory &memory, MOS6502 &cpu, BYTE &targetRegister, BYTE offsetValue) {
    const WORD targetAddress = cpu.GetAbsIndexedAddress(memory, offsetValue, false);
    cpu.WriteByte(memory, targetRegister, targetAddress);
}
