// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/service/i2c_cam.h"

namespace Service {
namespace I2C {

static void ReadRegister16(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0;
    LOG_TRACE(Service_PDN, "(STUBBED) called");
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x000500C0, nullptr, "WriteRegister8"},
    {0x000A0080, ReadRegister16, "ReadRegister16"},
    {0x000D00C0, nullptr, "ReadRegisterBuffer8"},
};

I2C_CAM::I2C_CAM() {
    Register(FunctionTable);
}

I2C_CAM::~I2C_CAM() {}

} // namespace I2C
} // namespace Service
