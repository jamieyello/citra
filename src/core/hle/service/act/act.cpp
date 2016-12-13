// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/kernel/shared_memory.h"
#include "core/hle/service/act/act.h"
#include "core/hle/service/act/act_a.h"
#include "core/hle/service/act/act_u.h"

namespace Service {
namespace ACT {

static Kernel::SharedPtr<Kernel::SharedMemory> shared_memory;

void Initialize(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 version = cmd_buff[1];
    self->SetVersion(version);
    u32 size = cmd_buff[2];
    Kernel::Handle sh_mem = cmd_buff[6];

    if (Kernel::g_handle_table.IsValid(sh_mem)) {
        shared_memory = Kernel::g_handle_table.Get<Kernel::SharedMemory>(sh_mem);
        shared_memory->name = "ACT:shared_memory";
    }

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_ACT, "(STUBBED) called, version=0x%X, sh_mem=0x%X, size=0x%X", version,
                sh_mem, size);
}

void GetErrorCode(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 error_code = cmd_buff[1];

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    cmd_buff[2] = error_code; // TODO (mailwl): Do error conversion
    LOG_WARNING(Service_ACT, "(STUBBED) called, errorcode=0x%08X", error_code);
}

ResultCode FillDataBlock(BlkID bkl_id, VAddr buf, u32 size) {
    Memory::ZeroBlock(buf, size);
    switch (bkl_id) {
    case BlkID::AccountId: {
        LOG_WARNING(Service_CFG, "AccountId");
        return RESULT_SUCCESS;
    }
    }
    return RESULT_SUCCESS; // TODO (mailwl): find error code
}

void GetAccountDataBlock(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u8 unknown = static_cast<u8>(cmd_buff[1] & 0xFF);

    u32 size = cmd_buff[2];
    BlkID blk_id = static_cast<BlkID>(cmd_buff[3]);
    VAddr buf = cmd_buff[5];

    cmd_buff[1] = FillDataBlock(blk_id, buf, size).raw;
    LOG_WARNING(Service_ACT, "(STUBBED) called, unknown=0x%X, size=0x%X, blk_id=0x%X, buf=0x%08X",
                unknown, size, blk_id, buf);
}

void GenerateUuid(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unknown = cmd_buff[1];

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    std::memset(cmd_buff+2, 0, 0x10); // TODO (mailwl): fill with something
    LOG_WARNING(Service_ACT, "(STUBBED) called, unknown=0x%08X", unknown);
}

void Init() {
    AddService(new ACT_A);
    AddService(new ACT_U);

    shared_memory = nullptr;
}

void Shutdown() {
    shared_memory = nullptr;
}

} // namespace ACT
} // namespace Service
