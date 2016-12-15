// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/kernel/event.h"
#include "core/hle/service/mcu_gpu.h"

namespace Service {
namespace MCU {

static Kernel::SharedPtr<Kernel::Event> mcu_gpu_event;

static void GetLcdPowerState(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 1;
    cmd_buff[3] = 1;
     LOG_WARNING(Service_MCU, "(STUBBED) called");
}

static void SetLcdPowerState(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u8 p1 = cmd_buff[1] & 0xFF;
    u8 p2 = cmd_buff[2] & 0xFF;
    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_MCU, "(STUBBED) called, p1=%u, p2=%u", p1, p2);
}

static void GetLcdInterfaceState(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 1;
    LOG_WARNING(Service_MCU, "(STUBBED) called");
}

static void SetLcdInterfaceState(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u8 state = cmd_buff[1];

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_MCU, "(STUBBED) called, state=%u", state);
}

static void GetMcuFwVerHigh(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 11;
    LOG_WARNING(Service_MCU, "(STUBBED) called");
}

static void GetMcuFwVerLow(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0;
    LOG_WARNING(Service_MCU, "(STUBBED) called");
}

static void Set3dLedState(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u8 state = cmd_buff[1];

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_MCU, "(STUBBED) called, state=%u", state);
}

static void GetMcuGpuEventHandle(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[3] = Kernel::g_handle_table.Create(mcu_gpu_event).MoveFrom();

    LOG_WARNING(Service_MCU, "(STUBBED) called");
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x00010000, GetLcdPowerState, "GetLcdPowerState"},
    {0x00020080, SetLcdPowerState, "SetLcdPowerState"},
    {0x00030000, GetLcdInterfaceState, "GetLcdInterfaceState"},
    {0x00040040, SetLcdInterfaceState, "SetLcdInterfaceState"},
    {0x00090000, GetMcuFwVerHigh, "GetMcuFwVerHigh"},
    {0x000A0000, GetMcuFwVerLow, "GetMcuFwVerLow"},
    {0x000B0040, Set3dLedState, "Set3dLedState"},
    {0x000C0000, nullptr, "Get3dLedState"},
    {0x000D0000, GetMcuGpuEventHandle, "GetMcuGpuEventHandle"},
    {0x000E0000, nullptr, "GetMcuGpuEventReason"},
};

MCU_GPU::MCU_GPU() {
    Register(FunctionTable);
    mcu_gpu_event = Kernel::Event::Create(Kernel::ResetType::OneShot, "MCU_GPU::event");
}

MCU_GPU::~MCU_GPU() {
    mcu_gpu_event = nullptr;
}

} // namespace MCU
} // namespace Service
