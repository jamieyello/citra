// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/service/pxi_dev.h"

namespace Service {
namespace PXI {

static void ReadHostIO(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service, "called");
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x000101C2, nullptr, "ReadHostIO"},
};

PXI_DEV::PXI_DEV() {
    Register(FunctionTable);
}

PXI_DEV::~PXI_DEV() {}

} // namespace PXI
} // namespace Service
