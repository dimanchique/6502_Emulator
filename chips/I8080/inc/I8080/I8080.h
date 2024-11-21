#pragma once

#include "I8080_Status.h"
#include "I8080_OpCodes.h"
#include "core/macro.h"
#include "base/compute.h"
#include "base/memory.h"
#include "function_library/content_manipulation.h"

#define STOP_OPCODE I8080_OpCodes::HLT /**< HALT instruction opcode used to stop execution of finite programs */

/**
 * @class I8080
 * @brief I8080 CPU implementation
 * @details I8080 (Launch: 1974) is an 8-bit microprocessor with 78 supported instructions.
 * Registers:
 * - Program Counter register (PC)
 * - Stack Pointer register (SP)
 * - Accumulator register (A)
 * - BC paired register
 * - DE paired register
 * - HL paired register
 * - Status register
 * Max CPU clock rate 2-4 MHz. Data width: 8 bits. Address width: 16 bits
 */
class I8080 final: public Compute{
public:

    WORD PC;                                /**< Program Counter */
    WORD SP;                                /**< Stack Pointer */
    BYTE A;                                 /**< Accumulator */
    I8080_Status Status;                    /**< Status Register */
    DECLARE_PAIRED_REG(BYTE, WORD, B, C);   /**< Paired BC Register */
    DECLARE_PAIRED_REG(BYTE, WORD, D, E);   /**< Paired DE Register */
    DECLARE_PAIRED_REG(BYTE, WORD, H, L);   /**< Paired HL Register */

    void Reset(Memory &memory) noexcept override;

    U32 Run(Memory &memory) override;

    /**
     * @brief Fetch byte from memory address PC points to.
     * @note Increments PC. Increments cycles count by 3.
     * @param memory Memory struct instance.
     * @return Fetched byte.
     */
    FORCE_INLINE BYTE FetchByte(const Memory &memory) {
        const BYTE Data = memory[PC++];
        cycles += 3;
        return Data;
    }

    /**
     * @brief Fetch word from memory address PC points to.
     * @note Increments PC by 2. Increments cycles count by 6.
     * @attention I8080 is little-endian system.
     * 16-bit word value has memory layout [LOW][HIGH].
     * Additional 8-bit shift is needed.
     * @param memory Memory struct instance.
     * @return Fetched word.
     */
    FORCE_INLINE WORD FetchWord(const Memory &memory) {
        const BYTE Lo = FetchByte(memory);
        const BYTE Hi = FetchByte(memory);
        return Hi | (Lo << 8);
    }

    /**
     * @brief Read byte from memory.
     * @note Increments cycles count by 3.
     * @param memory Memory struct instance.
     * @param address Address to read from.
     * @return Read byte.
     */
    FORCE_INLINE BYTE ReadByte(const Memory &memory, const WORD address) {
        const BYTE Data = memory[address];
        cycles += 3;
        return Data;
    }

    /**
     * @brief Read word from memory.
     * @note Increments cycles count by 6.
     * @attention I8080 is little-endian system.
     * 16-bit word value has memory layout [LOW][HIGH].
     * Additional 8-bit shift is needed.
     * @param memory Memory struct instance.
     * @param address Address to read from.
     * @return Fetched word.
     */
    FORCE_INLINE WORD ReadWord(const Memory &memory, const WORD address) {
        const BYTE Lo = ReadByte(memory, address);
        const BYTE Hi = ReadByte(memory, address + 1);
        return Lo | (Hi << 8);
    }

    /**
     * @brief Write a byte to memory.
     * @note Increments cycles count by 3.
     * @param memory Memory struct instance.
     * @param value Value to write.
     * @param address Address to write to.
     */
    FORCE_INLINE void WriteByte(Memory &memory, const BYTE value, const WORD address) {
        memory[address] = value;
        cycles += 3;
    }

    /**
     * @brief Write a word to memory.
     * @note Increments cycles count by 6.
     * @attention I8080 is little-endian system.
     * 16-bit word value has memory layout [LOW][HIGH].
     * Additional 8-bit shift is needed.
     * @param memory Memory struct instance.
     * @param value Value to write.
     * @param address Address to write to.
     */
    FORCE_INLINE void WriteWord(Memory &memory, const WORD value, const WORD address) {
        WriteByte(memory, value & 0xFF, address);
        WriteByte(memory, (value >> 8), address + 1);
    }

    /**
     * @brief Push two bytes of data to stack.
     * @note Increments cycles count by 7. Decrements the Stack Pointer by 2.
     * @param memory Memory struct instance.
     * @param lsb Low byte to push.
     * @param msb High byte to push.
     */
    FORCE_INLINE void PushDataToStack(Memory &memory, const BYTE &lsb, const BYTE &msb) {
        WriteByte(memory, lsb, --SP);
        WriteByte(memory, msb, --SP);
        cycles++;
    }

    /**
     * @brief Push Program Counter (PC) register value to stack.
     * @note Increments cycles count by 7. Decrements the Stack Pointer by 2.
     * @param memory Memory struct instance.
     */
    FORCE_INLINE void PushProgramCounterToStack(Memory &memory) {
        PushDataToStack(memory, (PC >> 8) & 0xFF, PC & 0xFF);
    }

    /**
     * @brief Pop Program Counter (PC) register value from stack.
     * @details Sets new value of PC register.
     * @note Increments cycles count by 3. Increments the Stack Pointer by 2.
     * @param memory Memory struct instance.
     */
    FORCE_INLINE void PopProgramCounterFromStack(Memory &memory) {
        PC = ReadWord(memory, SP);
        SP += 2;
    }


    /**
     * @brief Pop two bytes of data from stack.
     * @note Increments cycles count by 6. Increments the Stack Pointer by 2.
     * @param memory Memory struct instance.
     * @param lsb Low byte ref to write-back to.
     * @param msb High byte ref to write-back to.
     */
    FORCE_INLINE void PopDataFromStack(Memory &memory, BYTE* lsb, BYTE* msb) {
        *msb = ReadByte(memory, SP++);
        *lsb = ReadByte(memory, SP++);
    }
};
