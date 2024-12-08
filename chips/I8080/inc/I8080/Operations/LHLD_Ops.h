#pragma once
#include "I8080/I8080.h"

/**
 * @brief Load H And L Direct
 * @details The byte at the memory address (immediate value) replaces the contents of the H and L registers.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_LHLD(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord(memory);
    const WORD memoryValue = cpu.ReadWord(memory, memoryAddress);
    cpu.L = memoryValue & 0xFF;
    cpu.H = (memoryValue >> 8) & 0xFF;
}
