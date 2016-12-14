// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace PS {

class PS_PS final : public Interface {
public:
    PS_PS();
    ~PS_PS() override;

    std::string GetPortName() const override {
        return "ps:ps";
    }
};

} // namespace PS
} // namespace Service
