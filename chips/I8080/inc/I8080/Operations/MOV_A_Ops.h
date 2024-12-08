#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to A
 * @details This instruction is nop-like instruction
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_A(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

/**
 * @brief MOV from B to A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_B(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.B);
}

/**
 * @brief MOV from C to A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_C(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.C);
}

/**
 * @brief MOV from D to A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_D(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.D);
}

/**
 * @brief MOV from E to A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_E(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.E);
}

/**
 * @brief MOV from H to A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_H(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.H);
}

/**
 * @brief MOV from L to A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_L(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.L);
}

/**
 * @brief MOV from Memory to A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_M(Memory &memory, I8080 &cpu) {
    PerformMemToRegMOV(memory, cpu, cpu.A);
}
