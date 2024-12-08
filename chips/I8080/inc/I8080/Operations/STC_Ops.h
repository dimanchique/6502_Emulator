#pragma once
#include "I8080/I8080.h"

/**
 * @brief Set Carry
 * @details Set Carry flag value
 * @short C = 1
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_STC(Memory &memory, I8080 &cpu) {
    cpu.Status.C = 1;
}
