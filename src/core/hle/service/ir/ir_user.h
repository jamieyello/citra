// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace IR {

class IR_User final : public Interface {
public:
    IR_User();

    std::string GetPortName() const override {
        return "ir:USER";
    }
};

} // namespace IR
} // namespace Service
