#pragma once

#include "I8086/I8086.h"
#include "OR_Ops.h"
#include "AND_Ops.h"
#include "XOR_Ops.h"
#include "ROR_RCR_SAR_SHR_Ops.h"
#include "ROL_RCL_SAL_SHL_Ops.h"

template<typename T>
using GRP_CallbackSignature = void (*)(I8086&, Memory&, const ModRegByte&);

template<typename T>
void GRP_InvalidCall(I8086&, Memory&, const ModRegByte&) {
    throw EXIT_FAILURE;
}

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

template<typename T>
FORCE_INLINE void I8086_GRP2_Ex_1(Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
            &ROL_ByOne<T>,          // 000 -> ROL
            &ROR_ByOne<T>,          // 001 -> ROR
            &RCL_ByOne<T>,          // 010 -> RCL
            &RCR_ByOne<T>,          // 011 -> RCR
            &SAL_SHL_ByOne<T>,      // 100 -> SAL/SHL
            &SHR_ByOne<T>,          // 101 -> SHR
            &GRP_InvalidCall<T>,    // 110 -> INVALID
            &SAR_ByOne<T>           // 111 -> SAR
    };

    callMap[modReg.reg](cpu, memory, modReg);
}

void I8086_GRP2_Eb_1(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP2_Ex_1<BYTE>(memory, cpu);
}

void I8086_GRP2_Ev_1(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP2_Ex_1<WORD>(memory, cpu);
}

template<typename T>
FORCE_INLINE void I8086_GRP2_Ex_CL(Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
            &ROL_ByCL<T>,           // 000 -> ROL
            &ROR_ByCL<T>,           // 001 -> ROR
            &RCL_ByCL<T>,           // 010 -> RCL
            &RCR_ByCL<T>,           // 011 -> RCR
            &SAL_SHL_ByCL<T>,       // 100 -> SAL/SHL
            &SHR_ByCL<T>,           // 101 -> SHR
            &GRP_InvalidCall<T>,    // 110 -> INVALID
            &SAR_ByCL<T>            // 111 -> SAR
    };

    callMap[modReg.reg](cpu, memory, modReg);
}

void I8086_GRP2_Eb_CL(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP2_Ex_CL<BYTE>(memory, cpu);
}

void I8086_GRP2_Ev_CL(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP2_Ex_CL<WORD>(memory, cpu);
}
