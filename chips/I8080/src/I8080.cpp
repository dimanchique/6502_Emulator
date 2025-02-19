#include "I8080/I8080.h"
#include "I8080/I8080_OpHelpers.h"

void I8080::Reset(Memory &memory) noexcept {
    PC = 0x0000;
    SP = 0xFFFF;
    Status.Value = 0;

    // Accumulator and general-purpose registers are not defined after reset and may contain arbitrary values.
    cycles = 0;

    memory.Reset();
}

U32 I8080::Run(Memory &memory) {
    bool decodeSuccess;

    do {
        const BYTE opCode = FetchByte(memory);
        decodeSuccess = DecodeInstruction(opCode, memory, *this);
    } while (decodeSuccess);

    cycles -= 3;    // revert false fetch cycles
    PC--;           // revert extra PC increment for last instruction fetching
    return cycles;
}
