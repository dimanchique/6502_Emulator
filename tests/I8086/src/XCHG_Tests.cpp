#include "I8086_ImpliedOpTests.h"

class I8086_XCHG_AX_Fixture : public I8086_ImpliedOpTests {
public:
    void TestXCHG_AX(I8086_OpCodes opCode, WORD *regPtr) {
        constexpr WORD tmp1 = 0xBABE;
        constexpr WORD tmp2 = 0xDEAD;
        cpu.AX = tmp1;
        *regPtr = tmp2;
        TestImpliedInstruction(opCode);
        EXPECT_EQ(cpu.AX, tmp2);
        EXPECT_EQ(*regPtr, tmp1);
    }
};

TEST_F(I8086_XCHG_AX_Fixture, XCHG_CX_AX) {
    TestXCHG_AX(XCHG_CX_AX, &cpu.CX);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_DX_AX) {
    TestXCHG_AX(XCHG_DX_AX, &cpu.DX);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_BX_AX) {
    TestXCHG_AX(XCHG_BX_AX, &cpu.BX);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_SP_AX) {
    TestXCHG_AX(XCHG_SP_AX, &cpu.SP);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_BP_AX) {
    TestXCHG_AX(XCHG_BP_AX, &cpu.BP);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_SI_AX) {
    TestXCHG_AX(XCHG_SI_AX, &cpu.SI);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_DI_AX) {
    TestXCHG_AX(XCHG_DI_AX, &cpu.DI);
}
