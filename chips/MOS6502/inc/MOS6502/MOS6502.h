#pragma once

#include "core/compilers_macro.h"
#include "MOS6502_Status.h"
#include "base/compute.h"
#include "MOS6502_AddressingMode.h"

#define STOP_OPCODE 0x02 /**< One of unused MOS6502 opcodes used to stop execution of finite programs*/
#define PAGE_SIZE 0xFF /**< MOS6502 default page size */
#define IsPageCrossed(src, dst) ((src ^ dst) >= PAGE_SIZE) /**< Memory page is crossed when it bounds PAGE_SIZE */

/**
 * @class MOS6502
 * @brief MOS6502 CPU implementation
 * @details MOS6502 (Launch: 1975) is an 8-bit microprocessor with 55 supported instructions and 8 addressing modes.
 * Registers: Program Counter register (PC), Stack Pointer register (SP), Accumulator register (A), two index registers (X,Y) and Status.
 * Max CPU clock rate 1-3 MHz. Data width: 8 bits. Address width: 16 bits
 */
class MOS6502 final : public Compute {
public:

    WORD PC;                /**< Program Counter */
    BYTE SP;                /**< Stack Pointer (+ 0x100 offset) */
    BYTE A;                 /**< Accumulator */
    BYTE X;                 /**< X Register */
    BYTE Y;                 /**< Y Register */
    MOS6502_Status Status;  /**< Status Register */

    void Reset(Memory &memory) noexcept override;

    U32 Run(Memory &memory) override;

    /**
     * @brief Fetch byte from memory address PC points to.
     * @note Increments PC and cycles count.
     * @param memory Memory struct instance.
     * @return Fetched byte.
     */
    FORCE_INLINE BYTE FetchByte(const Memory &memory) {
        const BYTE Data = memory[PC++];
        cycles++;
        return Data;
    }

    /**
     * @brief Fetch word from memory address PC points to.
     * @note Increments PC by 2. Increments cycles count by 2.
     * @attention MOS6502 is little-endian system.
     * 16-bit word value has memory layout [LOW][HIGH].
     * Additional 8-bit shift is needed.
     * @param memory Memory struct instance.
     * @return Fetched word.
     */
    FORCE_INLINE WORD FetchWord(const Memory &memory) {
        const BYTE Lo = FetchByte(memory);
        const BYTE Hi = FetchByte(memory);
        return Lo | (Hi << 8);
    }

    /**
     * @brief Read byte from memory.
     * @note Increments cycles count.
     * @param memory Memory struct instance.
     * @param address Address to read from.
     * @return Read byte.
     */
    FORCE_INLINE BYTE ReadByte(const Memory &memory, const WORD address) {
        const BYTE Data = memory[address];
        cycles++;
        return Data;
    }

    /**
     * @brief Read word from memory.
     * @note Increments PC by 2. Increments cycles count by 2.
     * @attention MOS6502 is little-endian system.
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
     * @note Increments cycles count.
     * @param memory Memory struct instance.
     * @param value Value to write.
     * @param address Address to write to.
     */
    FORCE_INLINE void WriteByte(Memory &memory, const BYTE value, const WORD address) {
        memory[address] = value;
        cycles++;
    }

    /**
     * @brief Write a word to memory.
     * @note Increments cycles count by 2.
     * @attention MOS6502 is little-endian system.
     * 16-bit word value has memory layout [LOW][HIGH].
     * Additional 8-bit shift is needed.
     * @param memory Memory struct instance.
     * @param value Value to write.
     * @param address Address to write to.
     */
    FORCE_INLINE void WriteWord(Memory &memory, const WORD value, const WORD address) {
        memory[address] = value & 0xFF;
        cycles++;
        memory[address + 1] = (value >> 8);
        cycles++;
    }

    /**
     * @brief Push Program Counter (PC) register value to stack.
     * @see PushWordToStack
     * @param memory Memory struct instance.
     */
    FORCE_INLINE void PushProgramCounterToStack(Memory &memory) {
        PushWordToStack(memory, PC - 1);
    }

    /**
     * @brief Pop an address from stack.
     * @note Increments cycles count by 2. Increments the Stack Pointer by 2.
     * @see PopWordFromStack
     * @param memory Memory struct instance.
     * @return Popped address.
     */
    FORCE_INLINE WORD PopAddressFromStack(const Memory &memory) {
        return PopWordFromStack(memory) + 1;
    }

    /**
     * @brief Push Status register value to stack.
     * @note Increments cycles count by 2. Decrements the Stack Pointer.
     * @see WriteByte
     * @param memory Memory struct instance.
     */
    FORCE_INLINE void PushStatusToStack(Memory &memory) {
        WriteByte(memory, Status, StackPointerToAddress());
        SP--;
        cycles++;
    }

    /**
     * @brief Pop Status register value from the stack.
     * @note Increments cycles count by 3. Increments the Stack Pointer.
     * @see ReadByte
     * @param memory Memory struct instance.
     */
    FORCE_INLINE void PopStatusFromStack(const Memory &memory) {
        SP++;
        cycles++;
        Status = ReadByte(memory, StackPointerToAddress());
        cycles++;
    }

    /**
     * @brief Push a byte to stack.
     * @note Increments cycles count by 2. Decrements the Stack Pointer.
     * @see WriteByte
     * @param memory Memory struct instance.
     * @param value Value to push to stack.
     */
    FORCE_INLINE void PushByteToStack(Memory &memory, const BYTE value) {
        WriteByte(memory, value, StackPointerToAddress());
        SP--;
        cycles++;
    }

    /**
     * @brief Pop a byte from stack.
     * @note Increments cycles count by 3. Increments the Stack Pointer.
     * @see ReadByte
     * @param memory Memory struct instance.
     * @return Popped value.
     */
    FORCE_INLINE BYTE PopByteFromStack(const Memory &memory) {
        SP++;
        cycles++;
        const BYTE value = ReadByte(memory, StackPointerToAddress());
        cycles++;
        return value;
    }

    /**
     * @brief Push a word to stack.
     * @note Increments cycles count by 2. Decrements the Stack Pointer by 2.
     * @see WriteWord
     * @param memory Memory struct instance.
     * @param value Value to push to stack.
     */
    FORCE_INLINE void PushWordToStack(Memory &memory, const WORD value) {
        WriteWord(memory, value, StackPointerToAddress() - 1);
        SP -= 2;
    }

    /**
     * @brief Pop a word from stack.
     * @note Increments cycles count by 4. Increments the Stack Pointer by 2.
     * @see ReadWord
     * @param memory Memory struct instance.
     * @return Popped value.
     */
    FORCE_INLINE WORD PopWordFromStack(const Memory &memory) {
        const WORD value = ReadWord(memory, StackPointerToAddress() + 1);
        cycles++;
        SP += 2;
        cycles++;
        return value;
    }

    /**
     * @brief Convert Stack Pointer register to address.
     * @return Converted address.
     */
    [[nodiscard]] FORCE_INLINE WORD StackPointerToAddress() const noexcept {
        return 0x100 + SP;
    }

/** @defgroup MOS6502-Addressing MOS6502 Addressing
 *  MOS6502 Addressing Modes
 *  @{
 */

    /**
     * @brief Get address based on given addressing mode
     * @note Offset value is calculating automatically if addressing mode is indexed.
     * @param memory Memory struct instance.
     * @param addressing MOS6502 Addressing mode.
     * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
     * @return Target address.
     */
    FORCE_INLINE WORD GetAddressingModeAddress(const Memory &memory, MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
        BYTE offsetValue = 0;
        switch (addressing) {
            case MOS6502_AddressingMode::ZeroPage_X:
            case MOS6502_AddressingMode::Absolute_X:
            case MOS6502_AddressingMode::Indirect_X:
                offsetValue = X;
                break;

            case MOS6502_AddressingMode::ZeroPage_Y:
            case MOS6502_AddressingMode::Absolute_Y:
            case MOS6502_AddressingMode::Indirect_Y:
                offsetValue = Y;

            default:
                break;
        }

        switch (addressing) {
            case MOS6502_AddressingMode::Immediate:
                return  PC++;
            case MOS6502_AddressingMode::ZeroPage:
                return FetchByte(memory);
            case MOS6502_AddressingMode::ZeroPage_X:
            case MOS6502_AddressingMode::ZeroPage_Y:
                return GetZeroPageIndexedAddress(memory, offsetValue);
            case MOS6502_AddressingMode::Absolute:
                return FetchWord(memory);
            case MOS6502_AddressingMode::Absolute_X:
            case MOS6502_AddressingMode::Absolute_Y:
                return GetAbsIndexedAddress(memory, offsetValue, shouldCheckPageCross);
            case MOS6502_AddressingMode::Indirect_X:
                return GetIndXAddress(memory);
            case MOS6502_AddressingMode::Indirect_Y:
                return GetIndYAddress(memory, shouldCheckPageCross);
        }
        throw; // unexpected
    }

    /**
     * @brief Get value based on given addressing mode
     * @note Offset value is calculating automatically if addressing mode is indexed.
     * @param memory Memory struct instance.
     * @param addressing MOS6502 Addressing mode.
     * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
     * @return Memory value.
     */
    FORCE_INLINE BYTE GetAddressingModeValue(const Memory &memory, MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
        const WORD address = GetAddressingModeAddress(memory, addressing, shouldCheckPageCross);
        return ReadByte(memory, address);
    }

private:

    /**
     * @brief Get Indexed ZeroPage addressing mode address (Generic).
     * @details Fetch byte. Add offset to fetched byte to get effective address.
     * @attention Increments cycles count by 2. Increments PC.
     * @addressing Zero Page,X
     * Zero Page,Y
     * @see FetchByte
     * @param memory Memory struct instance.
     * @param offsetValue Address offset value.
     * @return Zero Page Indexed address.
     */
    FORCE_INLINE WORD GetZeroPageIndexedAddress(const Memory &memory, const BYTE offsetValue) {
        const BYTE baseAddress = FetchByte(memory);
        cycles++;
        return (BYTE)(baseAddress + offsetValue);
    }

    /**
     * @brief Get Indexed Absolute addressing mode address (Generic).
     * @note Fetch word. Add offset to fetched word to get effective address.
     * @attention Increments cycles count by 2. Increments PC by 2.
     * Extra cycles count increment if a page cross is detected.
     * Extra cycles is not applied for ASL/DEC/INC/LSR/ROR/ROL/STA.
     * @addressing Absolute,X
     * Absolute,Y
     * @see FetchWord
     * @param memory Memory struct instance.
     * @param offsetValue Address offset value.
     * @return Absolute Indexed address.
     */
    FORCE_INLINE WORD GetAbsIndexedAddress(const Memory &memory, const BYTE offsetValue, bool shouldCheckPageCross = true) {
        const WORD baseAddress = FetchWord(memory);
        const WORD effectiveAddress = baseAddress + offsetValue;

        // add extra cycle if NO page-cross check
        if (!shouldCheckPageCross || IsPageCrossed(effectiveAddress, baseAddress))
            cycles++;
        return effectiveAddress;
    }

    /**
     * @brief Get (Indirect,X) addressing mode address.
     * @details Fetch byte. Add X to the fetched value.
     * Read word using this value to get (Indirect,X) address.
     * @attention Increments cycles count by 4. Increments PC.
     * @addressing (Indirect,X)
     * @see FetchByte
     * @see ReadWord
     * @param memory Memory struct instance.
     * @return (Indirect,X) address.
     */
    FORCE_INLINE WORD GetIndXAddress(const Memory &memory) {
        const BYTE baseAddress = FetchByte(memory) + X;
        cycles++;
        return ReadWord(memory, baseAddress);
    }

    /**
     * @brief Get (Indirect),Y addressing mode address.
     * @details Fetch byte. Read word using fetched byte to get effective address.
     * Add Y to the effective address to get (Indirect),Y address.
     * @attention Increments cycles count by 3. Increments PC.
     * Extra cycles count increment if a page cross is detected.
     * Extra cycles is not applied for EOR/STA instructions
     * @addressing (Indirect),Y
     * @see FetchByte
     * @see ReadWord
     * @param memory Memory struct instance.
     * @return (Indirect),Y address.
     */
    FORCE_INLINE WORD GetIndYAddress(const Memory &memory, bool shouldCheckPageCross = true) {
        const BYTE baseAddressPtr = FetchByte(memory);
        const WORD baseAddress = ReadWord(memory, baseAddressPtr);
        const WORD effectiveAddress = baseAddress + Y;
        if (shouldCheckPageCross && IsPageCrossed(effectiveAddress, baseAddress))
            cycles++;
        return effectiveAddress;
    }

/** @} */ // end of addressing
};
