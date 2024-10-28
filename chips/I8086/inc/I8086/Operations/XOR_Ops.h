#pragma once

#include "I8086/I8086.h"
#include "Adressing.h"

template<typename T>
T GenericXOR(const T value1, const T value2) {
    return value1 ^ value2;
}

template<typename T>
FORCE_INLINE void GenericUpdateStatusAfterXOR(I8086 &cpu, const T &value){
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void UpdateStatusAfterXOR(I8086 &cpu, const InstructionResult<T> &instructionResult) {
    GenericUpdateStatusAfterXOR(cpu, instructionResult.leftOp.after);
}

//  Mem8 <-- Mem8 XOR Reg8
void I8086_XOR_Eb_Gb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<BYTE>(memory, cpu, &GenericXOR, &UpdateStatusAfterXOR, InstructionDirection::MemReg_Reg);
}

//  Mem16 <-- Mem16 XOR Reg16
void I8086_XOR_Ev_Gv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<WORD>(memory, cpu, &GenericXOR, &UpdateStatusAfterXOR, InstructionDirection::MemReg_Reg);
}

//  Reg8 <-- Reg8 XOR Reg8
//  Reg8 <-- Reg8 XOR Mem8
void I8086_XOR_Gb_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<BYTE>(memory, cpu, &GenericXOR, &UpdateStatusAfterXOR, InstructionDirection::Reg_MemReg);
}

//  Reg16 <-- Reg16 XOR Reg16
//  Reg16 <-- Reg16 XOR Mem16
void I8086_XOR_Gv_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<WORD>(memory, cpu, &GenericXOR, &UpdateStatusAfterXOR, InstructionDirection::Reg_MemReg);
}

//  AL <-- AL XOR Immediate8
void I8086_XOR_AL_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const BYTE value = cpu.Fetch<BYTE>(memory);
    cpu.AL = GenericXOR(cpu.AL, value);
    GenericUpdateStatusAfterXOR(cpu, cpu.AL);
}

//  AX <-- AX XOR Immediate16
void I8086_XOR_AX_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const WORD value = cpu.Fetch<WORD>(memory);
    cpu.AX = GenericXOR(cpu.AX, value);
    GenericUpdateStatusAfterXOR(cpu, cpu.AX);
}

//  Reg8 <-- Reg8 XOR Immediate8
//  Mem8 <-- Mem8 XOR Immediate8
void I8086_XOR_Eb_Ib(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<BYTE>(memory, cpu, modRegByte, &GenericXOR, &UpdateStatusAfterXOR);
}

//  Reg16 <-- Reg16 XOR Immediate16
//  Mem16 <-- Mem16 XOR Immediate16
void I8086_XOR_Ev_Iv(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<WORD>(memory, cpu, modRegByte, &GenericXOR, &UpdateStatusAfterXOR);
}
