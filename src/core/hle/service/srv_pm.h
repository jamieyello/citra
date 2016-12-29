// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace SRV {

/// Interface to "srv:" service
class SRV_PM final : public Interface {
public:
    SRV_PM();
    ~SRV_PM() override;

    std::string GetPortName() const override {
        return "srv:pm";
    }
};

} // namespace SRV
} // namespace Service
