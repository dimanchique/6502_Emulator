#include "MOS6502_B_Tests.h"

class MOS6502_BEQFixture : public MOS6502_BFixture {};

TEST_F(MOS6502_BEQFixture, BEQ_REL_CanBranch) {
    B_REL_CanBranch(BEQ_REL, MOS6502_Status_Z, true);
}

TEST_F(MOS6502_BEQFixture, BEQ_REL_CannotBranch) {
    B_REL_CannotBranch(BEQ_REL, MOS6502_Status_Z, false);
}

TEST_F(MOS6502_BEQFixture, BEQ_REL_CanBranch_WithPageCrossing) {
    B_REL_CanBranch_WithPageCrossing(BEQ_REL, MOS6502_Status_Z, true);
}
