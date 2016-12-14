// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/service/nwm_ext.h"

namespace Service {
namespace NWM {

const Interface::FunctionInfo FunctionTable[] = {
    {0x00020000, nullptr, "OpenMpMode"},
    {0x00030000, nullptr, "CloseMpMode"},
};

NWM_EXT::NWM_EXT() {
    Register(FunctionTable);
}

NWM_EXT::~NWM_EXT() {}

} // namespace NWM
} // namespace Service
