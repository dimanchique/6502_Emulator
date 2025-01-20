#include "I8086_GroupTests.h"

class I8086_INC_DEC_Fixture : public I8086_GroupFixture {};

TEST_F(I8086_INC_DEC_Fixture, INC_Eb_Addressed_Mem) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const BYTE memValue = 0b01010101;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    const BYTE refValue = 0b01010110;

    TestMemoryInstruction(memAddress, memValue, refValue, GRP4_Eb, modReg, GRP4_INC, 16);
}

TEST_F(I8086_INC_DEC_Fixture, INC_Eb_BH_Reg) {
    const BYTE reg = bBH;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.BH = 0b01010101;
    const BYTE refValue = 0b01010110;

    TestRegisterInstruction(&cpu.BH, refValue, GRP4_Eb, &reg, GRP4_INC, 16);
}

TEST_F(I8086_INC_DEC_Fixture, DEC_Eb_AH_Reg) {
    const BYTE reg = bAH;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AH = 0b10000000;
    const BYTE refValue = 0b01111111;

    TestRegisterInstruction(&cpu.AH, refValue, GRP4_Eb, &reg, GRP4_DEC, 16);
}

TEST_F(I8086_INC_DEC_Fixture, INC_Ev_AX_Reg) {
    const BYTE reg = wAX;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AX = 0b11111111'11111111;
    const WORD refValue = 0b00000000'00000000;

    TestRegisterInstruction(&cpu.AX, refValue, GRP5_Ev, &reg, GRP5_INC, 16);
}

TEST_F(I8086_INC_DEC_Fixture, DEC_Ev_DX_Reg) {
    const BYTE reg = wDX;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.DX = 0b00000000'00000000;
    const WORD refValue = 0b11111111'11111111;

    TestRegisterInstruction(&cpu.DX, refValue, GRP5_Ev, &reg, GRP5_DEC, 16);
}
