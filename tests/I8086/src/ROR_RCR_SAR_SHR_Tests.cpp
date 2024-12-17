#include "RotationInstructionsTests.h"

class I8086_ROR_RCR_SAR_SHR_Fixture : public I8086_RotateFixture {};

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, ROR_1_BX_Addressed_Mem) {
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
    const BYTE refValue = 0b10101010;

    RotateMemory(memAddress, memValue, refValue, I8086_OpCodes::GRP2_Eb_1, modReg, 0b001);
    EXPECT_EQ(cpu.Status.C, 1);
    EXPECT_EQ(cpu.Status.O, 1);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, ROR_1_BH_Reg) {
    const BYTE reg = bBH;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.BH = 0b01010101;
    const BYTE refValue = 0b10101010;

    RotateReg(&cpu.BH, refValue, I8086_OpCodes::GRP2_Eb_1, &reg, 0b001, 16);
    EXPECT_EQ(cpu.Status.C, 1);
    EXPECT_EQ(cpu.Status.O, 1);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, ROR_1_AH_Reg) {
    const BYTE reg = bAH;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AH = 0b10000000;
    const BYTE refValue = 0b01000000;

    RotateReg(&cpu.AH, refValue, I8086_OpCodes::GRP2_Eb_1, &reg, 0b001, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 1);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, ROR_CL_AX_Reg) {
    const BYTE reg = wAX;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AX = 0b00000000'00000001;
    cpu.CL = 0x10;
    const WORD refValue = 0b00000000'00000001;

    RotateReg(&cpu.AX, refValue, I8086_OpCodes::GRP2_Ev_CL, &reg, 0b001, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, RCR_1_AL_Reg) {
    const BYTE reg = bAL;
    cpu.Status.C = 1;
    cpu.Status.O = 0;
    cpu.AL = 0b00000000;
    const BYTE refValue = 0b10000000;

    RotateReg(&cpu.AL, refValue, I8086_OpCodes::GRP2_Eb_1, &reg, 0b011, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 1);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, RCR_1_BH_Reg) {
    const BYTE reg = bBH;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.BH = 0b00101010;
    const BYTE refValue = 0b00010101;

    RotateReg(&cpu.BH, refValue, I8086_OpCodes::GRP2_Eb_1, &reg, 0b011, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, RCR_CL_DX_Reg) {
    const BYTE reg = wDX;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.DX = 0b00101010;
    cpu.CL = 0x10;
    const WORD refValue = 0b01010100;

    RotateReg(&cpu.DX, refValue, I8086_OpCodes::GRP2_Ev_CL, &reg, 0b011, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, SHR_1_BL_Reg) {
    const BYTE reg = bBL;
    cpu.Status.C = 1;
    cpu.Status.O = 0;
    cpu.BL = 0b00000001;
    const BYTE refValue = 0b00000000;

    RotateReg(&cpu.BL, refValue, I8086_OpCodes::GRP2_Eb_1, &reg, 0b101, 16);
    EXPECT_EQ(cpu.Status.C, 1);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, SHR_1_CL_Reg) {
    const BYTE reg = bCL;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.CL = 0b00101010;
    const BYTE refValue = 0b00010101;

    RotateReg(&cpu.CL, refValue, I8086_OpCodes::GRP2_Eb_1, &reg, 0b101, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, SHR_CL_AX_Reg) {
    const BYTE reg = wAX;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AX = 0b00000000'00101010;
    cpu.CL = 0x08;
    const WORD refValue = 0b00000000'00000000;

    RotateReg(&cpu.AX, refValue, I8086_OpCodes::GRP2_Ev_CL, &reg, 0b101, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, SAR_1_BL_Reg) {
    const BYTE reg = bBL;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.BL = 0b00000001;
    const BYTE refValue = 0b00000000;

    RotateReg(&cpu.BL, refValue, I8086_OpCodes::GRP2_Eb_1, &reg, 0b111, 16);
    EXPECT_EQ(cpu.Status.C, 1);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, SAR_1_CL_Reg) {
    const BYTE reg = bCL;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.CL = 0b00101010;
    const BYTE refValue = 0b00010101;

    RotateReg(&cpu.CL, refValue, I8086_OpCodes::GRP2_Eb_1, &reg, 0b111, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROR_RCR_SAR_SHR_Fixture, SAR_CL_AX_Reg) {
    const BYTE reg = wAX;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AX = 0b00000000'00101010;
    cpu.CL = 0x08;
    const WORD refValue = 0b00000000'00000000;

    RotateReg(&cpu.AX, refValue, I8086_OpCodes::GRP2_Ev_CL, &reg, 0b111, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}
