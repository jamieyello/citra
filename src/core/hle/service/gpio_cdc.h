// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace GPIO {

class GPIO_CDC final : public Interface {
public:
    GPIO_CDC();
    ~GPIO_CDC() override;

    std::string GetPortName() const override {
        return "gpio:CDC";
    }
};

} // namespace PS
} // namespace Service
