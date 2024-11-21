#pragma once
#include "I8080/I8080.h"

/**
 * @brief RETURN Implementation
 * @details The RETURN instruction pops program counter register (PC) off the stack.
 * @note This function surveys conditional RETURN instructions: C(N)C, C(N)Z, CM, CP, CPE, CPO.
 * If function called from conditional RETURN, conditionFlag is required.
 * @short PC = Stack
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param conditionFlag Condition flag value if instruction is conditional (default true).
 */
FORCE_INLINE void PerformReturn(Memory &memory, I8080 &cpu, const bool conditionFlag = true) {
    if (conditionFlag)
        cpu.PopProgramCounterFromStack(memory);
}

/**
 * @brief Absolute Return
 * @details Absolute (unconditional) RET instruction. Pops program counter register (PC) off the stack.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RET(Memory &memory, I8080 &cpu) {
    PerformReturn(memory, cpu);
}

/**
 * @brief Return if Carry
 * @details Conditional RET instruction. Performs return if carry flag is set
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RC(Memory &memory, I8080 &cpu) {
    PerformReturn(memory, cpu, cpu.Status.C);
}

/**
 * @brief Return if Not Carry
 * @details Conditional RET instruction. Performs return if carry flag is unset
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RNC(Memory &memory, I8080 &cpu) {
    PerformReturn(memory, cpu, !cpu.Status.C);
}

/**
 * @brief Return if Minus
 * @details Conditional RET instruction. Performs return if sign flag is set
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RM(Memory &memory, I8080 &cpu) {
    PerformReturn(memory, cpu, cpu.Status.S);
}

/**
 * @brief Return if Positive
 * @details Conditional RET instruction. Performs return if sign flag is unset
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RP(Memory &memory, I8080 &cpu) {
    PerformReturn(memory, cpu, !cpu.Status.S);
}

/**
 * @brief Return if Zero
 * @details Conditional RET instruction. Performs return if zero flag is set
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RZ(Memory &memory, I8080 &cpu) {
    PerformReturn(memory, cpu, cpu.Status.Z);
}

/**
 * @brief Return if Not Zero
 * @details Conditional RET instruction. Performs return if zero flag is unset
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RNZ(Memory &memory, I8080 &cpu) {
    PerformReturn(memory, cpu, !cpu.Status.Z);
}

/**
 * @brief Return if Parity Even
 * @details Conditional RET instruction. Performs return if parity flag is set
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RPE(Memory &memory, I8080 &cpu) {
    PerformReturn(memory, cpu, cpu.Status.P);
}

/**
 * @brief Return if Parity Odd
 * @details Conditional RET instruction. Performs return if parity flag is unset
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RPO(Memory &memory, I8080 &cpu) {
    PerformReturn(memory, cpu, !cpu.Status.P);
}
