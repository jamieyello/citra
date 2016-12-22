// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included..

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace IR {

class IR_RST final : public Interface {
public:
    IR_RST();

    std::string GetPortName() const override {
        return "ir:rst";
    }
};

} // namespace IR
} // namespace Service
