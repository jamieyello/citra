// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "audio_core/mike.h"

namespace AudioCore {

class NullMike final : public Mike {
public:
    ~NullMike() override = default;
};

} // namespace
