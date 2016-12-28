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
static bool nfc_connected = false;
static TagState nfc_tag_state = TagState::NotInitialized;
static CommunicationStatus nfc_status = CommunicationStatus::NfcInitialized;

static ConnectionStatus connection_status{};
static TagInfo tag_info{};
static CommonInfo common_info{};
static AmiiboSettings amiibo_settings{};

void Initialize(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u8 param = static_cast<u8>(cmd_buff[1] & 0xFF);

    nfc_tag_state = TagState::Initialized;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_NFC, "(STUBBED) called, param=%u", param);
}

void Finalize(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u8 param = static_cast<u8>(cmd_buff[1] & 0xFF);
    nfc_tag_state = TagState::NotInitialized;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_NFC, "(STUBBED) called, param=%u", param);
}

void Connect(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    nfc_connected = true;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void Disconnect(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    nfc_connected = false;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void StartDetection(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    nfc_tag_state = TagState::TagInRange;
    activate_event->Signal();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void StopDetection(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    nfc_tag_state = TagState::Initialized;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void Mount(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    nfc_tag_state = TagState::TagDataLoaded;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void Unmount(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    nfc_tag_state = TagState::Initialized;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void GetStatus(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    cmd_buff[2] = static_cast<u8>(nfc_tag_state);
    LOG_DEBUG(Service_NFC, "(STUBBED) called");
}

void GetTargetConnectionStatus(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    cmd_buff[2] = static_cast<u8>(nfc_status);
    LOG_DEBUG(Service_NFC, "(STUBBED) called");
}

void GetConnectionStatus(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    std::memcpy(cmd_buff + 2, &connection_status, sizeof(ConnectionStatus));
    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void GetTagInfo(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    std::memcpy(cmd_buff + 2, &tag_info, sizeof(TagInfo));

    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void GetConnectResult(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    cmd_buff[2] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void GetNfpRegisterInfo(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    std::memcpy(cmd_buff + 2, &amiibo_settings, sizeof(AmiiboSettings));
    LOG_WARNING(Service_NFC, "(STUBBED) called");
}

void GetNfpCommonInfo(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    std::memcpy(cmd_buff + 2, &common_info, sizeof(CommonInfo));

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
