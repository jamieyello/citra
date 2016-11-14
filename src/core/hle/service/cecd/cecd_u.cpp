// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/cecd/cecd.h"
#include "core/hle/service/cecd/cecd_u.h"

namespace Service {
namespace CECD {

static const Interface::FunctionInfo FunctionTable[] = {
    {0x000100C2, Open, "Open"},
    {0x00020042, nullptr, "Read"},
    {0x00080102, nullptr, "Delete"},
    {0x000C0040, nullptr, "Stop"},
    {0x000D0082, GetCecInfoBuffer, "GetCecInfoBuffer"},
    {0x000E0000, GetCecStateAbbreviated, "GetCecStateAbbreviated"},
    {0x000F0000, GetCecInfoEventHandle, "GetCecInfoEventHandle"},
    {0x00100000, GetChangeStateEventHandle, "GetChangeStateEventHandle"},
    {0x00110104, OpenAndWriteFile, "OpenAndWriteFile"},
    {0x00120104, OpenAndReadFile, "OpenAndReadFile"},
};

CECD_U_Interface::CECD_U_Interface() {
    Register(FunctionTable);
}

} // namespace CECD
} // namespace Service
