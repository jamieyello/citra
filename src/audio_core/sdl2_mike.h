// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include "audio_core/mike.h"

namespace AudioCore {

class SDL2Mike final : public Mike {
public:
    SDL2Mike();
    ~SDL2Mike() override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // namespace
