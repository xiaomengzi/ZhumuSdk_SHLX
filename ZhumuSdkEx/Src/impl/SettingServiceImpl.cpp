#include "stdafx.h"
#include "SettingServiceImpl.h"
#include "reader.h"
#include "TcpClient\CustomTcpClient.h"
#include "plog\Log.h"
#include "Business\CustomData.h"
#include "Utils.h"



CSettingServiceImpl::CSettingServiceImpl()
{
}


CSettingServiceImpl::~CSettingServiceImpl()
{
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::SelectMic(const char* deviceId, const char* deviceName)
{
    std::string strDeviceId = CUtils::ASCII2UTF_8(deviceId);
    std::string strDdeviceName = CUtils::ASCII2UTF_8(deviceName);
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "SelectMic";

    // 协议内容
    Json::Value body;
    body["deviceId"] = strDeviceId;
    body["deviceName"] = strDdeviceName;
    root["body"] = body;
    std::string strJson = root.toStyledString();
    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::SetMicVol(int& value)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "SetMicVol";

    // 协议内容
    Json::Value body;
    body["value"] = value;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::SelectSpeaker(const char* deviceId, const char* deviceName)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    std::string strDeviceId = CUtils::ASCII2UTF_8(deviceId);
    std::string strDeviceName = CUtils::ASCII2UTF_8(deviceName);

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "SelectSpeaker";

    // 协议内容
    Json::Value body;
    body["deviceId"] = strDeviceId;
    body["deviceName"] = strDeviceName;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::SetSpeakerVol(int& value)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "SetSpeakerVol";

    // 协议内容
    Json::Value body;
    body["value"] = value;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "AutoFullScreen";

    // 协议内容
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::EanbleAlwaysDisplayedMeetingCtrlBar(bool bEnable)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "AlwaysShowCtrlBar";

    // 协议内容
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::EanbleAlwaysJoinMeetingbeforeAdmin(bool bEnable)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "AlwaysJoinMeetingbeforeAdmin";

    // 协议内容
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::EnableAutoJoinAudio(bool bEnable)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "AutoJoinAudio";

    // 协议内容
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::EnableParticipantsUnmuteWhenMeeting(bool bEnable)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "ParticipantsUnmute";

    // 协议内容
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::EnableEchoCancellation(bool bEnable)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "EchoCancellation";

    // 协议内容
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::SelectCamera(const char* deviceId)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    std::string strDeviceId = CUtils::ASCII2UTF_8(deviceId);
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "SelectCamera";

    // 协议内容
    Json::Value body;
    body["deviceId"] = deviceId;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::EnableHDVideo(bool bEnable)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "HDVideo";

    // 协议内容
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "AutoTurnOffVideo";

    // 协议内容
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendContent = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendContent, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}
