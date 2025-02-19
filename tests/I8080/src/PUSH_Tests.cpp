#include "I8080_TestingSuite.h"

class I8080_PUSHFixture : public I8080_TestFixture {
public:
    void PUSH_CanPush(const I8080_OpCodes opcode, const BYTE lsb, const BYTE msb) {
        // given:
        mem[0x0000] = opcode;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 11;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[cpu.SP], msb);
        EXPECT_EQ(mem[cpu.SP + 1], lsb);
        CheckCyclesCount();
    }
};

TEST_F(I8080_PUSHFixture, PUSH_CanPushB) {
    cpu.B = 0xAA;
    cpu.C = 0xBB;
    PUSH_CanPush(PUSH_B, cpu.B, cpu.C);
}

TEST_F(I8080_PUSHFixture, PUSH_CanPushD) {
    cpu.D = 0x12;
    cpu.E = 0x34;
    PUSH_CanPush(PUSH_D, cpu.D, cpu.E);
}

TEST_F(I8080_PUSHFixture, PUSH_CanPushH) {
    cpu.H = 0xDE;
    cpu.L = 0xAD;
    PUSH_CanPush(PUSH_H, cpu.H, cpu.L);
}

TEST_F(I8080_PUSHFixture, PUSH_CanPushPSW) {
    cpu.A = 0xDD;
    cpu.Status.Value = 0xEE;
    PUSH_CanPush(PUSH_PSW, cpu.A, cpu.Status.Value);
}
