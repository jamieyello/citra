// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/kernel/event.h"
#include "core/hle/service/pxi_dev.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace PXI_DEV

namespace PXI_DEV {

const Interface::FunctionInfo FunctionTable[] = {
    {0x000101C2, nullptr, "Initialize"},
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface class

Interface::Interface() {
    Register(FunctionTable);
}

Interface::~Interface() {}

} // namespace
