#include "MOS6502_CM_Tests.h"

class MOS6502_CPXFixture : public MOS6502_CMFixture {};

TEST_F(MOS6502_CPXFixture, CPX_IM_CanCompare) {
    CM_IM_CanCompare(CPX_IM, cpu.X, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CPXFixture, CPX_IM_CanAffectZeroFlag) {
    CM_IM_CanCompare(CPX_IM, cpu.X, 0x10, 0x10);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_CPXFixture, CPX_IM_CanAffectNegativeFlag) {
    CM_IM_CanCompare(CPX_IM, cpu.X, 0x10, 0x11);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_CPXFixture, CPX_ZP_CanCompare) {
    CM_ZP_CanCompare(CPX_ZP, cpu.X, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CPXFixture, CPX_ABS_CanCompare) {
    CM_ABS_CanCompare(CPX_ABS, cpu.X, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}
