// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/service/mcu_hwc.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace MCU_HWC

namespace MCU_HWC {

static void GetMcuFwVerHigh(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    cmd_buff[2] = 0xA;

    //LOG_WARNING(Service_AC, "(STUBBED) called");
}

static void GetMcuFwVerLow(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    cmd_buff[2] = 0x1;

    //LOG_WARNING(Service_AC, "(STUBBED) called");
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x00010082, nullptr, "ReadRegister"},
    {0x00020082, nullptr, "WriteRegister"},
    {0x00030042, nullptr, "GetInfoRegisters"},
    {0x00040000, nullptr, "GetBatteryVoltage"},
    {0x00050000, nullptr, "GetBatteryLevel"},
    {0x00060040, nullptr, "SetPowerLEDPattern"},
    {0x00070040, nullptr, "SetWifiLEDState"},
    {0x00080040, nullptr, "SetCameraLEDPattern"},
    {0x00090040, nullptr, "Set3DLEDState"},
    {0x000A0640, nullptr, "SetInfoLEDPattern"},
    {0x000B0000, nullptr, "GetSoundVolume"},
    {0x000F0000, nullptr, "GetRtcTime"},
    {0x00100000, GetMcuFwVerHigh, "GetMcuFwVerHigh"},
    {0x00110000, GetMcuFwVerLow, "GetMcuFwVerLow"},

};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface class

Interface::Interface() {
    Register(FunctionTable);
}

Interface::~Interface() {
}

} // namespace
