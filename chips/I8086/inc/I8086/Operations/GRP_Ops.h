#pragma once

#include "I8086/I8086.h"
#include "OR_Ops.h"
#include "AND_Ops.h"
#include "XOR_Ops.h"

void I8086_GRP1_Eb_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte::FromByte(modByte);
    switch (modReg.reg) {
        case 0b000: // ADD
            return;
        case 0b001: // OR
            I8086_OR_Eb_Ib(memory, cpu, modReg);
        case 0b010: // ADC
        case 0b011: // SBB
            return;
        case 0b100: // AND
            I8086_AND_Eb_Ib(memory, cpu, modReg);
        case 0b101: // SUB
            return;
        case 0b110: // XOR
            I8086_XOR_Eb_Ib(memory, cpu, modReg);
        case 0b111: // CMP
            return;
    }
}

void I8086_GRP1_Ev_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte::FromByte(modByte);
    switch (modReg.reg) {
        case 0b000: // ADD
            return;
        case 0b001: // OR
            I8086_OR_Ev_Iv(memory, cpu, modReg);
        case 0b010: // ADC
        case 0b011: // SBB
            return;
        case 0b100: // AND
            I8086_AND_Ev_Iv(memory, cpu, modReg);
        case 0b101: // SUB
            return;
        case 0b110: // XOR
            I8086_XOR_Ev_Iv(memory, cpu, modReg);
        case 0b111: // CMP
            return;
    }
}
