#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_B_A(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.B, cpu.A);
}

/**
 * @brief MOV from B to B
 * @details This instruction is nop-like instruction
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_B_B(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

/**
 * @brief MOV from C to B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_B_C(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.B, cpu.C);
}

/**
 * @brief MOV from D to B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_B_D(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.B, cpu.D);
}

/**
 * @brief MOV from E to B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_B_E(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.B, cpu.E);
}

/**
 * @brief MOV from H to B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_B_H(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.B, cpu.H);
}

/**
 * @brief MOV from L to B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_B_L(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.B, cpu.L);
}

/**
 * @brief MOV from Memory to B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_B_M(Memory &memory, I8080 &cpu) {
    PerformMemToRegMOV(memory, cpu, cpu.B);
}
