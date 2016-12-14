// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace PDN {

class PDN_D final : public Interface {
public:
    PDN_D();
    ~PDN_D() override;

    std::string GetPortName() const override {
        return "pdn:d";
    }
};

} // namespace PDN
} // namespace Service
