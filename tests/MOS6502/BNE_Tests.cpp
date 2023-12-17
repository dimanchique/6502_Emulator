#include "MOS6502_B_Tests.h"

class MOS6502_BNEFixture : public MOS6502_BFixture {};

TEST_F(MOS6502_BNEFixture, BNE_REL_CanBranch) {
    B_REL_CanBranch(MOS6502_OpCodes::BNE_REL, MOS6502_Status_Z, false);
}

TEST_F(MOS6502_BNEFixture, BNE_REL_CannotBranch) {
    B_REL_CannotBranch(MOS6502_OpCodes::BNE_REL, MOS6502_Status_Z, true);
}

TEST_F(MOS6502_BNEFixture, BNE_REL_CanBranch_WithPageCrossing) {
    B_REL_CanBranch_WithPageCrossing(MOS6502_OpCodes::BNE_REL, MOS6502_Status_Z, false);
}
