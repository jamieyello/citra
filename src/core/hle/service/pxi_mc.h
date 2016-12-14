// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace PXI {

class PXI_MC final : public Interface {
public:
    PXI_MC();
    ~PXI_MC() override;

    std::string GetPortName() const override {
        return "pxi:mc";
    }
};

} // namespace PXI
} // namespace Service
