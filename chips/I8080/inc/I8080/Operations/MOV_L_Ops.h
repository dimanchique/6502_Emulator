#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_A(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.A);
}

/**
 * @brief MOV from B to L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_B(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.B);
}

/**
 * @brief MOV from C to L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_C(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.C);
}

/**
 * @brief MOV from D to L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_D(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.D);
}

/**
 * @brief MOV from E to L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_E(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.E);
}

/**
 * @brief MOV from H to L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_H(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.H);
}

/**
 * @brief MOV from L to L
 * @details This instruction is nop-like instruction
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_L(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

/**
 * @brief MOV from Memory to L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_M(Memory &memory, I8080 &cpu) {
    PerformMemToRegMOV(memory, cpu, cpu.L);
}
