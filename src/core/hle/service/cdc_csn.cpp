// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/kernel/event.h"
#include "core/hle/service/cdc_csn.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace AC_U

namespace CDC_CSN {

static Kernel::SharedPtr<Kernel::Event> event;

static void GetEventHandle(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;                                      // No error
    cmd_buff[3] = Kernel::g_handle_table.Create(event).MoveFrom(); // Event handle

    //LOG_WARNING(Service_CECD, "(STUBBED) called");
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x00090000, GetEventHandle, "GetEventHandle"},
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface class

Interface::Interface() {
    Register(FunctionTable);

    event = Kernel::Event::Create(Kernel::ResetType::OneShot, "CDC_CSN::event");
}

Interface::~Interface() {
}

} // namespace
