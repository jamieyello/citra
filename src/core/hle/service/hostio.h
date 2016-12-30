// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace HOSTIO {

class HOSTIO0 final : public Interface {
public:
    HOSTIO0();

    std::string GetPortName() const override {
        return "$hostio0";
    }
};

class HOSTIO1 final : public Interface {
public:
    HOSTIO1();

    std::string GetPortName() const override {
        return "$hostio1";
    }
};

class HioFIO final : public Interface {
public:
    HioFIO();

    std::string GetPortName() const override {
        return "$hioFIO";
    }
};

} // namespace HOSTIO
} // namespace Service
