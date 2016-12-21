// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/kernel/event.h"
#include "core/hle/service/nim/nim.h"
#include "core/hle/service/nim/nim_aoc.h"
#include "core/hle/service/nim/nim_s.h"
#include "core/hle/service/nim/nim_u.h"
#include "core/hle/service/service.h"

namespace Service {
namespace NIM {

static Kernel::SharedPtr<Kernel::Event> sys_update_event;

void CheckForSysUpdateEvent(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[3] = Kernel::g_handle_table.Create(sys_update_event).MoveFrom();

    LOG_WARNING(Service_NIM, "(STUBBED) called");
}

void CheckSysUpdateAvailable(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // No update available

    LOG_WARNING(Service_NIM, "(STUBBED) called");
}

void Init() {
    AddService(new NIM_AOC_Interface);
    AddService(new NIM_S_Interface);
    AddService(new NIM_U_Interface);

    sys_update_event = Kernel::Event::Create(Kernel::ResetType::OneShot, "NIM::sys_update_event");
}

void Shutdown() {
    sys_update_event = nullptr;
}

} // namespace NIM

} // namespace Service
