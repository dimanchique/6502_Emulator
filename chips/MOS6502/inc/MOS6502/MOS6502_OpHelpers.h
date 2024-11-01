#pragma once

#include "core/types.h"

struct MOS6502;
struct Memory;

/**
 * @brief Instruction decoder.
 * @details Looking for instruction in the instruction table using given OpCode.
 * Decode success status is true if:
 * - OpCode is not STOP_OPCODE
 *      - decoder has reached the end of program (manually inserted OpCode)
 * - Instruction is not INVALID_OP
 *      - unexpected OpCode was fetched
 * @param opcode Instruction opcode to look for.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @return Decode success.
 */
bool DecodeInstruction(BYTE opcode, Memory &memory, MOS6502 &cpu);
