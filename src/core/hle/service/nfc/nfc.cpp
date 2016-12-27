// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/kernel/event.h"
#include "core/hle/service/nfc/nfc.h"
#include "core/hle/service/nfc/nfc_m.h"
#include "core/hle/service/nfc/nfc_u.h"

namespace Service {
namespace NFC {

static Kernel::SharedPtr<Kernel::Event> activate_event;
static Kernel::SharedPtr<Kernel::Event> deactivate_event;

void Initialize(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error

    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void SetActivateEvent(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    cmd_buff[3] = Kernel::g_handle_table.Create(activate_event).MoveFrom();

    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void SetDeactivateEvent(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    cmd_buff[3] = Kernel::g_handle_table.Create(deactivate_event).MoveFrom();

    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void Init() {
    AddService(new NFC_M());
    AddService(new NFC_U());

    activate_event = Kernel::Event::Create(Kernel::ResetType::OneShot, "NFC::activate_event");
    deactivate_event = Kernel::Event::Create(Kernel::ResetType::OneShot, "NFC::deactivate_event");
}

void Shutdown() {
    activate_event = nullptr;
    deactivate_event = nullptr;
}

} // namespace NFC
} // namespace Service
