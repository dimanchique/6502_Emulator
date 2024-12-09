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
void I8086_EGx_EGx_XOR(Memory &memory, I8086 &cpu, InstructionDirection direction) {
    I8086_EGx_EGx<T>(memory, cpu, &PerformXOR, &UpdateStatusAfterXOR_Wrapper, direction);
}

//  Mem8 <-- Mem8 XOR Reg8
void I8086_XOR_Eb_Gb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_XOR<BYTE>(memory, cpu, InstructionDirection::MemReg_Reg);
}

//  Mem16 <-- Mem16 XOR Reg16
void I8086_XOR_Ev_Gv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_XOR<WORD>(memory, cpu, InstructionDirection::MemReg_Reg);
}

//  Reg8 <-- Reg8 XOR Reg8
//  Reg8 <-- Reg8 XOR Mem8
void I8086_XOR_Gb_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_XOR<BYTE>(memory, cpu, InstructionDirection::Reg_MemReg);
}

//  Reg16 <-- Reg16 XOR Reg16
//  Reg16 <-- Reg16 XOR Mem16
void I8086_XOR_Gv_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx_XOR<WORD>(memory, cpu, InstructionDirection::Reg_MemReg);
}

//  AL <-- AL XOR Immediate8
void I8086_XOR_AL_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const BYTE value = cpu.Fetch<BYTE>(memory);
    cpu.AL = PerformXOR(cpu.AL, value);
    UpdateStatusAfterXOR(cpu, cpu.AL);
}

//  AX <-- AX XOR Immediate16
void I8086_XOR_AX_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const WORD value = cpu.Fetch<WORD>(memory);
    cpu.AX = PerformXOR(cpu.AX, value);
    UpdateStatusAfterXOR(cpu, cpu.AX);
}

//  Reg8 <-- Reg8 XOR Immediate8
//  Mem8 <-- Mem8 XOR Immediate8
void I8086_XOR_Eb_Ib(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<BYTE>(memory, cpu, modRegByte, &PerformXOR, &UpdateStatusAfterXOR_Wrapper);
}

//  Reg16 <-- Reg16 XOR Immediate16
//  Mem16 <-- Mem16 XOR Immediate16
void I8086_XOR_Ev_Iv(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<WORD>(memory, cpu, modRegByte, &PerformXOR, &UpdateStatusAfterXOR_Wrapper);
}
