// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/ns_s.h"

namespace Service {
namespace NS {

static void LaunchTitle(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u64 title_id = (u64)cmd_buff[2] << 32 | cmd_buff[1];
    u32 flags = cmd_buff[5];

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_NS, "(STUBBED) called, title_id=0x%llX, flags=0x%08X", title_id, flags);
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x000100C0, nullptr, "LaunchFIRM"},
    {0x000200C0, LaunchTitle, "LaunchTitle"},
    {0x00030000, nullptr, "TerminateApplication"},
    {0x00040040, nullptr, "TerminateProcess"},
    {0x000500C0, nullptr, "LaunchApplicationFIRM"},
    {0x00060042, nullptr, "SetFIRMParams4A0"},
    {0x00070042, nullptr, "CardUpdateInitialize"},
    {0x00080000, nullptr, "CardUpdateShutdown"},
    {0x000D0140, nullptr, "SetTWLBannerHMAC"},
    {0x000E0000, nullptr, "ShutdownAsync"},
    {0x00100180, nullptr, "RebootSystem"},
    {0x00110100, nullptr, "TerminateTitle"},
    {0x001200C0, nullptr, "SetApplicationCpuTimeLimit"},
    {0x00150140, nullptr, "LaunchApplication"},
    {0x00160000, nullptr, "RebootSystemClean"},
};

NS_S::NS_S() {
    Register(FunctionTable);
}

} // namespace NS
} // namespace Service
