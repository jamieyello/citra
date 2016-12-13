// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/act/act.h"
#include "core/hle/service/act/act_u.h"

namespace Service {
namespace ACT {

const Interface::FunctionInfo FunctionTable[] = {
    {0x00010084, Initialize, "Initialize"},
    {0x00020040, GetErrorCode, "GetErrorCode"},
    {0x00050082, nullptr, "GetCommonInfo"},
    {0x000600C2, GetAccountDataBlock, "GetAccountDataBlock"},
    {0x00070082, nullptr, "GetAsyncResult"},
    {0x000800C2, nullptr, "GetMiiImage"},
    {0x000B0042, nullptr, "AcquireEulaList"},
    {0x000D0040, GenerateUuid, "GenerateUuid"},
    {0x00190044, nullptr, "AcquireMii"},
    {0x001E0082, nullptr, "AcquireEula"},
};

ACT_U::ACT_U() {
    Register(FunctionTable);
}

} // namespace ACT
} // namespace Service
