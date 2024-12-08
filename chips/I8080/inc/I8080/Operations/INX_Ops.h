#pragma once
#include "I8080/I8080.h"

/**
 * @brief Increment Register Pair Implementation
 * @details The 16-bit number held in the specified register pair is incremented by one.
 * @short Register = Register+1
 * @note Condition bits are not affected
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to increment.
 */
FORCE_INLINE void PerformINX(I8080 &cpu, WORD &targetRegister) {
    targetRegister++;
    cpu.cycles++;
}

/**
 * @brief Increment BC
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INX_B(Memory &memory, I8080 &cpu) {
    PerformINX(cpu, cpu.BC);
}

/**
 * @brief Increment DE
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INX_D(Memory &memory, I8080 &cpu) {
    PerformINX(cpu, cpu.DE);
}

/**
 * @brief Increment HL
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INX_H(Memory &memory, I8080 &cpu) {
    PerformINX(cpu, cpu.HL);
}

/**
 * @brief Increment SP
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INX_SP(Memory &memory, I8080 &cpu) {
    PerformINX(cpu, cpu.SP);
}
