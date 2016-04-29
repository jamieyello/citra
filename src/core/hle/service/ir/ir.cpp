// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <sstream>
#include "common/string_util.h"

#include "core/hle/kernel/event.h"
#include "core/hle/kernel/shared_memory.h"

#include "core/hle/service/service.h"
#include "core/hle/service/ir/ir.h"
#include "core/hle/service/ir/ir_rst.h"
#include "core/hle/service/ir/ir_u.h"
#include "core/hle/service/ir/ir_user.h"

namespace Service {
namespace IR {

static Kernel::SharedPtr<Kernel::Event> handle_event;
static Kernel::SharedPtr<Kernel::Event> conn_status_event;
static Kernel::SharedPtr<Kernel::Event> receive_event;
static Kernel::SharedPtr<Kernel::Event> send_event;
static Kernel::SharedPtr<Kernel::SharedMemory> shared_memory;
static Kernel::SharedPtr<Kernel::SharedMemory> transfer_shared_memory;

static u32 transfer_buff_size;
static u32 recv_buff_size;
static u32 unk1;
static u32 send_buff_size;
static u32 unk2;
static BaudRate baud_rate;

static ConnectionStatus connection_status = ConnectionStatus::STOPPED;

void GetHandles(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0x4000000;
    cmd_buff[3] = Kernel::g_handle_table.Create(Service::IR::shared_memory).MoveFrom();
    cmd_buff[4] = Kernel::g_handle_table.Create(Service::IR::handle_event).MoveFrom();
}

void InitializeIrNopShared(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    transfer_buff_size = cmd_buff[1];
    recv_buff_size     = cmd_buff[2];
    unk1               = cmd_buff[3];
    send_buff_size     = cmd_buff[4];
    unk2               = cmd_buff[5];
    baud_rate          = static_cast<BaudRate>(cmd_buff[6] & 0xFF);
    Handle handle      = cmd_buff[8];

    if(Kernel::g_handle_table.IsValid(handle)) {
        transfer_shared_memory = Kernel::g_handle_table.Get<Kernel::SharedMemory>(handle);
        transfer_shared_memory->name = "IR:TransferSharedMemory";
    }

    connection_status = ConnectionStatus::STOPPED;

    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_IR, "(STUBBED) called, transfer_buff_size=%d, recv_buff_size=%d, "
                "unk1=%d, send_buff_size=%d, unk2=%d, baud_rate=%u, handle=0x%08X",
                transfer_buff_size, recv_buff_size, unk1, send_buff_size, unk2, baud_rate, handle);
}

void RequireConnection(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    connection_status = ConnectionStatus::CONNECTED;

    TransferMemory& t_mem = *reinterpret_cast<TransferMemory*>(transfer_shared_memory->GetPointer());
    t_mem.connection_info.connection_status = ConnectionStatus::STOPPED; //connection_status;
    //t_mem.connection_info.unk_0E = true;

    conn_status_event->Signal();

    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_IR, "(STUBBED) called");
}

static ResultCode ProcessPacket(VAddr addr, u32 size) {
    u8 command_id = Memory::Read8(addr);
    switch (command_id) {
    case 2: {// request read
        u8 unk5 = Memory::Read8(addr + 1);
        u16 unk6 = Memory::Read16(addr + 2);
        u16 unk8 = Memory::Read16(addr + 4);
        receive_event->Signal();
        break;
    }
    }
    return RESULT_SUCCESS;
}

void SendIrNop(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 size = cmd_buff[1];
    u32 buffer_addr = cmd_buff[3];

    cmd_buff[1] = ProcessPacket(buffer_addr, size).raw;

    LOG_WARNING(Service_IR, "(STUBBED) called, addr=0x%08X, size=%d", buffer_addr, size);
    Common::Dump(buffer_addr, size);
}

void SendIrNopLarge(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 size = cmd_buff[1];
    u32 buffer_addr = cmd_buff[3];

    cmd_buff[1] = ProcessPacket(buffer_addr, size).raw;

    LOG_WARNING(Service_IR, "(STUBBED) called, addr=0x%08X, size=%d", buffer_addr, size);
    Common::Dump(buffer_addr, size);
}

void ReceiveIrnop(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 size = cmd_buff[1];
    u32 size_shift = cmd_buff[2];
    u32 buffer_addr = cmd_buff[3];

    cmd_buff[1] = ProcessPacket(buffer_addr, size).raw;

    LOG_WARNING(Service_IR, "(STUBBED) called, addr=0x%08X, size=%d", buffer_addr, size);
    Common::Dump(buffer_addr, size);
}

void ReceiveIrnopLarge(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 size = cmd_buff[1];
    u32 size_shift = cmd_buff[2];
    u32 buffer_addr = cmd_buff[3];

    cmd_buff[1] = ProcessPacket(buffer_addr, size).raw;

    LOG_WARNING(Service_IR, "(STUBBED) called, addr=0x%08X, size=%d", buffer_addr, size);
    Common::Dump(buffer_addr, size);
}


void GetConnectionStatus(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;

    cmd_buff[3] = static_cast<u32>(connection_status);

    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void Disconnect(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    connection_status = ConnectionStatus::STOPPED;

    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void GetReceiveEvent(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[3] = Kernel::g_handle_table.Create(Service::IR::receive_event).MoveFrom();

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
    cmd_buff[3] = Kernel::g_handle_table.Create(Service::IR::conn_status_event).MoveFrom();

    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void FinalizeIrNop(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_IR, "(STUBBED) called");
}

void ReleaseReceivedData(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 addr = cmd_buff[1];

    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_IR, "(STUBBED) called, addr=0x%08X", addr);
}

void Init() {
    using namespace Kernel;

    AddService(new IR_RST_Interface);
    AddService(new IR_U_Interface);
    AddService(new IR_User_Interface);

    using Kernel::MemoryPermission;
    shared_memory = SharedMemory::Create(0x1000, Kernel::MemoryPermission::ReadWrite,
                                         Kernel::MemoryPermission::ReadWrite, "IR:SharedMemory");
    transfer_shared_memory = nullptr;

    // Create event handle(s)
    handle_event = Event::Create(ResetType::OneShot, "IR:HandleEvent");
    receive_event = Event::Create(ResetType::OneShot, "IR:ReceiveEvent");
    send_event = Event::Create(ResetType::OneShot, "IR:SendEvent");
    conn_status_event = Event::Create(ResetType::OneShot, "IR:ConnectionStatusEvent");
}

void Shutdown() {
    transfer_shared_memory = nullptr;
    shared_memory = nullptr;
    handle_event = nullptr;
    receive_event = nullptr;
    send_event = nullptr;
    conn_status_event = nullptr;
}

} // namespace IR

} // namespace Service
