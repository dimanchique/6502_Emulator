#include "Operations/CPU6502_ADC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ADC_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetImmediateAddressValue(cycles, memory);
    ExecuteADC(cpu, Data.Value);
}

void CPU6502_ADC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteADC(cpu, Data.Value);
}

void CPU6502_ADC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteADC(cpu, Data.Value);
}

void CPU6502_ADC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteADC(cpu, Data.Value);
}

void CPU6502_ADC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, affectingRegister);
    ExecuteADC(cpu, Data.Value);
}

void CPU6502_ADC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_ADC_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(cycles, memory, cpu, cpu.Y);
}

void CPU6502_ADC_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteADC(cpu, Data.Value);
}

void CPU6502_ADC_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteADC(cpu, Data.Value);
}
