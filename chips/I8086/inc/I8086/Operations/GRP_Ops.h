#pragma once

#include "I8086/I8086.h"
#include "OR_Ops.h"
#include "AND_Ops.h"
#include "XOR_Ops.h"
#include "ROR_RCR_SAR_SHR_Ops.h"
#include "ROL_RCL_SAL_SHL_Ops.h"
#include "NOT_NEG_Ops.h"
#include "INC_DEC_Ops.h"

template<typename T>
using GRP_CallbackSignature = void (*)(I8086&, Memory&, const ModRegByte&);

template<typename T>
void GRP_InvalidCall(I8086&, Memory&, const ModRegByte&) {
    throw InvalidInstruction();
}

template<typename T>
FORCE_INLINE void I8086_GRP1_Ex_Ix(Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
            &GRP_InvalidCall<T>,    // 000 -> ADD
            &I8086_OR_Ex_Ix<T>,     // 001 -> OR
            &GRP_InvalidCall<T>,    // 010 -> ADC
            &GRP_InvalidCall<T>,    // 011 -> SBB
            &I8086_AND_Ex_Ix<T>,    // 100 -> AND
            &GRP_InvalidCall<T>,    // 101 -> SUB
            &I8086_XOR_Ex_Ix<T>,    // 110 -> XOR
            &GRP_InvalidCall<T>     // 111 -> CMP
    };

    callMap[modReg.reg](cpu, memory, modReg);
}

void I8086_GRP1_Eb_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP1_Ex_Ix<BYTE>(memory, cpu);
}

void I8086_GRP1_Ev_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP1_Ex_Ix<WORD>(memory, cpu);
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

template<typename T>
FORCE_INLINE void I8086_GRP3x_Ex(Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
            &GRP_InvalidCall<T>,            // 000 -> TEST
            &GRP_InvalidCall<T>,            // 001 -> INVALID
            &I8086_NOT<T>,                  // 010 -> NOT
            &I8086_NEG<T>,                  // 011 -> NEG
            &GRP_InvalidCall<T>,            // 100 -> MUL
            &GRP_InvalidCall<T>,            // 101 -> IMUL
            &GRP_InvalidCall<T>,            // 110 -> DIV
            &GRP_InvalidCall<T>             // 111 -> IDIV
    };

    callMap[modReg.reg](cpu, memory, modReg);
}

void I8086_GRP3a_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP3x_Ex<BYTE>(memory, cpu);
}

void I8086_GRP3b_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP3x_Ex<WORD>(memory, cpu);
}

template<typename T>
FORCE_INLINE void I8086_GRP4_Ex(Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
        &INC_GRP4_Eb<T>,        // 000 -> INC
        &DEC_GRP4_Eb<T>,        // 001 -> DEC
        &GRP_InvalidCall<T>,    // 010 -> INVALID
        &GRP_InvalidCall<T>,    // 011 -> INVALID
        &GRP_InvalidCall<T>,    // 100 -> INVALID
        &GRP_InvalidCall<T>,    // 101 -> INVALID
        &GRP_InvalidCall<T>,    // 110 -> INVALID
        &GRP_InvalidCall<T>,    // 111 -> INVALID
};

    callMap[modReg.reg](cpu, memory, modReg);
}

void I8086_GRP4_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP4_Ex<BYTE>(memory, cpu);
}

template<typename T>
FORCE_INLINE void I8086_GRP5_Ex(Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
        &INC_GRP5_Ev<T>,        // 000 -> INC
        &DEC_GRP5_Ev<T>,        // 001 -> DEC
        &GRP_InvalidCall<T>,    // 010 -> CALL
        &GRP_InvalidCall<T>,    // 011 -> CALL Mp
        &GRP_InvalidCall<T>,    // 100 -> JMP
        &GRP_InvalidCall<T>,    // 101 -> JMP Mp
        &GRP_InvalidCall<T>,    // 110 -> PUSH
        &GRP_InvalidCall<T>,    // 111 -> INVALID
};

    callMap[modReg.reg](cpu, memory, modReg);
}

void I8086_GRP5_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_GRP5_Ex<WORD>(memory, cpu);
}
