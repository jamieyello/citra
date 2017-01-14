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
    LOG_WARNING(Service, "(STUBBED) called, version=0x%X, sh_mem=0x%X, size=0x%X", version,
                sh_mem, size);
}

void Init() {
    AddService(new ACT_A);
    AddService(new ACT_U);
}

} // namespace ACT
} // namespace Service
