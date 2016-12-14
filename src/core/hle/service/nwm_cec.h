// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace NWM {

class NWM_CEC : public Interface {
public:
    NWM_CEC();
    ~NWM_CEC() override;

    std::string GetPortName() const override {
        return "nwm::CEC";
    }
};

} // namespace NWM
} // namespace Service
