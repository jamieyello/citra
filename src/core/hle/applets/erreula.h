// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/applets/applet.h"
#include "core/hle/kernel/shared_memory.h"

namespace HLE {
namespace Applets {

class ErrEula final : public Applet {
public:
    ErrEula(Service::APT::AppletId id): Applet(id), started(false) { }

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
}
