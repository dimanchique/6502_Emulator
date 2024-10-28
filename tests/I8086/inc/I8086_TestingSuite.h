#pragma once

#include <gtest/gtest.h>
#include "I8086/I8086_OpCodes.h"
#include "ModRegConstructor.h"
#include "I8086/I8086.h"
#include "base/memory.h"

class I8086_TestFixture : public testing::Test {
public:
    Memory mem{1024};
    I8086 cpu{};

    U32 cyclesPassed;
    U32 cyclesExpected;

    void SetUp() override {
        cpu.Reset(mem);
    }

    void TearDown() override {
        std::printf("Cycles passed %d expected %d\n", cyclesPassed, cyclesExpected);
    }

    void CheckCyclesCount() const noexcept {
        EXPECT_EQ(cyclesPassed, cyclesExpected);
    }

    void CheckStatus(const I8086_Status &targetStatus) const {
        EXPECT_EQ(cpu.Status.C, targetStatus.C);
        EXPECT_EQ(cpu.Status.Z, targetStatus.Z);
        EXPECT_EQ(cpu.Status.P, targetStatus.P);
        EXPECT_EQ(cpu.Status.S, targetStatus.S);
    }
};
