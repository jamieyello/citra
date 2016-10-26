// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/kernel/event.h"
#include "core/hle/service/ac_i.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace AC_U

namespace AC_I {

const Interface::FunctionInfo FunctionTable[] = {
    {0x00230042, nullptr, "AddAllowApType"},
    {0x00400042, nullptr, "SetClientVersion"},
    {0x04010040, nullptr, "LoadNetworkSetting"},
    {0x04070000, nullptr, "GetNetworkSetting_Version"},
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface class

Interface::Interface() {
    Register(FunctionTable);
}

Interface::~Interface() {
}

} // namespace
