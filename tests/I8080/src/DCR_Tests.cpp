#include "I8080_TestingSuite.h"

class I8080_DCRFixture : public I8080_TestFixture {
public:
    void DCR_CanDecrementValue(const I8080_OpCodes opcode, BYTE &targetRegister, const BYTE initialValue) {
        // given:
        mem[0x0000] = opcode;
        mem[0x0001] = STOP_OPCODE;
        targetRegister = initialValue;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(targetRegister, (BYTE)(initialValue - 1));
        CheckCyclesCount();
    }

    void DCR_CanDecrementMemory(const BYTE initialValue, const WORD memoryAddress) {
        // given:
        mem[0x0000] = DCR_M;
        mem[0x0001] = STOP_OPCODE;
        mem[memoryAddress] = initialValue;
        ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(memoryAddress, cpu.H, cpu.L);

        cyclesExpected = 10;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[memoryAddress], (BYTE)(initialValue - 1));
        CheckCyclesCount();
    }
};

TEST_F(I8080_DCRFixture, DCR_A) {
    DCR_CanDecrementValue(DCR_A, cpu.A, 0x25);
}

TEST_F(I8080_DCRFixture, DCR_A_Zero) {
    DCR_CanDecrementValue(DCR_A, cpu.A, 0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(I8080_DCRFixture, DCR_A_Signed_Parity) {
    DCR_CanDecrementValue(DCR_A, cpu.A, 0x82);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_DCRFixture, DCR_A_Auxiliary_NoParity) {
    DCR_CanDecrementValue(DCR_A, cpu.A, 0xC8); //0xC8 (0b11001000) - 1 = 0xC7 (0b11000111)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.P);
    EXPECT_TRUE(cpu.Status.AC);
}

TEST_F(I8080_DCRFixture, DCR_B) {
    DCR_CanDecrementValue(DCR_B, cpu.B, 0x25);
}

TEST_F(I8080_DCRFixture, DCR_C) {
    DCR_CanDecrementValue(DCR_C, cpu.C, 0x25);
}

TEST_F(I8080_DCRFixture, DCR_D) {
    DCR_CanDecrementValue(DCR_D, cpu.D, 0x25);
}

TEST_F(I8080_DCRFixture, DCR_E) {
    DCR_CanDecrementValue(DCR_E, cpu.E, 0x25);
}

TEST_F(I8080_DCRFixture, DCR_H) {
    DCR_CanDecrementValue(DCR_H, cpu.H, 0x25);
}

TEST_F(I8080_DCRFixture, DCR_L) {
    DCR_CanDecrementValue(DCR_L, cpu.L, 0x25);
}

TEST_F(I8080_DCRFixture, DCR_M) {
    DCR_CanDecrementMemory(0x25, 0x1234);
}
