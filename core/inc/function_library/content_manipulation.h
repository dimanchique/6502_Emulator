#pragma once

#include "core/compilers_macro.h"
#include "core/types.h"

namespace ReSimFunctionLibrary::ContentManipulation {

    constexpr FORCE_INLINE WORD getWordAsSwappedBytes_Copy(const BYTE& lsbReg, const BYTE& msbReg) noexcept {
        WORD value = 0;
        value |= lsbReg << 8;
        value |= msbReg;
        return value;
    }

    constexpr FORCE_INLINE void putWordToBytesSwapped_Ref(const WORD value, BYTE& lsbReg, BYTE& msbReg) noexcept {
        msbReg = value & 0xFF;
        lsbReg = (value >> 8) & 0xFF;
    }
}
