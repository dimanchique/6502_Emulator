#include "I8080_TestingSuite.h"

class I8080_INRFixture : public I8080_TestFixture {
public:
    void INR_CanIncrementValue(const I8080_OpCodes opcode, BYTE &targetRegister, const BYTE initialValue) {
        // given:
        mem[0x0000] = opcode;
        mem[0x0001] = STOP_OPCODE;
        targetRegister = initialValue;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(targetRegister, (BYTE)(initialValue + 1));
        CheckCyclesCount();
    }

    void INR_CanIncrementMemory(const BYTE initialValue, const WORD memoryAddress) {
        // given:
        mem[0x0000] = INR_M;
        mem[0x0001] = STOP_OPCODE;
        mem[memoryAddress] = initialValue;
        ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(memoryAddress, cpu.H, cpu.L);

        cyclesExpected = 10;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[memoryAddress], (BYTE)(initialValue + 1));
        CheckCyclesCount();
    }
};

TEST_F(I8080_INRFixture, INR_A) {
    INR_CanIncrementValue(INR_A, cpu.A, 0x25);
}

TEST_F(I8080_INRFixture, INR_A_Zero) {
    INR_CanIncrementValue(INR_A, cpu.A, 0xFF);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(I8080_INRFixture, INR_A_Signed_Parity) {
    INR_CanIncrementValue(INR_A, cpu.A, 0x80);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_INRFixture, INR_A_Auxiliary_NoParity) {
    INR_CanIncrementValue(INR_A, cpu.A, 0xCF); //0xCF (0b11001111) + 1 = 0xD0 (0b11010000)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.P);
    EXPECT_TRUE(cpu.Status.AC);
}

TEST_F(I8080_INRFixture, INR_B) {
    INR_CanIncrementValue(INR_B, cpu.B, 0x25);
}

TEST_F(I8080_INRFixture, INR_C) {
    INR_CanIncrementValue(INR_C, cpu.C, 0x25);
}

TEST_F(I8080_INRFixture, INR_D) {
    INR_CanIncrementValue(INR_D, cpu.D, 0x25);
}

TEST_F(I8080_INRFixture, INR_E) {
    INR_CanIncrementValue(INR_E, cpu.E, 0x25);
}

TEST_F(I8080_INRFixture, INR_H) {
    INR_CanIncrementValue(INR_H, cpu.H, 0x25);
}

TEST_F(I8080_INRFixture, INR_L) {
    INR_CanIncrementValue(INR_L, cpu.L, 0x25);
}

TEST_F(I8080_INRFixture, INR_M) {
    INR_CanIncrementMemory(0x25, 0x1234);
}
