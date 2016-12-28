// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/common_funcs.h"
#include "common/common_types.h"

namespace Service {

class Interface;

namespace NFC {

struct Mii {
    u32 mii_id;
    u32 mac_address;
    u8 unknown;
    u8 allow_copy;
    u8 unknown1[0xE];
    u16 birthday;
    u16 mii_name[10];
    u16 width_height;
    u8 sharing;
    u8 makeup;
    u8 hair_style;
    u8 hair_color;
    u32 unknown2;
    u8 eyebrow_style;
    u8 eyebrow_scale;
    u16 eyebrow_rotation;
    u8 allow_copying;
    u8 unknown3[3];
    u8 mii_sharing_value;
    u8 unknown4[7];
    u16 author_name[10];
    u16 unknown5;
    u16 unknown6;
};
static_assert(sizeof(Mii) == 0x60, "Mii structure has incorrect size");

struct Amiibo {
    u8 serial_number[0x9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    u8 internal = 0;
    u8 lock[2] = {0x0F, 0xE0};
    u8 capability_container[4] = {0xF1, 0x10, 0xFF, 0xEE};
    // TODO fill all
};

enum class TagState : u8 {
    NotInitialized = 0,
    Initialized = 1,
    Scanning = 2,
    TagInRange = 3,
    TagOutOfRange = 4,
    TagDataLoaded = 5,
    TagDataLoadedRO = 6,
};

enum class CommunicationStatus : u8 {
    Disconnected = 0,
    AttemptInitialize = 1,
    NfcInitialized = 2,
};

struct ConnectionStatus {
    u32 status = 1;
    INSERT_PADDING_BYTES(48);
};
// static_assert(sizeof(ConnectionStatus) == 0x60, "ConnectionStatus structure has incorrect size");

struct Date {
    u16 year = 2016;
    u8 month = 1;
    u8 day = 1;
};

struct TagInfo {
    u8 uid[10];
    u8 uid_len;
    INSERT_PADDING_BYTES(21);
    u8 protocol;
    u8 tag_type;
    INSERT_PADDING_BYTES(50);
};
static_assert(sizeof(TagInfo) == 0x54, "TagInfo structure has incorrect size");

struct ApplicationAreaCreateInfo {
    u32 access_id;
    VAddr initial_data;
    u32 initial_data_size;
    INSERT_PADDING_BYTES(48);
};

struct RomInfo {
    u8 character_id[3];
    u8 series_id;
    u16 serial_number;
    u8 type;
    INSERT_PADDING_BYTES(47);
};

struct CommonInfo {
    Date last_write_data;
    u16 write_counter;
    u8 character_id[3];
    u8 series_id;
    u16 serial_number;
    u8 type;
    u8 version;
    u16 application_area_size;
    INSERT_PADDING_BYTES(48);
};
static_assert(sizeof(CommonInfo) == 0x40, "CommonInfo structure has incorrect size");

// struct RegisterInfo
struct AmiiboSettings {
    u8 owner_mii[0x60]; // TODO (mailwl): use mii struct
    u16 amiibo_nickname[0xB];
    u8 font_region;
    u8 country;
    u32 date;
    INSERT_PADDING_BYTES(0x2C);
};
static_assert(sizeof(AmiiboSettings) == 0xA8, "AmiiboSettings structure has incorrect size");

/**
 * NFC::SetClientVersion service function
 *  Inputs:
 *      0 : Header code []
 *      1 :
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */

/**
 * NFC::Initialize service function
 *  Inputs:
 *      0 : Header code [0x00010040]
 *      1 : (u8) unknown parameter. Can be either value 0x1 or 0x2
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void Initialize(Interface* self);

/**
 * NFC::Shutdown service function
 *  Inputs:
 *      0 : Header code [0x00020040]
 *      1 : (u8) unknown parameter
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void Finalize(Interface* self);

/**
 * NFC::StartCommunication service function
 *  Inputs:
 *      0 : Header code [0x00030000]
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void Connect(Interface* self);

void Disconnect(Interface* self);

/**
 * NFC::StartTagScanning service function
 *  Inputs:
 *      0 : Header code [0x00050040]
 *      1 : (u16) unknown. This is normally 0x0
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void StartDetection(Interface* self);

void StopDetection(Interface* self);

void Mount(Interface* self);

void Unmount(Interface* self);

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
