// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"

namespace Service {

class Interface;

namespace IR {

enum class ConnectionStatus : u8 {
    Stopped,
    TryingToConnect,
    Connected,
    Disconnected,
    FatalError,
};

enum class ConnectionRole : u8 {
    None,
    Require,
    Wait,
};

enum class BaudRate {
    BaudRate_115200 = 3,
    BaudRate_96000 = 4,
    BaudRate_72000 = 5,
    BaudRate_48000 = 6,
    BaudRate_36000 = 7,
    BaudRate_24000 = 8,
    BaudRate_18000 = 9,
    BaudRate_12000 = 10,
    BaudRate_9600 = 11,
    BaudRate_6000 = 12,
    BaudRate_3000 = 13,
    BaudRate_57600 = 14,
    BaudRate_38400 = 15,
    BaudRate_19200 = 16,
    BaudRate_7200 = 17,
    BaudRate_4800 = 18,
};

struct ConnectionInfo {
    u32 latest_recv_error;              // 0x00
    u32 latest_send_error;              // 0x04
    ConnectionStatus connection_status; // 0x08
    u8 unk_09;                          // 0x09
    ConnectionRole connection_role;     // 0x0A
    u8 own_machine_id;                  // 0x0B
    u8 unk_0C;                          // 0x0C
    u8 unk_0D;                          // 0x0D
    bool unk_0E;                        // 0x0E, must be true
    u8 unk_0F;                          // 0x0F
};

struct StructHead {
    u32 position;
    u32 size;
};

struct TransInfo {
    u32 read_idx;
    u32 write_idx;
    u64 count;
};

struct TransferMemory {             // extraPadWorkingMemory
    ConnectionInfo connection_info; // 0x00-0x0F
    TransInfo trans_info;           // 0x10
    StructHead struct_head;         // 0x20
    u8 head[0x4A];                  // 0x28 size = 0x4A
};

/**
 * IR_RST::GetHandles service function
 *  Inputs:
 *      0 : 0x00010000
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Translate header, used by the ARM11-kernel
 *      3 : Shared memory handle
 *      4 : Event handle
 */
void GetHandles(Interface* self);

/**
 * IR::FinalizeIrNop service function
 *  Inputs:
 *      0 : 0x00020000
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void FinalizeIrNop(Interface* self);

/**
 * IR::ClearReceiveBuffer service function
 *  Inputs:
 *      0 : 0x00030000
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void ClearReceiveBuffer(Interface* self);

/**
* IR::ClearSendBuffer service function
*  Inputs:
*      0 : 0x00040000
*  Outputs:
*      1 : Result of function, 0 on success, otherwise error code
*/
void ClearSendBuffer(Interface* self);

/**
 * IR::WaitConnection service function
 *  Inputs:
 *      0 : 0x000500C0
 *      1 : unknown (u8)
 *      2-3 : Timeout
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void WaitConnection(Interface* self);

/**
 * IR::RequireConnection service function
 *  Inputs:
 *      0 : 0x00060040
 *      1 : unknown (u8), looks like always 1
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void RequireConnection(Interface* self);

/**
 * IR::RequireConnection service function
 *  Inputs:
 *      0 : 0x000702C0
 *      1 : unknown (u8)
 *      2-3 : Timeout 1 (u64)
 *      4-5 : Timeout 2 (u64)
 *      6-7 : Timeout 3 (u64)
 *      8-9 : Timeout 4 (u64)
 *      10-11 : Timeout 5 (u64)
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void AutoConnection(Interface* self);

/**
 * IR::Disconnect service function
 *  Inputs:
 *      0 : 0x00090000
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void Disconnect(Interface* self);

/**
 * IR::GetReceiveEvent service function
 *  Inputs:
 *      0 : 0x000A0000
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      3 : Receive Status Event handle
 */
void GetReceiveEvent(Interface* self);

/**
 * IR::GetSendEvent service function
 *  Inputs:
 *      0 : 0x000B0000
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      3 : Connection Status Event handle
 */
void GetSendEvent(Interface* self);

/**
 * IR::GetConnectionStatusEvent service function
 *  Inputs:
 *      0 : 0x000C0000
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      3 : Connection Status Event handle
 */
void GetConnectionStatusEvent(Interface* self);

/* IR::SendIrNop service function
 *  Inputs:
 *      0 : 0x000D0042
 *      1 : Size
 *      2 : (Size << 14 | 2)
 *      3 : Buffer
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void SendIrNop(Interface* self);

/* IR::ReceiveIrnop service function
 *  Inputs:
 *      0 : 0x000F0040
 *      1 : Size
 *      64 : (Size << 14 | 2)
 *      65 : Buffer
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void ReceiveIrnop(Interface* self);

/* IR::GetLatestReceiveErrorResult service function
 *  Inputs:
 *      0 : 0x00110040
 *      1 : (bool) clear error
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Latest receive error
 */
void GetLatestReceiveErrorResult(Interface* self);

/* IR::GetLatestSendErrorResult service function
 *  Inputs:
 *      0 : 0x00120040
 *      1 : (bool) clear error
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Latest send error
 */
void GetLatestSendErrorResult(Interface* self);

/**
 * IR::GetConnectionStatus service function
 *  Inputs:
 *      0 : 0x00130000
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Connection Status
 */
void GetConnectionStatus(Interface* self);

/**
 * IR::GetConnectionRole service function
 *  Inputs:
 *      0 : 0x00170000
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Connection Status
 */
void GetConnectionRole(Interface* self);

/**
 * IR::InitializeIrNopShared service function
 *  Inputs:
 *      0 : 0x00180182
 *      1 : Size of transfer buffer
 *      2 : Recv buffer size
 *      3 : unknown
 *      4 : Send buffer size
 *      5 : unknown
 *      6 : BaudRate (u8)
 *      7 : Descriptor: Handle
 *      8 : Handle of transfer shared memory
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void InitializeIrNopShared(Interface* self);

/* IR::ReleaseReceivedData service function
 *  Inputs:
 *      0 : 0x00190040
 *      1 : Unknown (u32)
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void ReleaseReceivedData(Interface* self);

/// Initialize IR service
void Init();

/// Shutdown IR service
void Shutdown();

} // namespace IR
} // namespace Service
