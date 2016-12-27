// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/common_types.h"
#include "common/logging/log.h"
#include "core/hle/service/spi/spi.h"
#include "core/hle/service/spi/spi_cd2.h"
#include "core/hle/service/spi/spi_nor.h"

namespace Service {
namespace SPI {

void Init() {
    AddService(new SPI_CD2);
    AddService(new SPI_NOR);
}

} // namespace SPI
} // namespace Service
