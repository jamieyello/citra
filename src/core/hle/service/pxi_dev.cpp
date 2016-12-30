// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "common/swap.h"
#include "core/hle/service/pxi_dev.h"

namespace Service {
namespace PXI {

static void ReadHostIO(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 size = cmd_buff[1];
    u32 sector_count = cmd_buff[2];
    u8 sector_size = cmd_buff[3] & 0xFF;
    u32_be cmd1 = cmd_buff[4];
    u32_be cmd2 = cmd_buff[5];
    u32_be cmd3 = cmd_buff[6];
    u32_be cmd4 = cmd_buff[7];
    VAddr buffer = cmd_buff[9];
    Memory::ZeroBlock(buffer, size);

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service, "called, size=0x%X, cmd1=0x%X, cmd2=0x%X, cmd3=0x%X, cmd3=0x%X", size,
                cmd1, cmd2, cmd3, cmd4);
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x000101C2, ReadHostIO, "ReadHostIO"},
};

PXI_DEV::PXI_DEV() {
    Register(FunctionTable);
}

PXI_DEV::~PXI_DEV() {}

} // namespace PXI
} // namespace Service
