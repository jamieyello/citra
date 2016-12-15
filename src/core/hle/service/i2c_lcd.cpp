// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/service/i2c_lcd.h"

namespace Service {
namespace I2C {


const Interface::FunctionInfo FunctionTable[] = {
    {0x000500C0, nullptr, "WriteRegister8"},
    {0x000D00C0, nullptr, "ReadRegisterBuffer8"},
};


I2C_LCD::I2C_LCD() {
    Register(FunctionTable);
}

I2C_LCD::~I2C_LCD() {}

} // namespace I2C
} // namespace Service
