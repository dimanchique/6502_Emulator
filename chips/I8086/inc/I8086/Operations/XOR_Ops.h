#pragma once

#include "I8086/I8086.h"
#include "Adressing.h"

template<typename T>
T PerformXOR(const T value1, const T value2) {
    return value1 ^ value2;
}

template<typename T>
void UpdateStatusAfterXOR(I8086 &cpu, const T &value){
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void UpdateStatusAfterXOR_Wrapper(I8086 &cpu, const InstructionResult<T> &instructionResult) {
    UpdateStatusAfterXOR(cpu, instructionResult.leftOp.after);
}

template<typename T>
void I8086_EGx_EGx_XOR(Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<T>(memory, cpu, &PerformXOR, &UpdateStatusAfterXOR_Wrapper, InstructionDirection::MemReg_Reg);
}

//  Mem8 <-- Mem8 XOR Reg8
void I8086_XOR_Eb_Gb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_XOR<BYTE>(memory, cpu);
}

//  Mem16 <-- Mem16 XOR Reg16
void I8086_XOR_Ev_Gv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_XOR<WORD>(memory, cpu);
}

//  Reg8 <-- Reg8 XOR Reg8
//  Reg8 <-- Reg8 XOR Mem8
void I8086_XOR_Gb_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_XOR<BYTE>(memory, cpu);
}

//  Reg16 <-- Reg16 XOR Reg16
//  Reg16 <-- Reg16 XOR Mem16
void I8086_XOR_Gv_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_XOR<WORD>(memory, cpu);
}

//  AL <-- AL XOR Immediate8
//  AX <-- AX XOR Immediate16
template<typename T>
void I8086_XOR_Ax_Ix(T* regPtr, Memory &memory, I8086 &cpu) {
    const T value = cpu.Fetch<T>(memory);
    *regPtr = PerformXOR(*regPtr, value);
    UpdateStatusAfterXOR(cpu, *regPtr);
}

//  AL <-- AL XOR Immediate8
void I8086_XOR_AL_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_XOR_Ax_Ix(&cpu.AL, memory, cpu);
}

//  AX <-- AX XOR Immediate16
void I8086_XOR_AX_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_XOR_Ax_Ix(&cpu.AX, memory, cpu);
}

//  Reg8/16 <-- Reg8/16 XOR Immediate8/16
//  Mem8/16 <-- Mem8/16 XOR Immediate8/16
template<typename T>
void I8086_XOR_Ex_Ix(I8086 &cpu, Memory &memory, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(memory, cpu, modRegByte, &PerformXOR, &UpdateStatusAfterXOR_Wrapper);
}
