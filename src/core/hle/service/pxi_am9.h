// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace PXI {

class PXI_AM9 final : public Interface {
public:
    PXI_AM9();
    ~PXI_AM9() override;

    std::string GetPortName() const override {
        return "pxi:am9";
    }
};

} // namespace PXI
} // namespace Service
