#pragma once

#include "I8086/I8086.h"
#include "Adressing.h"

template<typename T>
T GenericAND(const T value1, const T value2) {
    return value1 & value2;
}

template<typename T>
FORCE_INLINE void GenericUpdateStatusAfterAND(I8086 &cpu, const T &value){
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void UpdateStatusAfterAND(I8086 &cpu, const InstructionResult<T> &instructionResult) {
    GenericUpdateStatusAfterAND(cpu, instructionResult.leftOp.after);
}

//  Mem8 <-- Mem8 AND Reg8
void I8086_AND_Eb_Gb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<BYTE>(memory, cpu, &GenericAND, &UpdateStatusAfterAND, InstructionDirection::MemReg_Reg);
}

//  Mem16 <-- Mem16 AND Reg16
void I8086_AND_Ev_Gv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<WORD>(memory, cpu, &GenericAND, &UpdateStatusAfterAND, InstructionDirection::MemReg_Reg);
}

//  Reg8 <-- Reg8 AND Reg8
//  Reg8 <-- Reg8 AND Mem8
void I8086_AND_Gb_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<BYTE>(memory, cpu, &GenericAND, &UpdateStatusAfterAND, InstructionDirection::Reg_MemReg);
}

//  Reg16 <-- Reg16 AND Reg16
//  Reg16 <-- Reg16 AND Mem16
void I8086_AND_Gv_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_EGx_EGx<WORD>(memory, cpu, &GenericAND, &UpdateStatusAfterAND, InstructionDirection::Reg_MemReg);
}

//  AL <-- AL AND Immediate8
void I8086_AND_AL_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    BYTE value = cpu.Fetch<BYTE>(memory);
    cpu.AL = GenericAND(cpu.AL, value);
    GenericUpdateStatusAfterAND(cpu, cpu.AL);
}

//  AX <-- AX AND Immediate16
void I8086_AND_AX_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    WORD value = cpu.Fetch<WORD>(memory);
    cpu.AX = GenericAND(cpu.AX, value);
    GenericUpdateStatusAfterAND(cpu, cpu.AX);
}

//  Reg8 <-- Reg8 AND Immediate8
//  Mem8 <-- Mem8 AND Immediate8
void I8086_AND_Eb_Ib(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<BYTE>(memory, cpu, modRegByte, &GenericAND, &UpdateStatusAfterAND);
}

//  Reg16 <-- Reg16 AND Immediate16
//  Mem16 <-- Mem16 AND Immediate16
void I8086_AND_Ev_Iv(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_Ex_Ix<WORD>(memory, cpu, modRegByte, &GenericAND, &UpdateStatusAfterAND);
}
