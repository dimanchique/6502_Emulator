#pragma once
#include "CPU6502.h"

/**
 * @instruction Store (generic)
 * @description
 * Stores the contents of the targetRegister into memory.
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @param targetRegister Register to store
 */
inline void CPU6502_ST_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE TargetAddress = cpu.FetchByte(memory);
    cpu.WriteByte(memory, targetRegister, TargetAddress);
}

/**
 * @instruction Store (generic)
 * @description
 * Stores the contents of the targetRegister into memory.
 * @addressing Zero Page (generic)
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @param targetRegister Register to store
 * @param affectingRegister Address offset register
 */
inline void CPU6502_ST_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE TargetAddress = cpu.GetZeroPageAddress(memory, affectingRegister);
    cpu.WriteByte(memory, targetRegister, TargetAddress);
}

/**
 * @instruction Store (generic)
 * @description
 * Stores the contents of the targetRegister into memory.
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @param targetRegister Register to store
 */
inline void CPU6502_ST_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const WORD TargetAddress = cpu.FetchWord(memory);
    cpu.WriteByte(memory, targetRegister, TargetAddress);
}

/**
 * @instruction Store (generic)
 * @description
 * Stores the contents of the targetRegister into memory.
 * @addressing Absolute (generic)
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @param targetRegister Register to store
 * @param affectingRegister Address offset register
 */
inline void CPU6502_ST_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const WORD TargetAddress = cpu.GetAbsAddress(memory, affectingRegister);
    cpu.WriteByte(memory, targetRegister, TargetAddress);
    cpu.cycles++; // extra cycle required
}
