// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/cfg/cfg.h"
#include "core/hle/service/cfg/cfg_u.h"

namespace Service {
namespace CFG {

const Interface::FunctionInfo FunctionTable[] = {
    // cfg common
    {0x00010082, GetConfigInfoBlk2, "GetConfig"},
    {0x00020000, SecureInfoGetRegion, "GetRegion"},
    {0x00030040, GenHashConsoleUnique, "GetTransferableId"},
    {0x00040000, GetRegionCanadaUSA, "IsCoppacsSupported"},
    {0x00050000, GetSystemModel, "GetSystemModel"},
    {0x00060000, GetModelNintendo2DS, "GetModelNintendo2DS"},
    {0x00070040, nullptr, "WriteToFirstByteCfgSavegame"},
    {0x00080080, nullptr, "GoThroughTable"},
    {0x00090040, GetCountryCodeString, "GetCountryCodeString"},
    {0x000A0040, GetCountryCodeID, "GetCountryCodeID"},
    {0x000B0000, nullptr, "IsFangateSupported"},
};

CFG_U_Interface::CFG_U_Interface() {
    Register(FunctionTable);
}

} // namespace CFG
} // namespace Service
