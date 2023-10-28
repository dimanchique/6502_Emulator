#pragma once
#include "CPU6502.h"

/**
 * @instruction Exclusive OR (generic)
 * @description
 * An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A^M
 * @param cpu CPU6502 struct instance
 * @param value Value to perform XOR with register A
 */
inline void GenericEOR(CPU6502 &cpu, const BYTE value) {
    cpu.A ^= value;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

/**
 * @instruction Exclusive OR
 * @addressing Immediate
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_EOR_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Exclusive OR
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_EOR_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Exclusive OR
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_EOR_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Exclusive OR
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_EOR_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Exclusive OR
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_EOR_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Exclusive OR
 * @addressing Absolute,Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_EOR_ABSY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Exclusive OR
 * @addressing (Indirect,X)
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_EOR_INDX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Exclusive OR
 * @addressing (Indirect),Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_EOR_INDY(Memory &memory, CPU6502 &cpu);
