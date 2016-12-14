// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace PDN {

class PDN_I final : public Interface {
public:
    PDN_I();
    ~PDN_I() override;

    std::string GetPortName() const override {
        return "pdn:i";
    }
};

} // namespace PDN
} // namespace Service
