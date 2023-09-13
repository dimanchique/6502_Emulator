#include "CPU6502_DE_Tests.h"

void CPU6502_DEFixture::DE_ZP_CanAffectValue(CPU6502_OpCodes OpCode, BYTE MemoryValue, BYTE OffsetValueRegister){
    // given:
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = 0x42;
    mem[0x42 + OffsetValueRegister] = MemoryValue;
    BYTE TargetValue = MemoryValue - 1;

    // when:
    const U32 NumCycles = OffsetValueRegister ? 6 : 5;
    cpu.Run(NumCycles, mem);

    // then:
    EXPECT_NE(mem[0x42 + OffsetValueRegister], MemoryValue);
    EXPECT_EQ(mem[0x42 + OffsetValueRegister], TargetValue);
}

void CPU6502_DEFixture::DE_ABS_CanAffectValue(CPU6502_OpCodes OpCode, BYTE MemoryValue, BYTE OffsetValueRegister){
    // given:
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = 0x00;
    mem[0xFFFE] = 0x42;
    mem[0x4200 + OffsetValueRegister] = MemoryValue;
    BYTE TargetValue = MemoryValue - 1;

    // when:
    const U32 NumCycles = OffsetValueRegister ? 7 : 6;
    cpu.Run(NumCycles, mem);

    // then:
    EXPECT_NE(mem[0x4200 + OffsetValueRegister], MemoryValue);
    EXPECT_EQ(mem[0x4200 + OffsetValueRegister], TargetValue);
}

void CPU6502_DEFixture::DE_IMPL_CanAffectValue(CPU6502_OpCodes OpCode, BYTE& TargetRegister){
    // given:
    BYTE InitialValue = TargetRegister;
    BYTE TargetValue = InitialValue - 1;
    mem[0xFFFC] = OpCode;

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_NE(TargetRegister, InitialValue);
    EXPECT_EQ(TargetRegister, TargetValue);
}
