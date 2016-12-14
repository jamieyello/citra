// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace CDC {

class CDC_MIC final : public Interface {
public:
    CDC_MIC();
    ~CDC_MIC() override;

    std::string GetPortName() const override {
        return "cdc:MIC";
    }
};

} // namespace CDC
} // namespace Service
