// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace SPI {

class SPI_CD2 final : public Interface {
public:
    SPI_CD2();
    ~SPI_CD2() override;

    std::string GetPortName() const override {
        return "SPI::CD2";
    }
};

} // namespace SPI
} // namespace Service
