#pragma once
#include "I8080/I8080.h"

/**
 * @brief Load Register Immediate Implementation
 * @details The word at the memory address (immediate value) replaces the contents of the given registers.
 * @short Register = MemoryImmediate
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param targetRegister Register for storing immediate value.
 */
FORCE_INLINE void PerformLXI(Memory &memory, I8080 &cpu, WORD& targetRegister) {
    targetRegister = cpu.FetchWord(memory);
}

/**
 * @brief Load BC Register Immediate
 * @details The word at the memory address (immediate value) replaces the contents of the BC registers.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_LXI_B(Memory &memory, I8080 &cpu) {
    PerformLXI(memory, cpu, cpu.BC);
}

/**
 * @brief Load DE Register Immediate
 * @details The word at the memory address (immediate value) replaces the contents of the DE registers.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_LXI_D(Memory &memory, I8080 &cpu) {
    PerformLXI(memory, cpu, cpu.DE);
}

/**
 * @brief Load HL Register Immediate
 * @details The word at the memory address (immediate value) replaces the contents of the HL registers.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_LXI_H(Memory &memory, I8080 &cpu) {
    PerformLXI(memory, cpu, cpu.HL);
}

/**
 * @brief Load SP Register Immediate
 * @details The word at the memory address (immediate value) replaces the contents of the SP registers.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_LXI_SP(Memory &memory, I8080 &cpu) {
    PerformLXI(memory, cpu, cpu.SP);
}
