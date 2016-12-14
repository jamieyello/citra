// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace CDC {

class CDC_DSP final : public Interface {
public:
    CDC_DSP();
    ~CDC_DSP() override;

    std::string GetPortName() const override {
        return "cdc:DSP";
    }
};

} // namespace CDC
} // namespace Service
