// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/core_timing.h"
#include "core/hle/kernel/event.h"
#include "core/hle/kernel/kernel.h"
#include "core/hle/kernel/shared_memory.h"
#include "core/hle/service/ir/ir.h"
#include "core/hle/service/ir/ir_rst.h"
#include "core/hle/service/ir/ir_u.h"
#include "core/hle/service/ir/ir_user.h"
#include "core/hle/service/service.h"

namespace Service {
namespace IR {

static Kernel::SharedPtr<Kernel::Event> handle_event;
static Kernel::SharedPtr<Kernel::SharedMemory> shared_memory;

static Kernel::SharedPtr<Kernel::Event> conn_status_event;
static Kernel::SharedPtr<Kernel::Event> receive_event;
static Kernel::SharedPtr<Kernel::Event> send_event;
static Kernel::SharedPtr<Kernel::SharedMemory> transfer_shared_memory;

static s32 send_event_callback_type;
static s32 recv_event_callback_type;
static u32 transfer_buff_size;
static u32 recv_buff_size;
static u32 unk1;
static u32 send_buff_size;
static u32 unk2;
static BaudRate baud_rate;

static ConnectionStatus connection_status;
static ConnectionRole connection_role;

static void FillConnectionInfo() {
    TransferMemory& trans_mem =
        *reinterpret_cast<TransferMemory*>(transfer_shared_memory->GetPointer());
    trans_mem.connection_info.connection_status = connection_status;
    trans_mem.connection_info.connection_role = connection_role;
    trans_mem.connection_info.unk_0E = true;
}

void GetHandles(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0x4000000;
    cmd_buff[3] = Kernel::g_handle_table.Create(shared_memory).MoveFrom();
    cmd_buff[4] = Kernel::g_handle_table.Create(handle_event).MoveFrom();
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void FinalizeIrNop(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void ClearReceiveBuffer(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void ClearSendBuffer(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void WaitConnection(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u8 unk = cmd_buff[1];
    uint64_t timeout = (uint64_t)cmd_buff[3] << 32 | cmd_buff[2];

    connection_status = ConnectionStatus::Connected;
    connection_role = ConnectionRole::Wait;

    FillConnectionInfo();

    conn_status_event->Signal(); // TODO (mailwl): really need this?

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called, unk=%u, timeout=%ull", unk, timeout);
}

void RequireConnection(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    connection_status = ConnectionStatus::Connected;
    connection_role = ConnectionRole::Require;

    FillConnectionInfo();

    conn_status_event->Signal(); // TODO (mailwl): really need this?

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void AutoConnection(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unknown = cmd_buff[1] & 0xFF;
    u64 sendReplyDelay = (u64)cmd_buff[3] << 32 | cmd_buff[2];
    u64 waitRequestMin = (u64)cmd_buff[5] << 32 | cmd_buff[4];
    u64 waitRequestMax = (u64)cmd_buff[7] << 32 | cmd_buff[6];
    u64 waitReplyMin = (u64)cmd_buff[9] << 32 | cmd_buff[8];
    u64 waitReplyMax = (u64)cmd_buff[11] << 32 | cmd_buff[10];

    // TODO (mailwl): check which needed for CCP

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void Disconnect(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void GetReceiveEvent(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[3] = Kernel::g_handle_table.Create(receive_event).MoveFrom();
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void GetSendEvent(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[3] = Kernel::g_handle_table.Create(Service::IR::send_event).MoveFrom();
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void GetConnectionStatusEvent(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[3] = Kernel::g_handle_table.Create(conn_status_event).MoveFrom();

    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void SendIrNop(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 size = cmd_buff[1];
    u32 buffer_addr = cmd_buff[3];

    // TODO (mailwl): parse buffer

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called, addr=0x%08X, size=%d", buffer_addr, size);
    CoreTiming::ScheduleEvent(100, recv_event_callback_type, 0);
}

void ReceiveIrnop(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 size = cmd_buff[1];
    u32 buffer_addr = cmd_buff[65];

    // TODO (mailwl): parse buffer

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called, addr=0x%08X, size=%d", buffer_addr, size);
    CoreTiming::ScheduleEvent(100, send_event_callback_type, 0);
}

void GetConnectionStatus(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = static_cast<u32>(connection_status);
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void GetConnectionRole(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = static_cast<u32>(connection_role);
    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void InitializeIrNopShared(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    transfer_buff_size = cmd_buff[1];
    recv_buff_size = cmd_buff[2];
    unk1 = cmd_buff[3];
    send_buff_size = cmd_buff[4];
    unk2 = cmd_buff[5];
    baud_rate = static_cast<BaudRate>(cmd_buff[6] & 0xFF);
    Handle memory_handle = cmd_buff[8];

    if (Kernel::g_handle_table.IsValid(memory_handle)) {
        transfer_shared_memory = Kernel::g_handle_table.Get<Kernel::SharedMemory>(memory_handle);
        transfer_shared_memory->name = "IR:TransferSharedMemory";
    } else {
        cmd_buff[1] = -1; // TODO (mailwl): find exact error code
        LOG_ERROR(Service_IR, "Error handle for shared memory");
        return;
    }

    connection_status = ConnectionStatus::Stopped;
    connection_role = ConnectionRole::None;

    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(
        Service_IR, "(STUBBED) called, transfer_buff_size=%d, recv_buff_size=%d, "
                    "unk1=%d, send_buff_size=%d, unk2=%d, baud_rate=%u, memory_handle=0x%08X",
        transfer_buff_size, recv_buff_size, unk1, send_buff_size, unk2, baud_rate, memory_handle);
}

void ReleaseReceivedData(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 addr = cmd_buff[1];

    cmd_buff[1] = RESULT_SUCCESS.raw;
    LOG_WARNING(Service_IR, "(STUBBED) called, addr=0x%08X", addr);
}

static void SendEventCallback(u64 /*user_data*/, int /*cycle_late*/) {
    send_event->signaled = true;
    send_event->WakeupAllWaitingThreads();
}

static void RecvEventCallback(u64 /*user_data*/, int /*cycle_late*/) {
    receive_event->signaled = true;
    receive_event->WakeupAllWaitingThreads();
}

void Init() {
    AddService(new IR_RST);
    AddService(new IR_U);
    AddService(new IR_User);

    using namespace Kernel;
    using Kernel::MemoryPermission;
    shared_memory = SharedMemory::Create(nullptr, 0x1000, Kernel::MemoryPermission::ReadWrite,
                                         Kernel::MemoryPermission::ReadWrite, 0,
                                         Kernel::MemoryRegion::BASE, "IR:SharedMemory");
    transfer_shared_memory = nullptr;

    // Create event handle(s)
    handle_event = Event::Create(ResetType::OneShot, "IR:HandleEvent");
    conn_status_event = Event::Create(ResetType::OneShot, "IR:ConnectionStatusEvent");
    send_event = Event::Create(ResetType::OneShot, "IR:SendEvent");
    receive_event = Event::Create(ResetType::OneShot, "IR:ReceiveEvent");

    connection_status = ConnectionStatus::Stopped;
    connection_role = ConnectionRole::None;

    send_event_callback_type = CoreTiming::RegisterEvent("SendEventCallback", SendEventCallback);
    recv_event_callback_type = CoreTiming::RegisterEvent("RecvEventCallback", RecvEventCallback);
}

void Shutdown() {
    transfer_shared_memory = nullptr;
    shared_memory = nullptr;
    handle_event = nullptr;
    conn_status_event = nullptr;
    send_event = nullptr;
    receive_event = nullptr;
}

} // namespace IR
} // namespace Service
