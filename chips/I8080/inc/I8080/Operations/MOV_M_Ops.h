#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_A(Memory &memory, I8080 &cpu) {
    PerformRegToMemMOV(memory, cpu, cpu.A);
}

/**
 * @brief MOV from B to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_B(Memory &memory, I8080 &cpu) {
    PerformRegToMemMOV(memory, cpu, cpu.B);
}

/**
 * @brief MOV from C to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_C(Memory &memory, I8080 &cpu) {
    PerformRegToMemMOV(memory, cpu, cpu.C);
}

/**
 * @brief MOV from D to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_D(Memory &memory, I8080 &cpu) {
    PerformRegToMemMOV(memory, cpu, cpu.D);
}

/**
 * @brief MOV from E to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_E(Memory &memory, I8080 &cpu) {
    PerformRegToMemMOV(memory, cpu, cpu.E);
}

/**
 * @brief MOV from H to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_H(Memory &memory, I8080 &cpu) {
    PerformRegToMemMOV(memory, cpu, cpu.H);
}

/**
 * @brief MOV from L to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_L(Memory &memory, I8080 &cpu) {
    PerformRegToMemMOV(memory, cpu, cpu.L);
}
