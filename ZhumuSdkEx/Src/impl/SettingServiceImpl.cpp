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

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
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

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
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

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
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

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
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

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
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

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
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

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
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

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
        err = SDKERR_UNKNOWN;
    }
    return err;
}
