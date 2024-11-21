#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_A(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.A);
}

/**
 * @brief MOV from B to H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_B(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.B);
}

/**
 * @brief MOV from C to H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_C(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.C);
}

/**
 * @brief MOV from D to H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_D(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.D);
}

/**
 * @brief MOV from E to H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_E(Memory &memory, I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.E);
}

/**
 * @brief MOV from H to H
 * @details This instruction is nop-like instruction
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_H(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

/**
 * @brief MOV from L to H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
 void I8080_MOV_H_L(Memory &memory, I8080 &cpu) {
     PerformRegToRegMOV(cpu, cpu.H, cpu.L);
}

/**
 * @brief MOV from Memory to H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_M(Memory &memory, I8080 &cpu) {
    PerformMemToRegMOV(memory, cpu, cpu.H);
}
