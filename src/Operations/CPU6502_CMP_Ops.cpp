#include "Operations/CPU6502_CM_Ops.h"
#include "Operations/CPU6502_CMP_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_CMP_IM(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_IM(memory, cpu, cpu.A);
}

void CPU6502_CMP_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ZP(memory, cpu, cpu.A);
}

void CPU6502_CMP_ZPX(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ZP(memory, cpu, cpu.A, cpu.X);
}

void CPU6502_CMP_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(memory, cpu, cpu.A);
}

void CPU6502_CMP_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(memory, cpu, cpu.A, cpu.X);
}

void CPU6502_CMP_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(memory, cpu, cpu.A, cpu.Y);
}

void CPU6502_CMP_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(memory);
    ExecuteCM(cpu, cpu.A, Data);
}

void CPU6502_CMP_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(memory);
    ExecuteCM(cpu, cpu.A, Data);
}
