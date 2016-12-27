// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace SPI {

class SPI_NOR final : public Interface {
public:
    SPI_NOR();
    ~SPI_NOR() override;

    std::string GetPortName() const override {
        return "SPI::NOR";
    }
};

} // namespace SPI
} // namespace Service
