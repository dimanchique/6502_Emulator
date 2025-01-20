#pragma once

#include "I8086/I8086.h"

namespace INC_DEC {
    template<typename T>
    using CallbackSignature = T(I8086&, T);

    template<typename T>
    FORCE_INLINE void INC_DEC(I8086& cpu, Memory& memory, const ModRegByte& modReg, CallbackSignature<T> *callback) {
        InstructionResult<T> instructionResult{};
        const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
        const InstructionData instructionData = cpu.GetInstructionDataNoFetch<T>(memory, opSize, InstructionDirection::MemReg_Imm, modReg);

        const T operand = instructionData.singleOp.get(cpu, memory, &instructionData.singleOp.operand);
        T opRes = callback(cpu, operand);
        instructionData.singleOp.set(cpu, memory, &instructionData.singleOp.operand, opRes);
    }
}

template<typename T>
T PerformINC(I8086& cpu, T value) {
    T cached = value;
    ++value;

    cpu.Status.UpdateStatusByValue<T>(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
    cpu.Status.O = cached > value; // 0xFFFF + 1 = 0x0000 ?
    // TODO: add Auxiliary Carry check
    return value;
}

template<typename T>
T PerformDEC(I8086& cpu, T value) {
    T cached = value;
    --value;

    cpu.Status.UpdateStatusByValue<T>(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
    cpu.Status.O = cached < value; // 0x0000 - 1 = 0xFFFF ?
    // TODO: add Auxiliary Carry check
    return value;
}

template<typename T>
void INC_GRP4_Eb(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    INC_DEC::INC_DEC<T>(cpu, memory, modReg, &PerformINC);
}

template<typename T>
void DEC_GRP4_Eb(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    INC_DEC::INC_DEC<T>(cpu, memory, modReg, &PerformDEC);
}

template<typename T>
void INC_GRP5_Ev(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    INC_DEC::INC_DEC<T>(cpu, memory, modReg, &PerformINC);
}

template<typename T>
void DEC_GRP5_Ev(I8086& cpu, Memory& memory, const ModRegByte& modReg) {
    INC_DEC::INC_DEC<T>(cpu, memory, modReg, &PerformDEC);
}
