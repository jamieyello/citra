// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace MCU {

class MCU_CAM final : public Interface {
public:
    MCU_CAM();
    ~MCU_CAM() override;

    std::string GetPortName() const override {
        return "mcu::CAM";
    }
};

} // namespace MCU
} // namespace Service
