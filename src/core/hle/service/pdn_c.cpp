// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/service/pdn_c.h"

namespace Service {
namespace PDN {


const Interface::FunctionInfo FunctionTable[] = {
    {0x00010040, nullptr, "unk_10040"},
    {0x00020000, nullptr, "unk_20000"},

};


PDN_C::PDN_C() {
    Register(FunctionTable);
}

PDN_C::~PDN_C() {}

} // namespace PDN
} // namespace Service
