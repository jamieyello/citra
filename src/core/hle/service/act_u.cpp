// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/act_u.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace ACT_U

namespace ACT_U {

static void Initialize(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 version = cmd_buff[1];
    u32 size = cmd_buff[2];
    u32 process_id_header = cmd_buff[3];
    u32 copy_handle = cmd_buff[5];
    Handle sh_mem = cmd_buff[6];

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_ACT, "(STUBBED) called, version=0x%X, sh_mem=0x%X, size=0x%X", version,
                sh_mem, size);
}

static void GetAccountInfo(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 p1 = cmd_buff[1] & 0xFF;
    u32 size = cmd_buff[2];
    u32 p3 = cmd_buff[3];
    VAddr buf = cmd_buff[5];

    Memory::ZeroBlock(buf, size);

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_ACT, "(STUBBED) called, p1=0x%X, size=0x%X, p3=0x%X, buf=0x%08X", p1, size,
                p3, buf);
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x00010084, Initialize, "Initialize"},
    {0x00020040, nullptr, "GetErrorCode"},
    {0x000600C2, GetAccountInfo, "GetAccountInfo"},
    {0x000D0040, nullptr, "GenerateUuid"},
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface class

Interface::Interface() {
    Register(FunctionTable);
}

} // namespace
