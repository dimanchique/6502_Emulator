#pragma once

#include "I8086/I8086.h"
#include "Adressing.h"

template<typename T>
T PerformAND(const T value1, const T value2) {
    return value1 & value2;
}

template<typename T>
void UpdateStatusAfterAND(I8086 &cpu, const T &value){
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void UpdateStatusAfterAND_Wrapper(I8086 &cpu, const InstructionResult<T> &instructionResult) {
    UpdateStatusAfterAND(cpu, instructionResult.leftOp.after);
}

template<typename T>
void I8086_EGx_EGx_AND(Memory &memory, I8086 &cpu, InstructionDirection direction) {
    I8086_EGx_EGx<BYTE>(memory, cpu, &PerformAND, &UpdateStatusAfterAND_Wrapper, direction);
}

//  Mem8 <-- Mem8 AND Reg8
void I8086_AND_Eb_Gb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_AND<BYTE>(memory, cpu, InstructionDirection::MemReg_Reg);
}

//  Mem16 <-- Mem16 AND Reg16
void I8086_AND_Ev_Gv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_AND<WORD>(memory, cpu, InstructionDirection::MemReg_Reg);
}

//  Reg8 <-- Reg8 AND Reg8
//  Reg8 <-- Reg8 AND Mem8
void I8086_AND_Gb_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_AND<BYTE>(memory, cpu, InstructionDirection::Reg_MemReg);
}

//  Reg16 <-- Reg16 AND Reg16
//  Reg16 <-- Reg16 AND Mem16
void I8086_AND_Gv_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_AND<WORD>(memory, cpu, InstructionDirection::Reg_MemReg);
}

//  AL <-- AL AND Immediate8
void I8086_AND_AL_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    BYTE value = cpu.Fetch<BYTE>(memory);
    cpu.AL = PerformAND(cpu.AL, value);
    UpdateStatusAfterAND(cpu, cpu.AL);
}

//  AX <-- AX AND Immediate16
void I8086_AND_AX_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    WORD value = cpu.Fetch<WORD>(memory);
    cpu.AX = PerformAND(cpu.AX, value);
    UpdateStatusAfterAND(cpu, cpu.AX);
}

//  Reg8 <-- Reg8 AND Immediate8
//  Mem8 <-- Mem8 AND Immediate8
void I8086_AND_Eb_Ib(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<BYTE>(memory, cpu, modRegByte, &PerformAND, &UpdateStatusAfterAND_Wrapper);
}

//  Reg16 <-- Reg16 AND Immediate16
//  Mem16 <-- Mem16 AND Immediate16
void I8086_AND_Ev_Iv(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<WORD>(memory, cpu, modRegByte, &PerformAND, &UpdateStatusAfterAND_Wrapper);
}
