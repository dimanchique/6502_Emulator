#include "I8086_TestingSuite.h"

class I8086_XORFixture : public I8086_TestFixture {
public:

    void XOR_CanDo_XOR_Ev_Gv(DWORD memAddress, WORD memValue, WORD refReg, ModRegByteConstructor &modReg) {
        // given:
        cpu.PC = 0x1000;
        cpu.CS = 0x1000;
        DWORD effectiveAddress = cpu.PC + (cpu.CS << 4);

        mem[memAddress] = memValue & 0xFF;
        mem[memAddress + 1] = (memValue >> 8) & 0xFF;

        modReg.size = OperandSize::WORD;
        BYTE modRegByte = modReg.MakeModByte();

        mem[effectiveAddress++] = XOR_Ev_Gv;
        mem[effectiveAddress++] = modRegByte;

        if (modReg.leftOp.memData.mode == modeDirect) {
            mem[effectiveAddress++] = memAddress & 0xFF;
            mem[effectiveAddress++] = (memAddress >> 8) & 0xFF;
        }

        if (modReg.leftOp.memData.dispSize > 0) {
            mem[effectiveAddress++] = modReg.leftOp.memData.dispValue & 0xFF;
            if (modReg.leftOp.memData.dispSize > 1)
                mem[effectiveAddress++] = (modReg.leftOp.memData.dispValue >> 8) & 0xFF;
        }

        mem[effectiveAddress++] = STOP_OPCODE;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();

        // Result of ExGx is always in memory
        WORD result = mem[memAddress];
        result |= (mem[memAddress + 1] << 8);
        EXPECT_EQ(result, refReg ^ memValue);
    }

    template<typename T>
    void XOR_CanDo_XOR_Gx_Ex(const T* leftRegPtr, const T* rightRegPtr, ModRegByteConstructor &modReg) {
        // given:
        WORD initialLeftReg = *leftRegPtr;
        WORD initialRightReg = *rightRegPtr;

        cpu.PC = 0x1000;
        cpu.CS = 0x1000;
        DWORD effectiveAddress = cpu.PC + (cpu.CS << 4);

        modReg.size = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;;
        BYTE modRegByte = modReg.MakeModByte();

        mem[effectiveAddress++] = std::is_same_v<T, BYTE> ? XOR_Gb_Eb : XOR_Gv_Ev;
        mem[effectiveAddress++] = modRegByte;

        mem[effectiveAddress++] = STOP_OPCODE;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();

        // Result of GxEx is always in register
        EXPECT_EQ(*leftRegPtr, initialLeftReg ^ initialRightReg);
    }

    void XOR_CanDo_XOR_Gv_Ev(const WORD* leftRegPtr, WordRegisters leftRegName, const WORD* rightRegPtr, WordRegisters rightRegName) {
        ModRegByteConstructor modReg;
        modReg.leftOp.archetype = OperandArchetype::Reg;
        modReg.leftOp.regData.wordReg = leftRegName;

        modReg.rightOp.archetype = OperandArchetype::Reg;
        modReg.rightOp.regData.wordReg = rightRegName;

        XOR_CanDo_XOR_Gx_Ex(leftRegPtr, rightRegPtr, modReg);
    }

    void XOR_CanDo_XOR_Gb_Eb(const BYTE* leftRegPtr, ByteRegisters leftRegName, const BYTE* rightRegPtr, ByteRegisters rightRegName) {
        ModRegByteConstructor modReg;
        modReg.leftOp.archetype = OperandArchetype::Reg;
        modReg.leftOp.regData.byteReg = leftRegName;

        modReg.rightOp.archetype = OperandArchetype::Reg;
        modReg.rightOp.regData.byteReg = rightRegName;

        XOR_CanDo_XOR_Gx_Ex(leftRegPtr, rightRegPtr, modReg);
    }

    template<typename T>
    void XOR_CanDo_XOR_AI(T initialValue, T memValue) {
        // given:
        cpu.PC = 0x1000;
        cpu.CS = 0x1000;
        DWORD effectiveAddress = cpu.PC + (cpu.CS << 4);

        if (std::is_same_v<T, BYTE>)
            cpu.AL = initialValue;
        else
            cpu.AX = initialValue;

        mem[effectiveAddress++] = std::is_same_v<T, BYTE> ? XOR_AL_Ib : XOR_AX_Iv;
        mem[effectiveAddress++] = memValue & 0xFF;
        if (!std::is_same_v<T, BYTE>)
            mem[effectiveAddress++] = (memValue >> 8) & 0xFF;
        mem[effectiveAddress] = STOP_OPCODE;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();

        EXPECT_EQ((std::is_same_v<T, BYTE> ? cpu.AL : cpu.AX), initialValue ^ memValue);
    }
};

// Mem (BX addressed) <-- AX ^ Mem (BX addressed)
TEST_F(I8086_XORFixture, XOR_Ev_Gv_BX_Addressed_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData.wordReg = wAX;

    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);

    XOR_CanDo_XOR_Ev_Gv(memAddress, memValue, cpu.AX, modReg);
}

// Mem (Direct addressed) <-- BX ^ Mem (Direct addressed)
TEST_F(I8086_XORFixture, XOR_Ev_Gv_Direct_Addressed_BX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeDirect;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData.wordReg = wBX;

    cpu.BX = 0x0060;
    cyclesExpected = 16 + 6;
    
    const WORD memValue = 0x12C;
    const DWORD memAddress = 0x1000;
    
    XOR_CanDo_XOR_Ev_Gv(memAddress, memValue, cpu.BX, modReg);
}

// Mem (BP addressed WithDisp) <-- DX ^ Mem (BP addressed WithDisp)
TEST_F(I8086_XORFixture, XOR_Ev_Gv_BP_Addressed_WithDisp_DX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 2;
    modReg.leftOp.memData.dispValue = 0x100;
    modReg.leftOp.memData.mode = modeBP;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData.wordReg = wDX;

    cpu.DX = 0x0060;
    cpu.SS = 0x2000; // BP is force-replacing by SS
    cyclesExpected = 16 + 9;
    
    const WORD memValue = 0x12C;
    const DWORD memAddress = modReg.leftOp.memData.dispValue + (cpu.SS << 4);
    
    XOR_CanDo_XOR_Ev_Gv(memAddress, memValue, cpu.DX, modReg);
}

// Mem (BX SI addressed WithDisp) <-- AX ^ Mem (BX SI addressed WithDisp)
TEST_F(I8086_XORFixture, XOR_Ev_Gv_BXSI_Addressed_WithDisp_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 1;
    modReg.leftOp.memData.dispValue = 0xAD;
    modReg.leftOp.memData.mode = modeBXpSI;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData.wordReg = wAX;

    cpu.AX = 0x0060;
    cpu.BX = 0x8000;
    cpu.SI = 0x1000;
    cpu.DS = 0x2000;
    cyclesExpected = 16 + 11;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + cpu.SI + modReg.leftOp.memData.dispValue + (cpu.DS << 4);
    
    XOR_CanDo_XOR_Ev_Gv(memAddress, memValue, cpu.AX, modReg);
}

// AX <-- AX ^ BX
TEST_F(I8086_XORFixture, XOR_Gv_Ev_AX_BX) {
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;

    XOR_CanDo_XOR_Gv_Ev(&cpu.AX, wAX, &cpu.BX, wBX);
}

// BX <-- BX ^ DI
TEST_F(I8086_XORFixture, XOR_Gv_Ev_BX_DI) {
    cpu.BX = 0x0060;
    cpu.DI = 0x009A;

    XOR_CanDo_XOR_Gv_Ev(&cpu.BX, wBX, &cpu.DI, wDI);
}

// AL <-- AL ^ BH
TEST_F(I8086_XORFixture, XOR_Gb_Eb_AL_BH) {
    cpu.AL = 0x60;
    cpu.BH = 0x9A;

    XOR_CanDo_XOR_Gb_Eb(&cpu.AL, bAL, &cpu.BH, bBH);
}

// BL <-- BL ^ CL
TEST_F(I8086_XORFixture, XOR_Gb_Eb_BL_CL) {
    cpu.BL = 0x0060;
    cpu.CL = 0x009A;

    XOR_CanDo_XOR_Gb_Eb(&cpu.BL, bBL,&cpu.CL, bCL);
}

TEST_F(I8086_XORFixture, XOR_AL_Ib_Test1) {
    XOR_CanDo_XOR_AI<BYTE>(0x11, 0x22);
}

TEST_F(I8086_XORFixture, XOR_AL_Ib_Test2) {
    XOR_CanDo_XOR_AI<BYTE>(0x10, 0x01);
}

TEST_F(I8086_XORFixture, XOR_AL_Ib_Test3) {
    XOR_CanDo_XOR_AI<BYTE>(0x00, 0x00);
}

TEST_F(I8086_XORFixture, XOR_AL_Ib_Test4) {
    XOR_CanDo_XOR_AI<BYTE>(0xFF, 0xFF);
}

TEST_F(I8086_XORFixture, XOR_AL_Ib_Test5) {
    XOR_CanDo_XOR_AI<BYTE>(0xFF, 0x00);
}

TEST_F(I8086_XORFixture, XOR_AL_Iv_Test1) {
    XOR_CanDo_XOR_AI<WORD>(0x1111, 0x2222);
}

TEST_F(I8086_XORFixture, XOR_AL_Iv_Test2) {
    XOR_CanDo_XOR_AI<WORD>(0x1010, 0x0101);
}

TEST_F(I8086_XORFixture, XOR_AL_Iv_Test3) {
    XOR_CanDo_XOR_AI<WORD>(0x0000, 0x0000);
}

TEST_F(I8086_XORFixture, XOR_AL_Iv_Test4) {
    XOR_CanDo_XOR_AI<WORD>(0xFFFF, 0xFFFF);
}

TEST_F(I8086_XORFixture, XOR_AL_Iv_Test5) {
    XOR_CanDo_XOR_AI<WORD>(0xFFFF, 0x0000);
}
