// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/service/gpio_mcu.h"

namespace Service {
namespace GPIO {

/*
const Interface::FunctionInfo FunctionTable[] = {
};
*/

GPIO_MCU::GPIO_MCU() {
    // Register(FunctionTable);
}

GPIO_MCU::~GPIO_MCU() {}

} // namespace GPIO
} // namespace Service