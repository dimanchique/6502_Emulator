#pragma once

#include "I8086/I8086.h"

FORCE_INLINE void PUSH_Reg(I8086& cpu, Memory &memory, const BYTE regIdx) {
    assert(regIdx <= 7);
    cpu.PushDataToStack(memory, *cpu.GetRegWordPtr(regIdx));
}

FORCE_INLINE void POP_Reg(I8086& cpu, Memory &memory, const BYTE regIdx) {
    assert(regIdx <= 7);
    *cpu.GetRegWordPtr(regIdx) = cpu.PopDataFromStack(memory);
}

void I8086_PUSH_Reg(BYTE OpCode, Memory &memory, I8086 &cpu) {
    PUSH_Reg(cpu, memory, OpCode - PUSH_AX);
}

void I8086_PUSH_AX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, memory, cpu);
}

void I8086_PUSH_CX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, memory, cpu);
}

void I8086_PUSH_DX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, memory, cpu);
}

void I8086_PUSH_BX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, memory, cpu);
}

void I8086_PUSH_SP(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, memory, cpu);
}

void I8086_PUSH_BP(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, memory, cpu);
}

void I8086_PUSH_SI(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, memory, cpu);
}

void I8086_PUSH_DI(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, memory, cpu);
}

void I8086_POP_Reg(BYTE OpCode, Memory &memory, I8086 &cpu) {
    POP_Reg(cpu, memory, OpCode - POP_AX);
}

void I8086_POP_AX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_POP_Reg(OpCode, memory, cpu);
}

void I8086_POP_CX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_POP_Reg(OpCode, memory, cpu);
}

void I8086_POP_DX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_POP_Reg(OpCode, memory, cpu);
}

void I8086_POP_BX(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_POP_Reg(OpCode, memory, cpu);
}

void I8086_POP_SP(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_POP_Reg(OpCode, memory, cpu);
}

void I8086_POP_BP(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_POP_Reg(OpCode, memory, cpu);
}

void I8086_POP_SI(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_POP_Reg(OpCode, memory, cpu);
}

void I8086_POP_DI(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_POP_Reg(OpCode, memory, cpu);
}
