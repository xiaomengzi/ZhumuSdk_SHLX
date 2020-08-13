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
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "SelectMic";

    // Э������
    Json::Value body;
    body["deviceId"] = deviceId;
    body["deviceName"] = deviceName;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::SetMicVol(int& value)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "SetMicVol";

    // Э������
    Json::Value body;
    body["value"] = value;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::SelectSpeaker(const char* deviceId, const char* deviceName)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "SelectSpeaker";

    // Э������
    Json::Value body;
    body["deviceId"] = deviceId;
    body["deviceName"] = deviceName;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::SetSpeakerVol(int& value)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "SetSpeakerVol";

    // Э������
    Json::Value body;
    body["value"] = value;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "AutoFullScreen";

    // Э������
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "AlwaysShowCtrlBar";

    // Э������
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "AlwaysJoinMeetingbeforeAdmin";

    // Э������
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "AutoJoinAudio";

    // Э������
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "ParticipantsUnmute";

    // Э������
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "EchoCancellation";

    // Э������
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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

ZHUMUSDKEX_NAMESPACE::SDKError CSettingServiceImpl::SelectCamera(const char* deviceId)
{
    bool bRet = false;
    SDKError err = SDKERR_SUCCESS;
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "SelectCamera";

    // Э������
    Json::Value body;
    body["deviceId"] = deviceId;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "HDVideo";

    // Э������
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "AutoTurnOffVideo";

    // Э������
    Json::Value body;
    body["enable"] = bEnable;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
