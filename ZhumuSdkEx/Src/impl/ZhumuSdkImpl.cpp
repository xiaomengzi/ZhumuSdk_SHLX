#include "stdafx.h"
#include <shellapi.h>
#include "ZhumuSdkImpl.h"
#include "plog\Log.h"
#include "Utils.h"
#include "TcpClient\CustomTcpClient.h"
#include "Business\CustomData.h"
#include "json.h"
#include "setting_service_interface.h"
#include "ZhumuSdkEx_def.h"


CZhumuSdkImpl::CZhumuSdkImpl()
{
    m_event = nullptr;
    m_pTcpServer = nullptr;

}

CZhumuSdkImpl::~CZhumuSdkImpl()
{

}

void CZhumuSdkImpl::SetEvent(ZhumuSdkEx_Event* _event)
{
    m_event = _event;
}

bool CZhumuSdkImpl::StartTcpServer()
{
    bool bRet = false;
    if (nullptr == m_pTcpServer)
    {
        m_pTcpServer = new CCustomTcpServer();
        m_pTcpServer->SetEvent(this);
        if (false == m_pTcpServer->StartServer(g_nLocalListeningPort))
        {
            LOGE << "[" << __FUNCTION__ << "] The TCP service failed to start! " << std::endl;
        }
        else
        {
            LOGI << "[" << __FUNCTION__ << "] The TCP service started successfully! " << std::endl;
            bRet = true;
        }
    }
    return bRet;
}

bool CZhumuSdkImpl::StopTcpServer()
{
    if (nullptr != m_pTcpServer)
    {
        m_pTcpServer->StopServer();
        m_pTcpServer = nullptr;
    }

    return true;
}

bool CZhumuSdkImpl::StartSdkProcess(std::string strPath /*= ""*/)
{
    HANDLE hMutex = nullptr;
    hMutex = CreateMutex(NULL, FALSE, _T("CZhumuSdkProgress_Mutex"));
    if (nullptr == hMutex || ERROR_ALREADY_EXISTS == ::GetLastError())
    {
        DestorySDK();
        Sleep(50);
    }
    if (nullptr != hMutex)
    {
        CloseHandle(hMutex);
    }

    std::string strExePath = strPath;
    if (strPath.empty())
    {
        // 未指定则在当前EXE同级目录中
        strExePath = "ZhumuSdkProgress.exe";
    }

    LOGI << "[" << __FUNCTION__ << "] strExePath: " << strPath << std::endl;

    // 启动进程
    ShellExecute(NULL, L"open", CUtils::s2ws(strExePath).c_str(), NULL, NULL, SW_SHOWNORMAL);
    //WinExec(strExePath.c_str(), SW_HIDE);
    return true;
}

bool CZhumuSdkImpl::InitSDK(ZmSdkInitParam initParam)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "InitSDK";
    // 协议内容
    Json::Value body;
    body["bandingName"] = (nullptr == initParam.bindingName) ? "" : CUtils::ASCII2UTF_8(initParam.bindingName);
    body["supportUrl"] = (nullptr == initParam.supportUrl) ? "" : CUtils::ASCII2UTF_8(initParam.supportUrl);
    body["wbDomain"] = (nullptr == initParam.webDomain) ? "" : CUtils::ASCII2UTF_8(initParam.webDomain);
    body["asynchronous"] = initParam.asynchronous;
    body["timeOut"] = initParam.timeOut;
    body["sdkLangId"] = initParam.language;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
    }
    return bRet;
}

bool CZhumuSdkImpl::LoginSDK(ZmSdkLoginParam loginParam)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "LoginSDK";
    // 协议内容
    Json::Value body;

    body["account"] = (nullptr == loginParam.account) ? "" : CUtils::ASCII2UTF_8(loginParam.account);
    body["password"] = (nullptr == loginParam.password) ? "" : CUtils::ASCII2UTF_8(loginParam.password);

    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
    }
    return bRet;
}

bool CZhumuSdkImpl::StartAppointmentMeeting(ZmStartAppointmentMeetingParam meetingParam)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "StartAppointmentMeeting";

    // 协议内容
    Json::Value body;
    body["meetingNumber"] = meetingParam.meetingNumber;
    body["participantId"] = (nullptr == meetingParam.participantId) ? "" : CUtils::ASCII2UTF_8(meetingParam.participantId);
    body["isVideoOff"] = meetingParam.isVideoOff;
    body["isAudioOff"] = meetingParam.isAudioOff;
    body["isDirectShareDesktop"] = meetingParam.isDirectShareDesktop;
    root["body"] = body;
    
    // 控制字段
    Json::Value meetingCtrl;
    meetingCtrl["fullScreenJoinMeeting"] = meetingParam.isFullScreenJoinMeeting;
    meetingCtrl["enableHDVideo"] = meetingParam.isEnableHDVideo;
    meetingCtrl["echoCancellation"] = meetingParam.isEchoCancellation;
    meetingCtrl["alwaysShowCtrlBar"] = meetingParam.isAlwaysShowCtrlBar;
    meetingCtrl["enableHDVideo"] = meetingParam.isEnableHDVideo;
    meetingCtrl["micDeviceId"] = (nullptr == meetingParam.micDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.micDeviceId);
    meetingCtrl["micDeviceName"] = (nullptr == meetingParam.micDeviceName) ? "" : CUtils::ASCII2UTF_8(meetingParam.micDeviceName);
    meetingCtrl["micVol"] = meetingParam.micVol;
    meetingCtrl["speakerDeviceId"] = (nullptr == meetingParam.speakerDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.speakerDeviceId);
    meetingCtrl["speakerDeviceName"] = (nullptr == meetingParam.speakerDeviceName) ? "" : CUtils::ASCII2UTF_8(meetingParam.speakerDeviceName);
    meetingCtrl["speakerVol"] = meetingParam.speakerVol;
    meetingCtrl["sameraDeviceId"] = (nullptr == meetingParam.sameraDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.sameraDeviceId);
    root["meetingCtrl"] = meetingCtrl;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
    }
    return bRet;
}

bool CZhumuSdkImpl::StartInstantMeeting(ZmStartInstantMeetingParam meetingParam)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "StartInstantMeeting";

    // 协议内容
    Json::Value body;
    body["meetingTopic"] = (nullptr == meetingParam.meetingTopic) ? "" : CUtils::ASCII2UTF_8(meetingParam.meetingTopic);
    body["meetingParticipants"] = (nullptr == meetingParam.meetingParticipants) ? "" : CUtils::ASCII2UTF_8(meetingParam.meetingParticipants);
    body["isVideoOff"] = meetingParam.isVideoOff;
    body["isAudioOff"] = meetingParam.isAudioOff;
    body["isDirectShareDesktop"] = meetingParam.isDirectShareDesktop;
    root["body"] = body;

    // 控制字段
    Json::Value meetingCtrl;
    meetingCtrl["fullScreenJoinMeeting"] = meetingParam.isFullScreenJoinMeeting;
    meetingCtrl["enableHDVideo"] = meetingParam.isEnableHDVideo;
    meetingCtrl["echoCancellation"] = meetingParam.isEchoCancellation;
    meetingCtrl["alwaysShowCtrlBar"] = meetingParam.isAlwaysShowCtrlBar;
    meetingCtrl["enableHDVideo"] = meetingParam.isEnableHDVideo;
    meetingCtrl["micDeviceId"] = (nullptr == meetingParam.micDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.micDeviceId);
    meetingCtrl["micDeviceName"] = (nullptr == meetingParam.micDeviceName) ? "" : CUtils::ASCII2UTF_8(meetingParam.micDeviceName);
    meetingCtrl["micVol"] = meetingParam.micVol;
    meetingCtrl["speakerDeviceId"] = (nullptr == meetingParam.speakerDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.speakerDeviceId);
    meetingCtrl["speakerDeviceName"] = (nullptr == meetingParam.speakerDeviceName) ? "" : CUtils::ASCII2UTF_8(meetingParam.speakerDeviceName);
    meetingCtrl["speakerVol"] = meetingParam.speakerVol;
    meetingCtrl["sameraDeviceId"] = (nullptr == meetingParam.sameraDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.sameraDeviceId);
    root["meetingCtrl"] = meetingCtrl;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
    }
    return bRet;
}

bool CZhumuSdkImpl::JoinMeeting(ZmJoinMeetingParam meetingParam)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "JoinMeeting";

    // 协议内容
    Json::Value body;
    body["meetingNumber"] = meetingParam.meetingNumber;
    body["userName"] = (nullptr == meetingParam.userName) ? "" : CUtils::ASCII2UTF_8(meetingParam.userName);
    body["psw"] = (nullptr == meetingParam.psw) ? "" : CUtils::ASCII2UTF_8(meetingParam.psw);
    body["isVideoOff"] = meetingParam.isVideoOff;
    body["isAudioOff"] = meetingParam.isAudioOff;
    body["isDirectShareDesktop"] = meetingParam.isDirectShareDesktop;
    root["body"] = body;

    // 控制字段
    Json::Value meetingCtrl;
    meetingCtrl["fullScreenJoinMeeting"] = meetingParam.isFullScreenJoinMeeting;
    meetingCtrl["enableHDVideo"] = meetingParam.isEnableHDVideo;
    meetingCtrl["echoCancellation"] = meetingParam.isEchoCancellation;
    meetingCtrl["alwaysShowCtrlBar"] = meetingParam.isAlwaysShowCtrlBar;
    meetingCtrl["enableHDVideo"] = meetingParam.isEnableHDVideo;
    meetingCtrl["micDeviceId"] = (nullptr == meetingParam.micDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.micDeviceId);
    meetingCtrl["micDeviceName"] = (nullptr == meetingParam.micDeviceName) ? "" : CUtils::ASCII2UTF_8(meetingParam.micDeviceName);
    meetingCtrl["micVol"] = meetingParam.micVol;
    meetingCtrl["speakerDeviceId"] = (nullptr == meetingParam.speakerDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.speakerDeviceId);
    meetingCtrl["speakerDeviceName"] = (nullptr == meetingParam.speakerDeviceName) ? "" : CUtils::ASCII2UTF_8(meetingParam.speakerDeviceName);
    meetingCtrl["speakerVol"] = meetingParam.speakerVol;
    meetingCtrl["sameraDeviceId"] = (nullptr == meetingParam.sameraDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.sameraDeviceId);
    root["meetingCtrl"] = meetingCtrl;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
    }
    return bRet;
}

bool CZhumuSdkImpl::AnonymityJoinMeeting(ZmAnonymityJoinMeetingParam meetingParam)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "AnonymityJoinMeeting";

    // 协议内容
    Json::Value body;
    body["meetingNumber"] = meetingParam.meetingNumber;
    body["userName"] = (nullptr == meetingParam.userName) ? "" : CUtils::ASCII2UTF_8(meetingParam.userName);
    body["psw"] = (nullptr == meetingParam.psw) ? "" : CUtils::ASCII2UTF_8(meetingParam.psw);
    body["isVideoOff"] = meetingParam.isVideoOff;
    body["isAudioOff"] = meetingParam.isAudioOff;
    body["isDirectShareDesktop"] = meetingParam.isDirectShareDesktop;
    root["body"] = body;

    // 控制字段
    Json::Value meetingCtrl;
    meetingCtrl["fullScreenJoinMeeting"] = meetingParam.isFullScreenJoinMeeting;
    meetingCtrl["enableHDVideo"] = meetingParam.isEnableHDVideo;
    meetingCtrl["echoCancellation"] = meetingParam.isEchoCancellation;
    meetingCtrl["alwaysShowCtrlBar"] = meetingParam.isAlwaysShowCtrlBar;
    meetingCtrl["micDeviceId"] = (nullptr == meetingParam.micDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.micDeviceId);
    meetingCtrl["micDeviceName"] = (nullptr == meetingParam.micDeviceName) ? "" : CUtils::ASCII2UTF_8(meetingParam.micDeviceName);
    meetingCtrl["micVol"] = meetingParam.micVol;
    meetingCtrl["speakerDeviceId"] = (nullptr == meetingParam.speakerDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.speakerDeviceId);
    meetingCtrl["speakerDeviceName"] = (nullptr == meetingParam.speakerDeviceName) ? "" : CUtils::ASCII2UTF_8(meetingParam.speakerDeviceName);
    meetingCtrl["speakerVol"] = meetingParam.speakerVol;
    meetingCtrl["cameraDeviceId"] = (nullptr == meetingParam.cameraDeviceId) ? "" : CUtils::ASCII2UTF_8(meetingParam.cameraDeviceId);
    root["meetingCtrl"] = meetingCtrl;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
    }
    return bRet;
}

bool CZhumuSdkImpl::DirectSharing(ZmDirectSharingParam directSharingParam)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "DirectSharing";
    Json::Value body;
    body["meetingNumber"] = directSharingParam.meetingNumber;
    root["body"] = body;
    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
    }
    return bRet;
}

bool CZhumuSdkImpl::DestorySDK()
{
    bool bRet = false;
    
    

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "DestorySDK";

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure ! " << std::endl;
    }
    return bRet;
}

void CZhumuSdkImpl::onInitRet(SDKError status)
{

}

void CZhumuSdkImpl::onAuthRet(AuthResult status)
{

}

void CZhumuSdkImpl::onLoginRet(LOGINSTATUS status)
{

}

void CZhumuSdkImpl::onMeetingStatus(MeetingStatus status, MeetingFailCode code)
{

}

void CZhumuSdkImpl::onExitApp()
{

}

int CZhumuSdkImpl::OnReceive(std::string strReceive, int iLength)
{
    return 0;
}

int CZhumuSdkImpl::OnInitResult(int nInitResult)
{
    LOGE << "[" << __FUNCTION__ << "]  initResult: " << nInitResult << std::endl;
    if (nullptr != m_event)
    {
        m_event->onInitRet(SDKError(nInitResult));
    }
    return 0;
}

int CZhumuSdkImpl::OnAuthResult(int nAuthResult)
{
    LOGE << "[" << __FUNCTION__ << "]  authResult: " << nAuthResult << std::endl;
    if (nullptr != m_event)
    {
        m_event->onAuthRet(AuthResult(nAuthResult));
    }
    return 0;
}

int CZhumuSdkImpl::OnLoginResult(int nLoginResult)
{
    LOGE << "[" << __FUNCTION__ << "]  loginResult: " << nLoginResult << std::endl;
    if (nullptr != m_event)
    {
        m_event->onLoginRet(LOGINSTATUS(nLoginResult));
    }
    return 0;
}

int CZhumuSdkImpl::OnMeetingStatusResult(int nMeetingStatus, int nFailCode)
{
    LOGE << "[" << __FUNCTION__ << "]  MeetingStatus: " << nMeetingStatus  << " FailCode: " << nFailCode << std::endl;
    if (nullptr != m_event)
    {
        m_event->onMeetingStatus(MeetingStatus(nMeetingStatus), MeetingFailCode(nFailCode));
    }
    return 0;
}



