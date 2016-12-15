// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace MCU {

class MCU_GPU final : public Interface {
public:
    MCU_GPU();
    ~MCU_GPU() override;

    std::string GetPortName() const override {
        return "mcu::GPU";
    }
};

} // namespace MCU
} // namespace Service
