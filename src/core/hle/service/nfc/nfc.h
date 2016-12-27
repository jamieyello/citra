// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"

namespace Service {

class Interface;

namespace NFC {

struct ConnectionStatus {
    u8 unknown[0x60];
};

struct TagInfo {
    u8 unknown[0x54];
};

struct CommonInfo {
    u8 unknown[0x40];
};

void Initialize(Interface* self);

void Finalize(Interface* self);

void Connect(Interface* self);

void Disconnect(Interface* self);

void StartDetection(Interface* self);

void StopDetection(Interface* self);

void Mount(Interface* self);

void GetStatus(Interface* self);

void GetTargetConnectionStatus(Interface* self);

void GetConnectionStatus(Interface* self);

void GetTagInfo(Interface* self);

void GetConnectResult(Interface* self);

void GetNfpRegisterInfo(Interface* self);

void GetNfpCommonInfo(Interface* self);

void SetActivateEvent(Interface* self);

void SetDeactivateEvent(Interface* self);

/// Initialize all NFC services.
void Init();

} // namespace NFC
} // namespace Service
