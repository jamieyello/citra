// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/nfc/nfc.h"
#include "core/hle/service/nfc/nfc_u.h"

namespace Service {
namespace NFC {

const Interface::FunctionInfo FunctionTable[] = {
    // clang-format off
    {0x00010040, Initialize, "Initialize"},
    {0x00020040, nullptr, "Finalize"},
    {0x00030000, nullptr, "Connect"},
    {0x00040000, nullptr, "Disconnect"},
    {0x00050040, nullptr, "StartDetection"},
    {0x00060000, nullptr, "StopDetection"},
    {0x00070000, nullptr, "Mount"},
    {0x00080000, nullptr, "Unmount"},
    {0x00090002, nullptr, "Flush"},
    {0x000A0000, nullptr, "Restore"},
    {0x000B0000, SetActivateEvent, "SetActivateEvent"},
    {0x000C0000, nullptr, "SetDeactivateEvent"},
    {0x000D0000, nullptr, "GetStatus"},
    {0x000E0000, nullptr, "GitSubState"},
    {0x000F0000, nullptr, "GetTargetConnectionStatus"},
    {0x00100000, nullptr, "GetConnectionStatus"},
    {0x00110000, nullptr, "GetTagInfo"},
    {0x00120000, nullptr, "GetConnectResult"},
    {0x00130040, nullptr, "OpenApplicationArea"},
    {0x00140384, nullptr, "CreateApplicationArea"},
    {0x00150040, nullptr, "ReadApplicationArea"},
    {0x00160242, nullptr, "WriteApplicationArea"},
    {0x00170000, nullptr, "GetNfpRegisterInfo"},
    {0x00180000, nullptr, "GetNfpCommonInfo"},
    {0x00190000, nullptr, "InitializeCreateInfo"},
    {0x001A0000, nullptr, "MountRom"},
    {0x001B0000, nullptr, "GetNfpRomInfo"},
    {0x001C0040, nullptr, "SetPowerSavingModeEnabled"},
    {0x001D0040, nullptr, "SetProtocolFilter"},
    {0x001E0040, nullptr, "IsAvailableFontRegion"},
    {0x001F0080, nullptr, "StartDetectionWithProtocolFilter"},
    {0x00200102, nullptr, "SendCommand"},
    {0x00210000, nullptr, "KeepSession"},
    {0x00220000, nullptr, "ReleaseSession"},
    // clang-format on
};

NFC_U::NFC_U() {
    Register(FunctionTable);
}

} // namespace NFC
} // namespace Service
