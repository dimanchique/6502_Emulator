#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_E_A(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.E, cpu.A);
}

/**
 * @brief MOV from B to E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_E_B(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.E, cpu.B);
}

/**
 * @brief MOV from C to E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_E_C(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.E, cpu.C);
}

/**
 * @brief MOV from D to E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_E_D(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.E, cpu.D);
}

/**
 * @brief MOV from E to E
 * @details This instruction is nop-like instruction
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_E_E(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

/**
 * @brief MOV from H to E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_E_H(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.E, cpu.H);
}

/**
 * @brief MOV from L to E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_E_L(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.E, cpu.L);
}

/**
 * @brief MOV from Memory to E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_E_M(Memory &memory, I8080 &cpu) {
    PerformMemToRegMOV(memory, cpu, cpu.E);
}
