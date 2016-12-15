// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/service/pdn_g.h"

namespace Service {
namespace PDN {

static void GpuPower(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u8 p1 = cmd_buff[1] & 0xFF;
    u8 p2 = cmd_buff[2] & 0xFF;
    u8 p3 = cmd_buff[3] & 0xFF;

    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_PDN, "called, p1=%u, p2=%u, p3=%u", p1, p2, p3);
}

const Interface::FunctionInfo FunctionTable[] = {
    // clang-format off
    {0x000100C0, GpuPower, "GpuPower"},
    // clang-format on
};


PDN_G::PDN_G() {
    Register(FunctionTable);
}

PDN_G::~PDN_G() {}

} // namespace PDN
} // namespace Service
