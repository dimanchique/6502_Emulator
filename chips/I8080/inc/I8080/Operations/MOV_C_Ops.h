#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_A(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.A);
}

/**
 * @brief MOV from B to C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_B(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.B);
}

/**
 * @brief MOV from C to C
 * @details This instruction is nop-like instruction
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_C(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

/**
 * @brief MOV from D to C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_D(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.D);
}

/**
 * @brief MOV from E to C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_E(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.E);
}

/**
 * @brief MOV from H to C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_H(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.H);
}

/**
 * @brief MOV from L to C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_L(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.L);
}

/**
 * @brief MOV from Memory to C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_M(Memory &memory, I8080 &cpu) {
    PerformMemToRegMOV(memory, cpu, cpu.C);
}
