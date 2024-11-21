#pragma once
#include "I8080/I8080.h"

/**
 * @brief Load Accumulator Implementation
 * @details The contents of the memory location replace the contents of the Accumulator.
 * @short A = Memory value
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param memoryAddress Given memory location.
 */
FORCE_INLINE void PerformLDA(Memory &memory, I8080 &cpu, const WORD memoryAddress) {
    const BYTE memoryValue = cpu.ReadByte(memory, memoryAddress);
    cpu.A = memoryValue;
}

/**
 * @brief Load Accumulator Direct
 * @details The byte at the memory address (immediate value) replaces the contents of the Accumulator.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_LDA(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord(memory);
    PerformLDA(memory, cpu, memoryAddress);
}

/**
 * @brief Load Accumulator addressed by BC
 * @details The byte at the memory address formed using BC register replaces the contents of the Accumulator.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_LDAX_B(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.B, cpu.C);
    PerformLDA(memory, cpu, memoryAddress);
}

/**
 * @brief Load Accumulator addressed by DE
 * @details The byte at the memory address formed using DE register replaces the contents of the Accumulator.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_LDAX_D(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.D, cpu.E);
    PerformLDA(memory, cpu, memoryAddress);
}
