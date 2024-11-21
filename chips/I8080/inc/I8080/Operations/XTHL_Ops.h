#pragma once
#include "I8080/I8080.h"

/**
 * @brief Exchange Stack
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XTHL(Memory &memory, I8080 &cpu) {
    const WORD stackPointerValue = cpu.ReadWord(memory, cpu.SP);
    const WORD registerValue = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    cpu.cycles++;
    cpu.WriteWord(memory, registerValue, cpu.SP);
    ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(stackPointerValue, cpu.H, cpu.L);
    cpu.cycles++;
}
