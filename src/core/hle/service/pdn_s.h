// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace PDN {

class PDN_S final : public Interface {
public:
    PDN_S();
    ~PDN_S() override;

    std::string GetPortName() const override {
        return "pdn:s";
    }
};

} // namespace PDN
} // namespace Service
