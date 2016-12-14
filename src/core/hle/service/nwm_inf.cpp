// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/service/nwm_inf.h"

namespace Service {
namespace NWM {

const Interface::FunctionInfo FunctionTable[] = {
    {0x000603C4, nullptr, "RecvBeaconBroadcastData"},
    {0x00070742, nullptr, "ConnectToEncryptedAP"},
};

NWM_INF::NWM_INF() {
    Register(FunctionTable);
}

NWM_INF::~NWM_INF() {}

} // namespace NWM
} // namespace Service
