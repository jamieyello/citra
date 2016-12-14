// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace I2C {

class I2C_CAM final : public Interface {
public:
    I2C_CAM();
    ~I2C_CAM() override;

    std::string GetPortName() const override {
        return "i2c::CAM";
    }
};

} // namespace I2C
} // namespace Service
