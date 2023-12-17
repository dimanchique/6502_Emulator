#include "MOS6502_B_Tests.h"

class MOS6502_BCCFixture : public MOS6502_BFixture {};

TEST_F(MOS6502_BCCFixture, BCC_REL_CanBranch) {
    B_REL_CanBranch(MOS6502_OpCodes::BCC_REL, MOS6502_Status_C, false);
}

TEST_F(MOS6502_BCCFixture, BCC_REL_CannotBranch) {
    B_REL_CannotBranch(MOS6502_OpCodes::BCC_REL, MOS6502_Status_C, true);
}

TEST_F(MOS6502_BCCFixture, BCC_REL_CanBranch_WithPageCrossing) {
    B_REL_CanBranch_WithPageCrossing(MOS6502_OpCodes::BCC_REL, MOS6502_Status_C, false);
}
