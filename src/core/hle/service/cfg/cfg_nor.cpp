// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/cfg/cfg.h"
#include "core/hle/service/cfg/cfg_nor.h"

namespace Service {
namespace CFG {

static void Initialize(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 use_spi = cmd_buff[1] & 0xFF;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error

    LOG_WARNING(Service_CFG, "(STUBBED) called, use_spi=%u", use_spi);
}

static void Finalize(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error

    LOG_WARNING(Service_CFG, "(STUBBED) called");
}

static void Read(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unk = cmd_buff[1];
    u32 size = cmd_buff[2];
    u32 addr = cmd_buff[4];
    Memory::ZeroBlock(addr, size);

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error

    LOG_WARNING(Service_CFG, "(STUBBED) called, unk=0x%X, size=0x%X, addr=0x%08X", unk, size, addr);
}

static void Write(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 addr = cmd_buff[1];
    u32 size = cmd_buff[2];
    u32 unk = cmd_buff[4];

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error

    LOG_WARNING(Service_CFG, "(STUBBED) called, addr=0x%08X, size=0x%X, unk=0x%X", addr, size, unk);
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x00010040, Initialize, "Initialize"},
    {0x00020000, Finalize, "Finalize"},
    {0x00050082, Read, "Read"},
    {0x00060082, Write, "Write"},
};

CFG_NOR_Interface::CFG_NOR_Interface() {
    Register(FunctionTable);
}

} // namespace CFG
} // namespace Service
