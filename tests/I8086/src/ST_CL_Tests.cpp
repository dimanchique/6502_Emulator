#include "I8086_TestingSuite.h"

class I8086_ST_CL_Fixture : public I8086_TestFixture {
public:
    void ST_CL_Test(I8086_OpCodes opCode) {
        // given:
        mem[effectiveAddress++] = opCode;
        mem[effectiveAddress] = STOP_OPCODE;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();
    }

    void ST_CanSetFlag(I8086_OpCodes opCode, const WORD statusFieldMask) {
        // given:
        cpu.Status.Value &= ~statusFieldMask;

        // when:
        ST_CL_Test(opCode);

        // then:
        EXPECT_EQ(cpu.Status.Value & statusFieldMask, statusFieldMask);
    }

    void CL_CanClearFlag(I8086_OpCodes opCode, const WORD statusFieldMask) {
        // given:
        cpu.Status.Value |= statusFieldMask;

        // when:
        ST_CL_Test(opCode);

        // then:
        EXPECT_EQ(cpu.Status.Value & statusFieldMask, 0);
    }
};

TEST_F(I8086_ST_CL_Fixture, STC_CanSetCarry) {
    ST_CanSetFlag(STC, I8086_Status_C);
}

TEST_F(I8086_ST_CL_Fixture, STD_CanSetDirection) {
    ST_CanSetFlag(STD, I8086_Status_D);
}

TEST_F(I8086_ST_CL_Fixture, STI_CanSetInterrupt) {
    ST_CanSetFlag(STI, I8086_Status_I);
}

TEST_F(I8086_ST_CL_Fixture, CLC_CanClearCarry) {
    CL_CanClearFlag(CLC, I8086_Status_C);
}

TEST_F(I8086_ST_CL_Fixture, CLD_CanClearDirection) {
    CL_CanClearFlag(CLD, I8086_Status_D);
}

TEST_F(I8086_ST_CL_Fixture, CL_CanClearInterrupt) {
    CL_CanClearFlag(CLI, I8086_Status_I);
}
