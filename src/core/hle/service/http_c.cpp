// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/http_c.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace HTTP_C

namespace HTTP_C {

enum class RequestMethod : u8 {
    Get = 1,
    Post = 2,
    Head = 3,
    Put = 4,
    Delete = 5,
};

static u32 connection_id = 0;
static bool use_default_proxy = false;

static std::vector<std::vector<u8>> root_ca;

/**
 * HTTP_C::Initialize service function
 *  Inputs:
 *      1 : Buffer size
 *      2 : ProcessId Header
 *      4 : Copy handle header
 *      5 : Shared Memory handle for post data
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
static void Initialize(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 size = cmd_buff[1];
    Handle mem_handle = cmd_buff[5];
    if (mem_handle) {
        LOG_WARNING(Service_HTTP, "got memory for post");
    }

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_HTTP, "(STUBBED) called, size=%u", size);
}

/**
 * HTTP_C::Finalize service function
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
static void Finalize(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_HTTP, "(STUBBED) called");
}

/**
 * HTTP_C::CreateConnection service function
 *  Inputs:
 *      1 : Url size
 *      2 : Request Method
 *      4 : Url buffer
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Connection Id
 */
static void CreateConnection(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 size = cmd_buff[1];
    RequestMethod method = static_cast<RequestMethod>(cmd_buff[2] & 0xFF);
    VAddr url_buffer = cmd_buff[4];
    std::string url = Memory::ReadCString(url_buffer, size);

    connection_id = 0x1234;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    cmd_buff[2] = connection_id;
    LOG_WARNING(Service_HTTP, "(STUBBED) called, RequestMethod=%hhu, URL=%s", method, url.c_str());
}

/**
 * HTTP_C::DestroyConnection service function
 *  Inputs:
 *      1 : Connection Id
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
static void DestroyConnection(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 conn_id = cmd_buff[1];

    connection_id = 0;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_HTTP, "(STUBBED) called, conn_id=0x%X", conn_id);
}

/**
 * HTTP_C::SetRootCA service function
 *  Inputs:
 *      1 : Connection Id
 *      2 : Cert size
 *      4 : Cert buffer
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
static void SetRootCA(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 conn_id = cmd_buff[1];
    u32 cert_size = cmd_buff[2];
    VAddr cert_buff = cmd_buff[4];

    std::vector<u8> cert;
    cert.reserve(cert_size);
    Memory::ReadBlock(cert_buff, cert.data(), cert_size);

    root_ca.push_back(cert);

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_HTTP, "(STUBBED) called, conn_id=0x%X, size=0x%X, address=0x%08X", conn_id,
                cert_size, cert_buff);
}

/**
 * HTTP_C::SetProxyDefault service function
 *  Inputs:
 *      1 : Connection Id
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
static void SetProxyDefault(Service::Interface* self) {
    u32* cmd_buff = Kernel::GetCommandBuffer();

    u32 conn_id = cmd_buff[1];
    use_default_proxy = true;

    cmd_buff[1] = RESULT_SUCCESS.raw; // No error
    LOG_WARNING(Service_HTTP, "(STUBBED) called, conn_id=0x%X", conn_id);
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x00010044, Initialize, "InitializeGeneralSession"},
    {0x00020082, CreateConnection, "CreateConnection"},
    {0x00030040, DestroyConnection, "DestroyConnection"},
    {0x00040040, nullptr, "CancelConnection"},
    {0x00050040, nullptr, "GetConnectionState"},
    {0x00060040, nullptr, "GetConnectionProgress"},
    {0x00070040, nullptr, "GetConnectionError"},
    {0x00080042, nullptr, "InitializeConnectionSession"},
    {0x00090040, nullptr, "StartConnection"},
    {0x000A0040, nullptr, "StartConnectionAsync"},
    {0x000B0082, nullptr, "ReadBody"},
    {0x000C0102, nullptr, "ReadBodyWithTimeout"},
    {0x000D0146, nullptr, "SetProxy"},
    {0x000E0040, SetProxyDefault, "SetProxyDefault"},
    {0x000F00C4, nullptr, "SetBasicAuthorization"},
    {0x00100080, nullptr, "SetSocketBufferSize"},
    {0x001100C4, nullptr, "AddHeaderField"},
    {0x001200C4, nullptr, "AddPostDataAscii"},
    {0x001300C4, nullptr, "AddPostDataBinary"},
    {0x00140082, nullptr, "AddPostDataRaw"},
    {0x00150080, nullptr, "SetLazyPostDataSetting"},
    {0x001600C4, nullptr, "SendPostDataAscii"},
    {0x00170144, nullptr, "SendPostDataAsciiWithTimeout"},
    {0x001800C4, nullptr, "SendPostDataBinary"},
    {0x00190144, nullptr, "SendPostDataBinaryWithTimeout"},
    {0x001A0082, nullptr, "SendPostDataRaw"},
    {0x001B0102, nullptr, "SendPostDataRawWithTimeout"},
    {0x001C0080, nullptr, "SetPostDataEncoding"},
    {0x001D0040, nullptr, "NotifyFinishSendPostData"},
    {0x001E00C4, nullptr, "GetHeaderField"},
    {0x001F0144, nullptr, "GetHeaderFieldWithTimeout"},
    {0x00200082, nullptr, "GetHeaderAll"},
    {0x00210102, nullptr, "GetHeaderAllWithTimeout"},
    {0x00220040, nullptr, "GetResultCode"},
    {0x002300C0, nullptr, "GetResultCodeWithTimeout"},
    {0x00240082, SetRootCA, "SetRootCA"},
    {0x00250080, nullptr, "SetInternalRootCA"},
    {0x00260080, nullptr, "SetRootCaStore"},
    {0x002700C4, nullptr, "SetClientCert"},
    {0x00280080, nullptr, "SetInternalClientCert"},
    {0x00290080, nullptr, "SetClientCertId"},
    {0x002A0040, nullptr, "GetConnectionSslError"},
    {0x002B0080, nullptr, "SetVerifyOption"},
    {0x002C0080, nullptr, "DisableVerifyOptionForDebug"},
    {0x002D0000, nullptr, "CreateCertStore"},
    {0x002E0040, nullptr, "DestroyCertStore"},
    {0x002F0082, nullptr, "AddCertToStore"},
    {0x00300080, nullptr, "AddInternalCertToStore"},
    {0x00310080, nullptr, "RemoveCertFromCertStore"},
    {0x00320084, nullptr, "CreateClientCert"},
    {0x00330040, nullptr, "CreateInternalClientCert"},
    {0x00340040, nullptr, "DestroyClientCert"},
    {0x00350186, nullptr, "SetDefaultProxy"},
    {0x00360000, nullptr, "ClearDnsCaches"},
    {0x00370080, nullptr, "SetKeepAliveAvailability"},
    {0x003800C0, nullptr, "SetLazyPostDataSettingWithSize"},
    {0x00390000, Finalize, "FinalizeClient"},
    {0x003A0080, nullptr, "SetKeepAliveMode"},
    {0x003B0082, nullptr, "SetCrl"},
    {0x003C0080, nullptr, "SetInternalCrl"},
    {0x003D0080, nullptr, "SetCrlStore"},
    {0x003E0000, nullptr, "CreateCrlStore"},
    {0x003F0040, nullptr, "DestroyCrlStore"},
    {0x00400082, nullptr, "AddCrlToCrlStore"},
    {0x00410080, nullptr, "AddInternalCrlToCrlStore"},
    {0x00420080, nullptr, "RemoveCrlFromCrlStore"},
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface class

Interface::Interface() {
    Register(FunctionTable);
}

Interface::~Interface() {
    Register(FunctionTable);
}

} // namespace
