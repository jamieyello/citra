// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace AC_I

// socket service "ac:i"

namespace AC_I {

class Interface : public Service::Interface {
public:
    Interface();
    ~Interface();

    std::string GetPortName() const override {
        return "ac:i";
    }
};

} // namespace
