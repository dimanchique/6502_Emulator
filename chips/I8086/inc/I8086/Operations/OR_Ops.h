#pragma once

#include "I8086/I8086.h"
#include "Adressing.h"

template<typename T>
T PerformOR(const T value1, const T value2) {
    return value1 | value2;
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
void I8086_EGx_EGx_OR(Memory &memory, I8086 &cpu, InstructionDirection direction) {
    I8086_EGx_EGx<T>(memory, cpu, &PerformOR, &UpdateStatusAfterOR_Wrapper, direction);
}

//  Mem8 <-- Mem8 OR Reg8
void I8086_OR_Eb_Gb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_OR<BYTE>(memory, cpu, InstructionDirection::MemReg_Reg);
}

//  Mem16 <-- Mem16 OR Reg16
void I8086_OR_Ev_Gv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_OR<WORD>(memory, cpu, InstructionDirection::MemReg_Reg);
}

//  Reg8 <-- Reg8 OR Reg8
//  Reg8 <-- Reg8 OR Mem8
void I8086_OR_Gb_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_OR<BYTE>(memory, cpu, InstructionDirection::Reg_MemReg);
}

//  Reg16 <-- Reg16 OR Reg16
//  Reg16 <-- Reg16 OR Mem16
void I8086_OR_Gv_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_OR<WORD>(memory, cpu, InstructionDirection::Reg_MemReg);
}

//  AL <-- AL OR Immediate8
void I8086_OR_AL_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const BYTE value = cpu.Fetch<BYTE>(memory);
    cpu.AL = PerformOR(cpu.AL, value);
    UpdateStatusAfterOR(cpu, cpu.AL);
}

//  AX <-- AX OR Immediate16
void I8086_OR_AX_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const WORD value = cpu.Fetch<WORD>(memory);
    cpu.AX = PerformOR(cpu.AX, value);
    UpdateStatusAfterOR(cpu, cpu.AX);
}

//  Reg8 <-- Reg8 OR Immediate8
//  Mem8 <-- Mem8 OR Immediate8
void I8086_OR_Eb_Ib(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<BYTE>(memory, cpu, modRegByte, &PerformOR, &UpdateStatusAfterOR_Wrapper);
}

//  Reg16 <-- Reg16 OR Immediate16
//  Mem16 <-- Mem16 OR Immediate16
void I8086_OR_Ev_Iv(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<WORD>(memory, cpu, modRegByte, &PerformOR, &UpdateStatusAfterOR_Wrapper);
}
