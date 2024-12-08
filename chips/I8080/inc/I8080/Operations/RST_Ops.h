#pragma once
#include "I8080/I8080.h"
#include "I8080/I8080_OpCodes.h"

/**
 * @brief Reset
 * @details The contents of the program counter are pushed onto the stack, providing a return address for later use by a RETURN instruction.
 * Program execution continues at memory address depending on a reset vector value.
 * @short PC = resetVector << 3
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param resetVector Reset Vector.
 */
FORCE_INLINE void PerformRST(Memory &memory, I8080 &cpu, const BYTE resetVector) {
    cpu.PushProgramCounterToStack(memory);
    cpu.PC = (WORD)(resetVector << 3);
}

/**
 * @brief Reset 0
 * @details Perform RST with a '0' reset vector
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RST_0(Memory &memory, I8080 &cpu) {
    PerformRST(memory, cpu, 0b000);
}

/**
 * @brief Reset 1
 * @details Perform RST with a '1' reset vector
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RST_1(Memory &memory, I8080 &cpu) {
    PerformRST(memory, cpu, 0b001);
}

/**
 * @brief Reset 2
 * @details Perform RST with a '2' reset vector
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RST_2(Memory &memory, I8080 &cpu) {
    PerformRST(memory, cpu, 0b010);
}

/**
 * @brief Reset 3
 * @details Perform RST with a '3' reset vector
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RST_3(Memory &memory, I8080 &cpu) {
    PerformRST(memory, cpu, 0b011);
}

/**
 * @brief Reset 4
 * @details Perform RST with a '4' reset vector
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RST_4(Memory &memory, I8080 &cpu) {
    PerformRST(memory, cpu, 0b100);
}

/**
 * @brief Reset 5
 * @details Perform RST with a '5' reset vector
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RST_5(Memory &memory, I8080 &cpu) {
    PerformRST(memory, cpu, 0b101);
}

/**
 * @brief Reset 6
 * @details Perform RST with a '6' reset vector
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RST_6(Memory &memory, I8080 &cpu) {
    PerformRST(memory, cpu, 0b110);
}

/**
 * @brief Reset 7
 * @details Perform RST with a '7' reset vector
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_RST_7(Memory &memory, I8080 &cpu) {
    PerformRST(memory, cpu, 0b111);
}
