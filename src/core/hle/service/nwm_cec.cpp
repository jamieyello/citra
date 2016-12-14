// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/kernel/event.h"
#include "core/hle/service/nwm_cec.h"

namespace Service {
namespace NWM {

static Kernel::SharedPtr<Kernel::Event> handle_event;

const Interface::FunctionInfo FunctionTable[] = {
    {0x00060002, nullptr, "StartContinuousScan"},
    {0x000D0082, nullptr, "SetModuleFilter"},
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface class

NWM_CEC::NWM_CEC() {
    handle_event = Kernel::Event::Create(Kernel::ResetType::OneShot, "NWM_CEC::handle_event");

    Register(FunctionTable);
}

NWM_CEC::~NWM_CEC() {
    handle_event = nullptr;
}

} // namespace NWM
} // namespace Service
