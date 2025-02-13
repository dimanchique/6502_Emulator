#pragma once

#include "I8086/I8086.h"
#include "Adressing.h"

template<typename T>
void PerformOR(InstructionResult<T>& result) {
    result.leftOp.after = result.leftOp.before | result.rightOp.before;
    result.rightOp.after = result.rightOp.before;
}

template<typename T>
void UpdateStatusAfterOR(I8086 &cpu, const T &value){
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void UpdateStatusAfterOR_Wrapper(I8086 &cpu, const InstructionResult<T> &instructionResult) {
    UpdateStatusAfterOR(cpu, instructionResult.leftOp.after);
}

template<typename T>
void I8086_EGx_EGx_OR(Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<T>(memory, cpu, &PerformOR, &UpdateStatusAfterOR_Wrapper, InstructionDirection::MemReg_Reg, RightToLeft);
}

//  Mem8 <-- Mem8 OR Reg8
void I8086_OR_Eb_Gb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_OR<BYTE>(memory, cpu);
}

//  Mem16 <-- Mem16 OR Reg16
void I8086_OR_Ev_Gv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_OR<WORD>(memory, cpu);
}

//  Reg8 <-- Reg8 OR Reg8
//  Reg8 <-- Reg8 OR Mem8
void I8086_OR_Gb_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_OR<BYTE>(memory, cpu);
}

//  Reg16 <-- Reg16 OR Reg16
//  Reg16 <-- Reg16 OR Mem16
void I8086_OR_Gv_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_OR<WORD>(memory, cpu);
}

//  AL <-- AL OR Immediate8
//  AX <-- AX OR Immediate16
template<typename T>
void I8086_OR_Ax_Ix(T* regPtr, Memory &memory, I8086 &cpu) {
    const T value = cpu.Fetch<T>(memory);
    InstructionResult<T> instruction_result{};
    instruction_result.leftOp.before = *regPtr;
    instruction_result.rightOp.before = value;
    PerformOR(instruction_result);
    *regPtr = instruction_result.leftOp.after;
    UpdateStatusAfterOR(cpu, *regPtr);
}

//  AL <-- AL OR Immediate8
void I8086_OR_AL_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_OR_Ax_Ix(&cpu.AL, memory, cpu);
}

//  AX <-- AX OR Immediate16
void I8086_OR_AX_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_OR_Ax_Ix(&cpu.AX, memory, cpu);
}

//  Reg8/16 <-- Reg8/16 OR Immediate8/16
//  Mem8/16 <-- Mem8/16 OR Immediate8/16
template<typename T>
void I8086_OR_Ex_Ix(I8086 &cpu, Memory &memory, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(memory, cpu, modRegByte, &PerformOR, &UpdateStatusAfterOR_Wrapper);
}
