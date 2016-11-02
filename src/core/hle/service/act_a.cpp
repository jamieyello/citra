// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/act_a.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace ACT_A

namespace ACT_A {

static void Initialize(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 version = cmd_buff[1];
    u32 size = cmd_buff[2];
    u32 process_id_header = cmd_buff[3];
    u32 copy_handle = cmd_buff[5];
    Handle sh_mem = cmd_buff[6];

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_ACT, "(STUBBED) called, version=0x%X, sh_mem=0x%X, size=0x%X", version, sh_mem, size);
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x00010084, Initialize, "Initialize"},
    {0x00020040, nullptr, "GetErrorCode"},
    {0x000600C2, nullptr, "GetAccountInfo"},
    {0x041300C2, nullptr, "UpdateMiiImage"},
    {0x041B0142, nullptr, "AgreeEula"},
    {0x04210042, nullptr, "UploadMii"},
    {0x04230082, nullptr, "ValidateMailAddress"},
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface class

Interface::Interface() {
    Register(FunctionTable);
}

} // namespace
