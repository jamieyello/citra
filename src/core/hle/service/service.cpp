// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <boost/range/algorithm_ext/erase.hpp>

#include "common/logging/log.h"
#include "common/string_util.h"
#include "core/arm/arm_interface.h"
#include "core/core.h"
#include "core/hle/kernel/server_port.h"
#include "core/hle/service/ac_u.h"
#include "core/hle/service/act/act.h"
#include "core/hle/service/am/am.h"
#include "core/hle/service/apt/apt.h"
#include "core/hle/service/boss/boss.h"
#include "core/hle/service/cam/cam.h"
#include "core/hle/service/cdc_csn.h"
#include "core/hle/service/cdc_dsp.h"
#include "core/hle/service/cdc_mic.h"
#include "core/hle/service/cecd/cecd.h"
#include "core/hle/service/cfg/cfg.h"
#include "core/hle/service/csnd_snd.h"
#include "core/hle/service/dlp/dlp.h"
#include "core/hle/service/dsp_dsp.h"
#include "core/hle/service/err_f.h"
#include "core/hle/service/frd/frd.h"
#include "core/hle/service/fs/archive.h"
#include "core/hle/service/gpio_cdc.h"
#include "core/hle/service/gpio_ir.h"
#include "core/hle/service/gpio_mcu.h"
#include "core/hle/service/gsp_gpu.h"
#include "core/hle/service/gsp_lcd.h"
#include "core/hle/service/hid/hid.h"
#include "core/hle/service/hostio.h"
#include "core/hle/service/http_c.h"
#include "core/hle/service/i2c_cam.h"
#include "core/hle/service/i2c_ir.h"
#include "core/hle/service/i2c_lcd.h"
#include "core/hle/service/i2c_mcu.h"
#include "core/hle/service/ir/ir.h"
#include "core/hle/service/ldr_ro/ldr_ro.h"
#include "core/hle/service/mcu_cam.h"
#include "core/hle/service/mcu_cdc.h"
#include "core/hle/service/mcu_gpu.h"
#include "core/hle/service/mcu_pls.h"
#include "core/hle/service/mcu_rtc.h"
#include "core/hle/service/mic_u.h"
#include "core/hle/service/mvd/mvd.h"
#include "core/hle/service/ndm/ndm.h"
#include "core/hle/service/news/news.h"
#include "core/hle/service/nfc/nfc.h"
#include "core/hle/service/nim/nim.h"
#include "core/hle/service/ns_s.h"
#include "core/hle/service/nwm/nwm.h"
#include "core/hle/service/pdn_c.h"
#include "core/hle/service/pdn_d.h"
#include "core/hle/service/pdn_g.h"
#include "core/hle/service/pdn_i.h"
#include "core/hle/service/pdn_s.h"
#include "core/hle/service/pm_app.h"
#include "core/hle/service/ps_ps.h"
#include "core/hle/service/ptm/ptm.h"
#include "core/hle/service/pxi_am9.h"
#include "core/hle/service/pxi_mc.h"
#include "core/hle/service/pxi_ps9.h"
#include "core/hle/service/pxi_dev.h"
#include "core/hle/service/qtm/qtm.h"
#include "core/hle/service/service.h"
#include "core/hle/service/soc_p.h"
#include "core/hle/service/soc_u.h"
#include "core/hle/service/spi/spi.h"
#include "core/hle/service/srv.h"
#include "core/hle/service/srv_pm.h"
#include "core/hle/service/ssl_c.h"
#include "core/hle/service/y2r_u.h"

namespace Service {

std::unordered_map<std::string, Kernel::SharedPtr<Kernel::ClientPort>> g_kernel_named_ports;
std::unordered_map<std::string, Kernel::SharedPtr<Kernel::ClientPort>> g_srv_services;

/**
 * Creates a function string for logging, complete with the name (or header code, depending
 * on what's passed in) the port name, and all the cmd_buff arguments.
 */
static std::string MakeFunctionString(const char* name, const char* port_name,
                                      const u32* cmd_buff) {
    // Number of params == bits 0-5 + bits 6-11
    int num_params = (cmd_buff[0] & 0x3F) + ((cmd_buff[0] >> 6) & 0x3F);

    std::string function_string =
        Common::StringFromFormat("function '%s': port=%s", name, port_name);
    for (int i = 1; i <= num_params; ++i) {
        function_string += Common::StringFromFormat(", cmd_buff[%i]=0x%X", i, cmd_buff[i]);
    }
    return function_string;
}

void SessionRequestHandler::ClientConnected(
    Kernel::SharedPtr<Kernel::ServerSession> server_session) {
    connected_sessions.push_back(server_session);
}

void SessionRequestHandler::ClientDisconnected(
    Kernel::SharedPtr<Kernel::ServerSession> server_session) {
    boost::range::remove_erase(connected_sessions, server_session);
}

Interface::Interface(u32 max_sessions) : max_sessions(max_sessions) {}
Interface::~Interface() = default;

void Interface::HandleSyncRequest(Kernel::SharedPtr<Kernel::ServerSession> server_session) {
    // TODO(Subv): Make use of the server_session in the HLE service handlers to distinguish which
    // session triggered each command.

    u32* cmd_buff = Kernel::GetCommandBuffer();
    auto itr = m_functions.find(cmd_buff[0]);

    u32 lr = Core::CPU().GetReg(14);
    if (itr == m_functions.end() || itr->second.func == nullptr) {
        std::string function_name = (itr == m_functions.end())
                                        ? Common::StringFromFormat("0x%08X", cmd_buff[0])
                                        : itr->second.name;
        LOG_ERROR(
            Service, "lr: 0x%08X, unknown / unimplemented %s", lr,
            MakeFunctionString(function_name.c_str(), GetPortName().c_str(), cmd_buff).c_str());

        // TODO(bunnei): Hack - ignore error
        cmd_buff[1] = 0;
        return;
    }
    if (strcmp("TriggerCmdReqQueue", itr->second.name)) {
        if (strcmp("FlushDataCache", itr->second.name)) {
            if (strcmp("GetHeadphoneStatus", itr->second.name)) {
                if (strcmp("ConvertProcessAddressFromDspDram", itr->second.name)) {
                    LOG_DEBUG(Service, "lr: 0x%08X, %s", lr,
                              MakeFunctionString(itr->second.name, GetPortName().c_str(), cmd_buff)
                                  .c_str());
                }
            }
        }
    }

    itr->second.func(this);
}

void Interface::Register(const FunctionInfo* functions, size_t n) {
    m_functions.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        // Usually this array is sorted by id already, so hint to instead at the end
        m_functions.emplace_hint(m_functions.cend(), functions[i].id, functions[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Module interface

static void AddNamedPort(Interface* interface_) {
    auto ports =
        Kernel::ServerPort::CreatePortPair(interface_->GetMaxSessions(), interface_->GetPortName(),
                                           std::shared_ptr<Interface>(interface_));
    auto client_port = std::get<Kernel::SharedPtr<Kernel::ClientPort>>(ports);
    g_kernel_named_ports.emplace(interface_->GetPortName(), std::move(client_port));
}

void AddService(Interface* interface_) {
    auto ports =
        Kernel::ServerPort::CreatePortPair(interface_->GetMaxSessions(), interface_->GetPortName(),
                                           std::shared_ptr<Interface>(interface_));
    auto client_port = std::get<Kernel::SharedPtr<Kernel::ClientPort>>(ports);
    g_srv_services.emplace(interface_->GetPortName(), std::move(client_port));
}

/// Initialize ServiceManager
void Init() {
    AddNamedPort(new SRV::SRV);
    AddNamedPort(new ERR::ERR_F);

    AddNamedPort(new HOSTIO::HOSTIO0);
    AddNamedPort(new HOSTIO::HOSTIO1);
    AddNamedPort(new HOSTIO::HioFIO);

    FS::ArchiveInit();
    ACT::Init();
    AM::Init();
    APT::Init();
    BOSS::Init();
    CAM::Init();
    CECD::Init();
    CFG::Init();
    DLP::Init();
    FRD::Init();
    HID::Init();
    IR::Init();
    MVD::Init();
    NDM::Init();
    NEWS::Init();
    NFC::Init();
    NIM::Init();
    NWM::Init();
    PTM::Init();
    QTM::Init();
    SPI::Init();

    AddService(new AC::AC_U);
    AddService(new CSND::CSND_SND);
    AddService(new CDC::CDC_CSN);
    AddService(new CDC::CDC_DSP);
    AddService(new CDC::CDC_MIC);
    AddService(new DSP_DSP::Interface);
    AddService(new GPIO::GPIO_CDC);
    AddService(new GPIO::GPIO_IR);
    AddService(new GPIO::GPIO_MCU);
    AddService(new GSP::GSP_GPU);
    AddService(new GSP::GSP_LCD);
    AddService(new HTTP::HTTP_C);
    AddService(new I2C::I2C_CAM);
    AddService(new I2C::I2C_IR);
    AddService(new I2C::I2C_LCD);
    AddService(new I2C::I2C_MCU);
    AddService(new LDR::LDR_RO);
    AddService(new MCU::MCU_CAM);
    AddService(new MCU::MCU_CDC);
    AddService(new MCU::MCU_GPU);
    AddService(new MCU::MCU_PLS);
    AddService(new MCU::MCU_RTC);
    AddService(new MIC::MIC_U);
    AddService(new NS::NS_S);
    AddService(new PDN::PDN_C);
    AddService(new PDN::PDN_D);
    AddService(new PDN::PDN_G);
    AddService(new PDN::PDN_I);
    AddService(new PDN::PDN_S);
    AddService(new PM::PM_APP);
    AddService(new PS::PS_PS);
    AddService(new PXI::PXI_AM9);
    AddService(new PXI::PXI_MC);
    AddService(new PXI::PXI_PS9);
    AddService(new SOC::SOC_P);
    AddService(new PXI::PXI_DEV);
    AddService(new SOC::SOC_U);
    AddService(new SRV::SRV_PM);
    AddService(new SSL::SSL_C);
    AddService(new Y2R::Y2R_U);

    LOG_DEBUG(Service, "initialized OK");
}

/// Shutdown ServiceManager
void Shutdown() {
    PTM::Shutdown();
    NIM::Shutdown();
    NEWS::Shutdown();
    NDM::Shutdown();
    IR::Shutdown();
    HID::Shutdown();
    FRD::Shutdown();
    DLP::Shutdown();
    CFG::Shutdown();
    CECD::Shutdown();
    CAM::Shutdown();
    BOSS::Shutdown();
    APT::Shutdown();
    AM::Shutdown();
    FS::ArchiveShutdown();

    g_srv_services.clear();
    g_kernel_named_ports.clear();
    LOG_DEBUG(Service, "shutdown OK");
}
}
