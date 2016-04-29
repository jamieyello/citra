// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"
#include "common/common_funcs.h"

#include "core/hle/applets/applet.h"
#include "core/hle/kernel/kernel.h"
#include "core/hle/kernel/shared_memory.h"
#include "core/hle/result.h"
#include "core/hle/service/apt/apt.h"

namespace HLE {
namespace Applets {

struct MiiConfig {
    u8  unk_000; // 1
    u8  unk_001; // 0
    u8  unk_002; // 0
    u8  unk_003; // 1
    u8  unk_004; // 1
    INSERT_PADDING_BYTES(3);
    u16 unk_008; // 0
    INSERT_PADDING_BYTES(0x8c - 0xA);
    u8  unk_08C; // 0
    INSERT_PADDING_BYTES(3);
    u16 unk_090; // -1
    INSERT_PADDING_BYTES(2);
    u32 unk_094; // 01010101
    u16 unk_098; // 0101
    u8  unk_09A[0x64]; // all 1
    u8  unk_0FE; // 1
    u8  unk_0FF; // 1
    u32 unk_100; // 0 or 0x13DE28CF
};

static_assert(sizeof(MiiConfig) == 0x104, "MiiConfig structure has incorrect size");
#define ASSERT_REG_POSITION(field_name, position) static_assert(offsetof(MiiConfig, field_name) == position, "Field "#field_name" has invalid position")
ASSERT_REG_POSITION(unk_004, 0x04);
ASSERT_REG_POSITION(unk_008, 0x08);
ASSERT_REG_POSITION(unk_08C, 0x8C);
ASSERT_REG_POSITION(unk_090, 0x90);
ASSERT_REG_POSITION(unk_094, 0x94);
ASSERT_REG_POSITION(unk_0FE, 0xFE);
#undef ASSERT_REG_POSITION

struct MiiResult {
    u32 result_code;
    u8  unk_04;
    INSERT_PADDING_BYTES(7);
    u8 name_0c[0x60];
    u8 unk_6c[0x16];
    INSERT_PADDING_BYTES(2);
};
static_assert(sizeof(MiiResult) == 0x84, "MiiConfig structure has incorrect size");
#define ASSERT_REG_POSITION(field_name, position) static_assert(offsetof(MiiResult, field_name) == position, "Field "#field_name" has invalid position")
ASSERT_REG_POSITION(unk_04, 0x04);
ASSERT_REG_POSITION(name_0c, 0x0c);
ASSERT_REG_POSITION(unk_6c, 0x6C);


#undef ASSERT_REG_POSITION

class MiiSelector final : public Applet {
public:
    MiiSelector(Service::APT::AppletId id);

    ResultCode ReceiveParameter(const Service::APT::MessageParameter& parameter) override;
    ResultCode StartImpl(const Service::APT::AppletStartupParameter& parameter) override;
    void Update() override;
    bool IsRunning() const override { return started; }

    /// TODO(Subv): Find out what this is actually used for.
    /// It is believed that the application stores the current screen image here.
    Kernel::SharedPtr<Kernel::SharedMemory> framebuffer_memory;

    /// Whether this applet is currently running instead of the host application or not.
    bool started;
};

}
} // namespace
