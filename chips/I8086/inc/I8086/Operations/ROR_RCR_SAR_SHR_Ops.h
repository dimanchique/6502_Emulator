#pragma once

#include "I8086/I8086.h"

namespace ROR_RCR_SAR_SHR {
    template<typename T>
    using CallbackSignature = T(I8086 &, T, const BYTE *);

    template<typename T>
    FORCE_INLINE void RXR_ByX(I8086 &cpu, Memory &memory, const ModRegByte &modReg, CallbackSignature<T> *callback, BYTE *countPtr = nullptr) {
        InstructionResult<T> instructionResult{};
        const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
        const InstructionData instructionData = cpu.GetInstructionDataNoFetch<T>(memory, opSize, InstructionDirection::MemReg_Imm, modReg);

        const T operand = instructionData.singleOp.get(cpu, memory, &instructionData.singleOp.operand);
        T opRes = callback(cpu, operand, countPtr);
        instructionData.singleOp.set(cpu, memory, &instructionData.singleOp.operand, opRes);
    }
}

template<typename T>
T PerformROR(I8086& cpu, T value, const BYTE* countPtr = nullptr) {
    BYTE highOrderBitPosition = (sizeof(value) * 8) - 1;
    BYTE count = countPtr ? *countPtr : 1;

    const BYTE highOrderBitCached = (value >> highOrderBitPosition) & 0x01;
    do {
        cpu.Status.C = value & 0x01;
        value >>= 1;
        value |= (cpu.Status.C << highOrderBitPosition);
        count--;
    } while (count > 0);

    if (!countPtr)
        cpu.Status.O = ((value >> highOrderBitPosition) & 0x01) != (highOrderBitCached);

    return value;
}

template<typename T>
T PerformRCR(I8086& cpu, T value, const BYTE* countPtr = nullptr) {
    BYTE highOrderBitPosition = (sizeof(value) * 8) - 1;
    BYTE count = countPtr ? *countPtr : 1;
    BYTE tmpCarry = 0;

    const BYTE highOrderBitCached = (value >> highOrderBitPosition) & 0x01;
    do {
        tmpCarry = cpu.Status.C;
        cpu.Status.C = value & 0x01;
        value >>= 1;
        value |= (tmpCarry << highOrderBitPosition);
        count--;
    } while (count > 0);

    if (!countPtr)
        cpu.Status.O = ((value >> highOrderBitPosition) & 0x01) != (highOrderBitCached);

    return value;
}

template<typename T>
T PerformSAR(I8086& cpu, T value, const BYTE* countPtr = nullptr) {
    BYTE highOrderBitPosition = (sizeof(value) * 8) - 1;
    BYTE count = countPtr ? *countPtr : 1;
    BYTE highOrderBit = 0;

    do {
        highOrderBit = (value >> highOrderBitPosition) & 0x01;
        cpu.Status.C = value & 0x01;
        value >>= 1;
        value |= (highOrderBit << highOrderBitPosition);
        count--;
    } while (count > 0);

    if (!countPtr)
        cpu.Status.O = 0;

    cpu.Status.UpdateStatusByValue<T>(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
    return value;
}

template<typename T>
T PerformSHR(I8086& cpu, T value, const BYTE* countPtr = nullptr) {
    BYTE highOrderBitPosition = (sizeof(value) * 8) - 1;
    BYTE count = countPtr ? *countPtr : 1;

    if (!countPtr)
        cpu.Status.O = (value >> highOrderBitPosition) & 0x01;

    do {
        cpu.Status.C = value & 0x01;
        value >>= 1;
        count--;
    } while (count > 0);

    cpu.Status.UpdateStatusByValue<T>(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
    return value;
}

template<typename T>
FORCE_INLINE void ROR_ByOne(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    ROR_RCR_SAR_SHR::RXR_ByX<T>(cpu, memory, modReg, &PerformROR);
}

template<typename T>
FORCE_INLINE void ROR_ByCL(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    ROR_RCR_SAR_SHR::RXR_ByX<T>(cpu, memory, modReg, &PerformROR, &cpu.CL);
}

template<typename T>
FORCE_INLINE void RCR_ByOne(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    ROR_RCR_SAR_SHR::RXR_ByX<T>(cpu, memory, modReg, &PerformRCR);
}

template<typename T>
FORCE_INLINE void RCR_ByCL(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    ROR_RCR_SAR_SHR::RXR_ByX<T>(cpu, memory, modReg, &PerformRCR, &cpu.CL);
}

template<typename T>
FORCE_INLINE void SAR_ByOne(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    ROR_RCR_SAR_SHR::RXR_ByX<T>(cpu, memory, modReg, &PerformSAR);
}

template<typename T>
FORCE_INLINE void SAR_ByCL(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    ROR_RCR_SAR_SHR::RXR_ByX<T>(cpu, memory, modReg, &PerformSAR, &cpu.CL);
}

template<typename T>
FORCE_INLINE void SHR_ByOne(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    ROR_RCR_SAR_SHR::RXR_ByX<T>(cpu, memory, modReg, &PerformSHR);
}

template<typename T>
FORCE_INLINE void SHR_ByCL(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    ROR_RCR_SAR_SHR::RXR_ByX<T>(cpu, memory, modReg, &PerformSHR, &cpu.CL);
}
