// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace I2C {

class I2C_IR final : public Interface {
public:
    I2C_IR();
    ~I2C_IR() override;

    std::string GetPortName() const override {
        return "i2c::IR";
    }
};

} // namespace I2C
} // namespace Service
