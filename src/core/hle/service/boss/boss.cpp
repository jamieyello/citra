// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/kernel/event.h"
#include "core/hle/service/boss/boss.h"
#include "core/hle/service/boss/boss_p.h"
#include "core/hle/service/boss/boss_u.h"
#include "core/hle/service/service.h"

namespace Service {
namespace BOSS {

static u32 new_arrival_flag;
static u32 ns_data_new_flag;
static u32 optout_flag;
static Kernel::SharedPtr<Kernel::Event> new_arrival_event;

void InitializeSession(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u64 unk_param = ((u64)cmd_buff[1] | ((u64)cmd_buff[2] << 32));
    u32 translation = cmd_buff[3];

    if (translation != IPC::CallingPidDesc()) {
        cmd_buff[0] = IPC::MakeHeader(0, 0x1, 0); // 0x40
        cmd_buff[1] = ResultCode(ErrorDescription::OS_InvalidBufferDescriptor, ErrorModule::OS,
                                 ErrorSummary::WrongArgument, ErrorLevel::Permanent)
                          .raw;
        LOG_ERROR(Service_BOSS, "The translation was invalid, translation=0x%08X", translation);
        return;
    }

    cmd_buff[0] = IPC::MakeHeader(0x1, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param=0x%016llX, translation=0x%08X", unk_param,
                translation);
}

void RegisterStorage(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u64 extdata_id = ((u64)cmd_buff[1] | ((u64)cmd_buff[2] << 32));
    u32 boss_size = cmd_buff[3];
    u32 extdata_type = cmd_buff[4] & 0xFF;

    cmd_buff[0] = IPC::MakeHeader(0x2, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS,
                "(STUBBED) extdata_id=0x%08llX, boss_size=0x%08X, extdata_type=0x%08X", extdata_id,
                boss_size, extdata_type);
}

void UnregisterStorage(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[0] = IPC::MakeHeader(0x3, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "(STUBBED) called");
}

void GetStorageInfo(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[0] = IPC::MakeHeader(0x4, 0x2, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // boss_size, stub 0

    LOG_WARNING(Service_BOSS, "(STUBBED) called");
}

void RegisterPrivateRootCa(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x5, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) translation=0x%08X, buff_addr=0x%08X, buff_size=0x%08X",
                translation, buff_addr, buff_size);
}

void RegisterPrivateClientCert(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 translation1 = cmd_buff[3];
    u32 buff1_addr = cmd_buff[4];
    u32 buff1_size = (translation1 >> 4);
    u32 translation2 = cmd_buff[5];
    u32 buff2_addr = cmd_buff[6];
    u32 buff2_size = (translation2 >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x6, 0x1, 0x4);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff1_size << 4 | 0xA);
    cmd_buff[3] = buff1_addr;
    cmd_buff[2] = (buff2_size << 4 | 0xA);
    cmd_buff[3] = buff2_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, "
                              "translation1=0x%08X, buff1_addr=0x%08X, buff1_size=0x%08X, "
                              "translation2=0x%08X, buff2_addr=0x%08X, buff2_size=0x%08X",
                unk_param1, unk_param2, translation1, buff1_addr, buff1_size, translation2,
                buff2_addr, buff2_size);
}

void GetNewArrivalFlag(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[0] = IPC::MakeHeader(0x7, 0x2, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = new_arrival_flag;

    LOG_WARNING(Service_BOSS, "(STUBBED) new_arrival_flag=%u", new_arrival_flag);
}

void RegisterNewArrivalEvent(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 copy_handle_desc = cmd_buff[1];
    u32 event_handle = cmd_buff[2];
    new_arrival_event = Kernel::g_handle_table.Get<Kernel::Event>(event_handle);

    if (new_arrival_event) {
        new_arrival_event->name = "BOSS:new_arrival_event";
    }

    cmd_buff[0] = IPC::MakeHeader(0x8, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "(STUBBED) copy_handle_desc=0x%08X, event_handle=0x%08X",
                copy_handle_desc, event_handle);
}

void SetOptoutFlag(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    optout_flag = cmd_buff[1] & 0xFF;

    cmd_buff[0] = IPC::MakeHeader(0x9, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "optout_flag=%u", optout_flag);
}

void GetOptoutFlag(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[0] = IPC::MakeHeader(0xA, 0x2, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = optout_flag;

    LOG_WARNING(Service_BOSS, "output_flag=%u", optout_flag);
}

void RegisterTask(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 unk_param3 = cmd_buff[3] & 0xFF;
    u32 translation = cmd_buff[4];
    u32 buff_addr = cmd_buff[5];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0xB, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, unk_param3, translation, buff_addr, buff_size);
}

void UnregisterTask(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 translation = cmd_buff[3];
    u32 buff_addr = cmd_buff[4];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0xC, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, translation, buff_addr, buff_size);
}

void ReconfigureTask(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 translation = cmd_buff[3];
    u32 buff_addr = cmd_buff[4];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0xD, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, translation, buff_addr, buff_size);
}

void GetTaskIdList(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[0] = IPC::MakeHeader(0xE, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "(STUBBED) called");
}

void GetStepIdList(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0xF, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) translation=0x%08X, buff_addr=0x%08X, buff_size=0x%08X",
                translation, buff_addr, buff_size);
}

void GetNsDataIdList(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 unk_param3 = cmd_buff[3];
    u32 unk_param4 = cmd_buff[4];
    u32 translation = cmd_buff[5];
    u32 buff_addr = cmd_buff[6];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x10, 0x3, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (16 bit value)
    cmd_buff[3] = 0; // stub 0 (16 bit value)
    cmd_buff[4] = (buff_size << 4 | 0xC);
    cmd_buff[5] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "unk_param4=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, unk_param3, unk_param4, translation, buff_addr, buff_size);
}

void GetOwnNsDataIdList(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 unk_param3 = cmd_buff[3];
    u32 unk_param4 = cmd_buff[4];
    u32 translation = cmd_buff[5];
    u32 buff_addr = cmd_buff[6];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x11, 0x3, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (16 bit value)
    cmd_buff[3] = 0; // stub 0 (16 bit value)
    cmd_buff[4] = (buff_size << 4 | 0xC);
    cmd_buff[5] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "unk_param4=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, unk_param3, unk_param4, translation, buff_addr, buff_size);
}

void GetNewDataNsDataIdList(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 unk_param3 = cmd_buff[3];
    u32 unk_param4 = cmd_buff[4];
    u32 translation = cmd_buff[5];
    u32 buff_addr = cmd_buff[6];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x12, 0x3, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (16 bit value)
    cmd_buff[3] = 0; // stub 0 (16 bit value)
    cmd_buff[4] = (buff_size << 4 | 0xC);
    cmd_buff[5] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "unk_param4=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, unk_param3, unk_param4, translation, buff_addr, buff_size);
}

void GetOwnNewDataNsDataIdList(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 unk_param3 = cmd_buff[3];
    u32 unk_param4 = cmd_buff[4];
    u32 translation = cmd_buff[5];
    u32 buff_addr = cmd_buff[6];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x13, 0x3, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (16 bit value)
    cmd_buff[3] = 0; // stub 0 (16 bit value)
    cmd_buff[4] = (buff_size << 4 | 0xC);
    cmd_buff[5] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "unk_param4=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, unk_param3, unk_param4, translation, buff_addr, buff_size);
}

void SendProperty(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 translation = cmd_buff[3];
    u32 buff_addr = cmd_buff[4];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x14, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, translation, buff_addr, buff_size);
}

void SendPropertyHandle(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[2] & 0xFF;
    u32 translation = cmd_buff[3];
    u32 buff_addr = cmd_buff[4];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x15, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void ReceiveProperty(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 buff_size = cmd_buff[2];
    u32 translation = cmd_buff[3];
    u32 buff_addr = cmd_buff[4];

    cmd_buff[0] = IPC::MakeHeader(0x16, 0x2, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (32 bit value)
    cmd_buff[2] = (buff_size << 4 | 0xC);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, buff_size=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X",
                unk_param1, buff_size, translation, buff_addr);
}

void UpdateTaskInterval(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 translation = cmd_buff[3];
    u32 buff_addr = cmd_buff[4];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x17, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, translation, buff_addr, buff_size);
}

void UpdateTaskCount(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 buff_size = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2]; // TODO(JamePeng): Figure out the meaning of these parameters
    u32 translation = cmd_buff[3];
    u32 buff_addr = cmd_buff[4];

    cmd_buff[0] = IPC::MakeHeader(0x18, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) buff_size=0x%08X, unk_param2=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X",
                buff_size, unk_param2, translation, buff_addr);
}

void GetTaskInterval(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unk_param1 = cmd_buff[1]; // TODO(JamePeng): Figure out the meaning of these parameters
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x19, 0x2, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 ( 32bit value)
    cmd_buff[3] = (buff_size << 4 | 0xA);
    cmd_buff[4] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void GetTaskCount(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unk_param1 = cmd_buff[1]; // TODO(JamePeng): Figure out the meaning of these parameters
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x1A, 0x2, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 ( 32bit value)
    cmd_buff[3] = (buff_size << 4 | 0xA);
    cmd_buff[4] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void GetTaskServiceStatus(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unk_param1 = cmd_buff[1]; // TODO(JamePeng): Figure out the meaning of these parameters
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x1B, 0x2, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 ( 8bit value)
    cmd_buff[3] = (buff_size << 4 | 0xA);
    cmd_buff[4] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void StartTask(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unk_param1 = cmd_buff[1]; // TODO(JamePeng): Figure out the meaning of these parameters
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x1C, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void StartTaskImmediate(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unk_param1 = cmd_buff[1]; // TODO(JamePeng): Figure out the meaning of these parameters
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x1D, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void CancelTask(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x1E, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void GetTaskFinishHandle(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[0] = IPC::MakeHeader(0x1F, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0;
    cmd_buff[3] = 0; // stub 0(This should be a handle of task_finish ?)

    LOG_WARNING(Service_BOSS, "(STUBBED) called");
}

void GetTaskState(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 buff_size = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 translation = cmd_buff[3];
    u32 buff_addr = cmd_buff[4];

    cmd_buff[0] = IPC::MakeHeader(0x20, 0x4, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (8 bit value)
    cmd_buff[3] = 0; // stub 0 (32 bit value)
    cmd_buff[4] = 0; // stub 0 (8 bit value)
    cmd_buff[5] = (buff_size << 4 | 0xA);
    cmd_buff[6] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) buff_size=0x%08X, unk_param2=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X",
                buff_size, unk_param2, translation, buff_addr);
}

void GetTaskResult(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x21, 0x4, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (8 bit value)
    cmd_buff[3] = 0; // stub 0 (32 bit value)
    cmd_buff[4] = 0; // stub 0 (8 bit value)
    cmd_buff[5] = (buff_size << 4 | 0xA);
    cmd_buff[6] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void GetTaskCommErrorCode(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x22, 0x4, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (32 bit value)
    cmd_buff[3] = 0; // stub 0 (32 bit value)
    cmd_buff[4] = 0; // stub 0 (8 bit value)
    cmd_buff[5] = (buff_size << 4 | 0xA);
    cmd_buff[6] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void GetTaskStatus(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 unk_param3 = cmd_buff[3] & 0xFF;
    u32 translation = cmd_buff[4];
    u32 buff_addr = cmd_buff[5];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x23, 0x2, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (8 bit value)
    cmd_buff[3] = (buff_size << 4 | 0xA);
    cmd_buff[4] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, unk_param3, translation, buff_addr, buff_size);
}

void GetTaskError(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 translation = cmd_buff[4];
    u32 buff_addr = cmd_buff[5];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x24, 0x2, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (8 bit value)
    cmd_buff[3] = (buff_size << 4 | 0xA);
    cmd_buff[4] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, translation, buff_addr, buff_size);
}

void GetTaskInfo(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 translation = cmd_buff[4];
    u32 buff_addr = cmd_buff[5];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x25, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, translation, buff_addr, buff_size);
}

void DeleteNsData(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];

    cmd_buff[0] = IPC::MakeHeader(0x26, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X", unk_param1);
}

void GetNsDataHeaderInfo(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 unk_param3 = cmd_buff[3];
    u32 translation = cmd_buff[4];
    u32 buff_addr = cmd_buff[5];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x27, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xC);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, unk_param3, translation, buff_addr, buff_size);
}

void ReadNsData(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 unk_param3 = cmd_buff[3];
    u32 unk_param4 = cmd_buff[4];
    u32 translation = cmd_buff[5];
    u32 buff_addr = cmd_buff[6];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x28, 0x3, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (32bit value)
    cmd_buff[3] = 0; // stub 0 (32bit value)
    cmd_buff[4] = (buff_size << 4 | 0xC);
    cmd_buff[5] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "unk_param4=0x%08X, translation=0x%08X, "
                              "buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, unk_param3, unk_param4, translation, buff_addr, buff_size);
}

void SetNsDataAdditionalInfo(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];

    cmd_buff[0] = IPC::MakeHeader(0x29, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X", unk_param1,
                unk_param2);
}

void GetNsDataAdditionalInfo(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];

    cmd_buff[0] = IPC::MakeHeader(0x2A, 0x2, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (32bit value)

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X", unk_param1);
}

void SetNsDataNewFlag(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    ns_data_new_flag = cmd_buff[2] & 0xFF;

    cmd_buff[0] = IPC::MakeHeader(0x2B, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, ns_data_new_flag=0x%08X", unk_param1,
                ns_data_new_flag);
}

void GetNsDataNewFlag(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];

    cmd_buff[0] = IPC::MakeHeader(0x2C, 0x2, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = ns_data_new_flag;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, ns_data_new_flag=0x%08X", unk_param1,
                ns_data_new_flag);
}

void GetNsDataLastUpdate(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];

    cmd_buff[0] = IPC::MakeHeader(0x2D, 0x3, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (32bit value)
    cmd_buff[3] = 0; // stub 0 (32bit value)

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X", unk_param1);
}

void GetErrorCode(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];

    cmd_buff[0] = IPC::MakeHeader(0x2E, 0x2, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (32bit value)

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X", unk_param1);
}

void RegisterStorageEntry(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 unk_param3 = cmd_buff[3];
    u32 unk_param4 = cmd_buff[4];
    u32 unk_param5 = cmd_buff[5] & 0xFF;

    cmd_buff[0] = IPC::MakeHeader(0x2F, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "(STUBBED)  unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "unk_param4=0x%08X, unk_param5=0x%08X",
                unk_param1, unk_param2, unk_param3, unk_param4, unk_param5);
}

void GetStorageEntryInfo(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[0] = IPC::MakeHeader(0x30, 0x3, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (32bit value)
    cmd_buff[3] = 0; // stub 0 (16bit value)

    LOG_WARNING(Service_BOSS, "(STUBBED) called");
}

void SetStorageOption(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1] & 0xFF;
    u32 unk_param2 = cmd_buff[2];
    u32 unk_param3 = cmd_buff[3];
    u32 unk_param4 = cmd_buff[4];

    cmd_buff[0] = IPC::MakeHeader(0x31, 0x1, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;

    LOG_WARNING(Service_BOSS, "(STUBBED)  unk_param1=0x%08X, unk_param2=0x%08X, "
                              "unk_param3=0x%08X, unk_param4=0x%08X",
                unk_param1, unk_param2, unk_param3, unk_param4);
}

void GetStorageOption(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[0] = IPC::MakeHeader(0x32, 0x5, 0);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (32bit value)
    cmd_buff[3] = 0; // stub 0 (8bit value)
    cmd_buff[4] = 0; // stub 0 (16bit value)
    cmd_buff[5] = 0; // stub 0 (16bit value)

    LOG_WARNING(Service_BOSS, "(STUBBED) called");
}

void StartBgImmediate(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unk_param1 = cmd_buff[1]; // TODO(JamePeng): Figure out the meaning of these parameters
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x33, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff_size << 4 | 0xA);
    cmd_buff[3] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) buff_size=0x%08X, unk_param2=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void GetTaskActivePriority(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 unk_param1 = cmd_buff[1]; // TODO(JamePeng): Figure out the meaning of these parameters
    u32 translation = cmd_buff[2];
    u32 buff_addr = cmd_buff[3];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x34, 0x2, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = 0; // stub 0 (8bit value)
    cmd_buff[3] = (buff_size << 4 | 0xA);
    cmd_buff[4] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) buff_size=0x%08X, unk_param2=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X",
                unk_param1, translation, buff_addr, buff_size);
}

void RegisterImmediateTask(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2] & 0xFF;
    u32 unk_param3 = cmd_buff[3] & 0xFF;
    u32 translation = cmd_buff[4];
    u32 buff_addr = cmd_buff[5];
    u32 buff_size = (translation >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x35, 0x1, 0x2);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[3] = (buff_size << 4 | 0xA);
    cmd_buff[4] = buff_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, unk_param3=0x%08X, "
                              "translation=0x%08X, buff_addr=0x%08X, buff_size=0x%08X",
                unk_param1, unk_param2, unk_param3, translation, buff_addr, buff_size);
}

void SetTaskQuery(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 translation1 = cmd_buff[3];
    u32 buff1_addr = cmd_buff[4];
    u32 buff1_size = (translation1 >> 4);
    u32 translation2 = cmd_buff[5];
    u32 buff2_addr = cmd_buff[6];
    u32 buff2_size = (translation2 >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x36, 0x1, 0x4);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff1_size << 4 | 0xA);
    cmd_buff[3] = buff1_addr;
    cmd_buff[2] = (buff2_size << 4 | 0xA);
    cmd_buff[3] = buff2_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, "
                              "translation1=0x%08X, buff1_addr=0x%08X, buff1_size=0x%08X, "
                              "translation2=0x%08X, buff2_addr=0x%08X, buff2_size=0x%08X",
                unk_param1, unk_param2, translation1, buff1_addr, buff1_size, translation2,
                buff2_addr, buff2_size);
}

void GetTaskQuery(Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();
    // TODO(JamePeng): Figure out the meaning of these parameters
    u32 unk_param1 = cmd_buff[1];
    u32 unk_param2 = cmd_buff[2];
    u32 translation1 = cmd_buff[3];
    u32 buff1_addr = cmd_buff[4];
    u32 buff1_size = (translation1 >> 4);
    u32 translation2 = cmd_buff[5];
    u32 buff2_addr = cmd_buff[6];
    u32 buff2_size = (translation2 >> 4);

    cmd_buff[0] = IPC::MakeHeader(0x37, 0x1, 0x4);
    cmd_buff[1] = RESULT_SUCCESS.raw;
    cmd_buff[2] = (buff1_size << 4 | 0xA);
    cmd_buff[3] = buff1_addr;
    cmd_buff[2] = (buff2_size << 4 | 0xC);
    cmd_buff[3] = buff2_addr;

    LOG_WARNING(Service_BOSS, "(STUBBED) unk_param1=0x%08X, unk_param2=0x%08X, "
                              "translation1=0x%08X, buff1_addr=0x%08X, buff1_size=0x%08X, "
                              "translation2=0x%08X, buff2_addr=0x%08X, buff2_size=0x%08X",
                unk_param1, unk_param2, translation1, buff1_addr, buff1_size, translation2,
                buff2_addr, buff2_size);
}

void Init() {
    using namespace Kernel;

    AddService(new BOSS_P_Interface);
    AddService(new BOSS_U_Interface);

    new_arrival_event = nullptr;
    new_arrival_flag = 0;
    ns_data_new_flag = 0;
    optout_flag = 0;
}

void Shutdown() {
    new_arrival_event = nullptr;
}

} // namespace BOSS

} // namespace Service
