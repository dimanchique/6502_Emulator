#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_D_A(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.D, cpu.A);
}

/**
 * @brief MOV from B to D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_D_B(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.D, cpu.B);
}

/**
 * @brief MOV from C to D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_D_C(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.D, cpu.C);
}

/**
 * @brief MOV from D to D
 * @details This instruction is nop-like instruction
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_D_D(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

/**
 * @brief MOV from E to D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_D_E(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.D, cpu.E);
}

/**
 * @brief MOV from H to D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_D_H(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.D, cpu.H);
}

/**
 * @brief MOV from L to D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_D_L(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.D, cpu.L);
}

/**
 * @brief MOV from Memory to D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_D_M(Memory &memory, I8080 &cpu) {
    PerformMemToRegMOV(memory, cpu, cpu.D);
}
