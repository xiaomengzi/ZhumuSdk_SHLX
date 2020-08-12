#include "stdafx.h"
#include "BusinessLogic.h"
#include "reader.h"
#include "Utils.h"
#include "Resource.h"
#include "zoom_sdk.h"
#include "zoom_sdk_def.h"
#include "plog\Log.h"
#include "ZhumuSdkAgency.h"
#include "TcpClient\CustomTcpClient.h"

using namespace ZOOM_SDK_NAMESPACE;

CBusinessLogic *CBusinessLogic::m_pInstance = nullptr;


CBusinessLogic::CBusinessLogic()
{
    m_hWndMainDlg = NULL;
    m_bZhumuSdkAlreadyInit = false; // 瞩目SDK是否已经初始化 true-初始化 false-未初始化
    m_bIsLanding = false;           // 瞩目SDK是否正在登陆 true-正在登陆 false-未登录
    m_bAlreadyLanding = false;      // 瞩目SDK是否已经登录 true-已经登录 false-未登录
    m_bIsDirectLogin = false;       // 登录SDK 
    m_bIsAnonymousJoin = false;     // 是否为匿名入会
    m_bAlreadyAuth = false;
    m_bReadyMeeting = false;;       // 是否正在准备会议 true-正在准备会议 false-未准备会议
    m_bAttendMeeting = false;       // 是否正在准备会议 true-正在准备会议 false-未准备会议
}


CBusinessLogic::~CBusinessLogic()
{
}


CBusinessLogic * CBusinessLogic::Initialize()
{
    return CBusinessLogic::GetInstance();
}

void CBusinessLogic::Uninitialize()
{
    if (m_pInstance != nullptr)
    {
        m_pInstance->UnInitData();
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

CBusinessLogic * CBusinessLogic::GetInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CBusinessLogic;
        m_pInstance->InitData();
    }
    return m_pInstance;
}


void CBusinessLogic::InitData()
{
    m_mapMeetFailCode[MEETING_SUCCESS] = _T("开始会议成功。");//0,///<Start meeting successfully.
    m_mapMeetFailCode[MEETING_FAIL_NETWORK_ERR] = _T("网络错误。");//1,///<Network error.
    m_mapMeetFailCode[MEETING_FAIL_RECONNECT_ERR] = _T("连接错误。");//2,///<Reconnect error.
    m_mapMeetFailCode[MEETING_FAIL_MMR_ERR] = _T("多媒体路由器错误。");//3,///<Multi-media Router error.
    m_mapMeetFailCode[MEETING_FAIL_PASSWORD_ERR] = _T("密码是错误的。");//4,///<Password is wrong.
    m_mapMeetFailCode[MEETING_FAIL_SESSION_ERR] = _T("会话的错误。");//5,///<Session error.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_OVER] = _T("会议已经结束了。");//6,///<Meeting is over.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_NOT_START] = _T("会议还没有开始。");//7,///<Meeting has not begun.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_NOT_EXIST] = _T("会议不存在。");//8,///<Meeting does not exist.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_USER_FULL] = _T("会议的容量已经满了。");//9,///<The capacity of meeting is full.
    m_mapMeetFailCode[MEETING_FAIL_CLIENT_INCOMPATIBLE] = _T("客户端不兼容。");//10,///<The client is incompatible.
    m_mapMeetFailCode[MEETING_FAIL_NO_MMR] = _T("多媒体路由器不成立。");//11,///<The Multi-media router is not founded. 
    m_mapMeetFailCode[MEETING_FAIL_CONFLOCKED] = _T("会议已锁定。");//12,///<The meeting is locked.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_RESTRICTED] = _T("由于同一账号的限制，会议失败。");//13,///<The meeting is failed because of the restriction by the same account.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_RESTRICTED_JBH] = _T("会议由相同的帐户限制，而与会者被允许在主机之前加入。");//14,///<The meeting is restricted by the same account while the attendee is allowed to join before the host.
    m_mapMeetFailCode[MEETING_FAIL_CANNOT_EMIT_WEBREQUEST] = _T("无法发送web请求。");//15,///<Unable to send web request.
    m_mapMeetFailCode[MEETING_FAIL_CANNOT_START_TOKENEXPIRE] = _T("令牌过期。");//16,///The token is expired.
    m_mapMeetFailCode[SESSION_VIDEO_ERR] = _T("视频硬件或软件错误。");//17,///<Video hardware or software error.
    m_mapMeetFailCode[SESSION_AUDIO_AUTOSTARTERR] = _T("音频自动运行错误。");//18,///<Audio autostart error.
    m_mapMeetFailCode[MEETING_FAIL_REGISTERWEBINAR_FULL] = _T("注册的网络研讨会数量已经达到上限。");//19,///<The number of webinar registered has reached the upper limit.
    m_mapMeetFailCode[MEETING_FAIL_REGISTERWEBINAR_HOSTREGISTER] = _T("注册网络研讨会，扮演网络研讨会主持人的角色。");//20,///<Register webinar with the role of webinar host.
    m_mapMeetFailCode[MEETING_FAIL_REGISTERWEBINAR_PANELISTREGISTER] = _T("以小组成员的身份注册网络研讨会。");//21,///<Register webinar with the role of panelist member.
    m_mapMeetFailCode[MEETING_FAIL_REGISTERWEBINAR_DENIED_EMAIL] = _T("用被拒绝的电子邮件注册网络研讨会。");//22,///<Register webinar with the denied email.
    m_mapMeetFailCode[MEETING_FAIL_ENFORCE_LOGIN] = _T("网络会议请求登录。");//23,///<Webinar request to login.
    m_mapMeetFailCode[CONF_FAIL_ZC_CERTIFICATE_CHANGED] = _T("Windows SDK无效。");//24,  ///<Invalid for Windows SDK.
    m_mapMeetFailCode[CONF_FAIL_VANITY_NOT_EXIST] = _T("虚拟会议ID不存在。");//27, ///<Vanity conference ID does not exist.
    m_mapMeetFailCode[CONF_FAIL_JOIN_WEBINAR_WITHSAMEEMAIL] = _T("用同样的邮件加入网络会议。");//28, ///<Join webinar with the same email.
    m_mapMeetFailCode[CONF_FAIL_DISALLOW_HOST_MEETING] = _T("不允许会议设置启动会议。");//29, ///<Meeting settings is not allowed to start a meeting.
    m_mapMeetFailCode[MEETING_FAIL_WRITE_CONFIG_FILE] = _T("禁用以写入配置文件。");//50,	///<Disabled to write the configure file.
    m_mapMeetFailCode[MEETING_FAIL_FORBID_TO_JOIN_INTERNAL_MEETING] = _T("禁止参加内部会议。");//60, ///<Forbidden to join the internal meeting.
    m_mapMeetFailCode[CONF_FAIL_REMOVED_BY_HOST] = _T("被主机删除。"); //61, ///<Removed by the host. 
}

void CBusinessLogic::UnInitData()
{
}

void CBusinessLogic::StartTcpServer()
{
    m_tcpServer.StartServer(g_nLocalListeningPort);
}

void CBusinessLogic::StopTcpServer()
{
    m_tcpServer.StopServer();

}
/************************************************************************/
/*                   上层协议调用处理函数                                */
/************************************************************************/
int CBusinessLogic::InitZhumuSDK(std::string strContent)
{
    int nRet = -1;
    if (true == m_bZhumuSdkAlreadyInit)
    {
        LOGE << "[" << __FUNCTION__ << "] Zhumu SDK Already initialized!" << std::endl;
        return nRet;
    }

    std::string *pStr = new std::string(strContent);
    PostMessage(m_hWndMainDlg, WMUSER_INIT_ZHUMUSDK, (WPARAM)pStr, NULL);

    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    return 0;
}

int CBusinessLogic::LoginZhumuSDK(std::string strContent)
{
    int nRet = -1;
    if (false == m_bZhumuSdkAlreadyInit)
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return nRet;
    }
    if (true == m_bAlreadyLanding || true == m_bIsLanding)
    {
        LOGE << "[" << __FUNCTION__ << "] Logging in or already logged in to the SDK!" << std::endl;
        return nRet;
    }

    std::string *pStr = new std::string(strContent);
    PostMessage(m_hWndMainDlg, WMUSER_LOGIN_ZHUMUSDK, (WPARAM)pStr, NULL);

    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    return 0;

}

int CBusinessLogic::StartAppointmentMeetingZhumuSDK(std::string strContent)
{
    int nRet = -1;

    std::string *pStr = new std::string(strContent);
    PostMessage(m_hWndMainDlg, WMUSER_START_APPOINTMENTMEETING_ZHUMUSDK, (WPARAM)pStr, NULL);

    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    return 0;
}

int CBusinessLogic::StartInstantMeetingZhumuSDK(std::string strContent)
{
    int nRet = -1;

    std::string *pStr = new std::string(strContent);
    PostMessage(m_hWndMainDlg, WMUSER_START_INSTANTMEETING_ZHUMUSDK, (WPARAM)pStr, NULL);

    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    return 0;
}


int CBusinessLogic::JoinMeetingZhumuSDK(std::string strContent)
{
    int nRet = -1;

    std::string *pStr = new std::string(strContent);
    PostMessage(m_hWndMainDlg, WMUSER_JOINMEETING_ZHUMUSDK, (WPARAM)pStr, NULL);

    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    return 0;
}

int CBusinessLogic::AnonymityJoinMeetingZhumuSDK(std::string strContent)
{
    int nRet = -1;

    std::string *pStr = new std::string(strContent);
    PostMessage(m_hWndMainDlg, WMUSER_ANONYMITY_JOINMEETING_ZHUMUSDK, (WPARAM)pStr, NULL);

    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    return 0;
}

// 注册主窗口句柄
void CBusinessLogic::DestroyZhumuSDK()
{
    // 退出sdk
    PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_QUIT, NULL, NULL);
}

/************************************************************************/
/*                   执行结果协议反馈处理函数                             */
/************************************************************************/
// 反馈初始化SDK结果
bool CBusinessLogic::FeedbackInitResult(ZOOM_SDK_NAMESPACE::SDKError ret)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "InitResult";
    // 协议内容
    Json::Value body;
    body["initResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

// 反馈认证结果
bool CBusinessLogic::FeedbackAuthResult(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "AuthResult";
    // 协议内容
    Json::Value body;
    body["authResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

// 反馈登录结果
bool CBusinessLogic::FeedbackLoginResult(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "LoginResult";
    // 协议内容
    Json::Value body;
    body["loginResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}


bool CBusinessLogic::FeedbackMeetingStatusResult(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "MeetingStatus";
    // 协议内容
    Json::Value body;
    body["meetingStatus"] = status;
    body["result"] = iResult;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

/************************************************************************/
/*                   瞩目SDK回调处理函数                                 */
/************************************************************************/
void CBusinessLogic::AuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
    LOGI << "[" << __FUNCTION__ << "] Authentication Return :" << ret << std::endl;

    // 将验证结果回调给上层
    FeedbackAuthResult(ret);

    //验证成功则根据任务来源确认执行条件
    if (ret == AUTHRET_SUCCESS)
    {
        m_bAlreadyAuth = true;
        if (m_bIsDirectLogin)
        {
            DirectLogin();
        }
    }
    else
    {
        // 弹出错误提示
        CString strErrMsg;
        strErrMsg.Format(_T("authentication failure ! error code %d"), ret);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
        LOGI << "[" << __FUNCTION__ << "] Zhumu SDK authentication failure ! error code:" << ret << std::endl;
    }
}

void CBusinessLogic::LoginReturn(LOGINSTATUS ret, IAccountInfo* pAccountInfo)
{
    LOGI << "[" << __FUNCTION__ << "] Login Return:" << ret << std::endl;

    if (ret == LOGIN_SUCCESS)
    {
        m_bAlreadyLanding = true;
        m_bIsLanding = false;
        // 将验证结果回调给上层
        FeedbackLoginResult(ret);
    }
    else if (ret == LOGIN_FAILED)
    {
        m_bAlreadyLanding = false;
        m_bIsLanding = false;
        FeedbackLoginResult(ret);

        // 弹出错误提示
        CString strErrMsg;
        strErrMsg.Format(_T("Login failure ! error code %d"), ret);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
    }
}

void CBusinessLogic::MeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/)
{
    LOGI << "[" << __FUNCTION__ << "] Meeting Status:" << status << " result:" << iResult << std::endl;
    // 任何状态都回调给上层
    FeedbackMeetingStatusResult(status, iResult);

    // 根据错误码进行提示
    switch (status)
    {
    case MEETING_STATUS_DISCONNECTING:
    {
        // 会议失去连接 清理标志位
        m_bAttendMeeting = false;
        m_bReadyMeeting = false;
        break;
    }
    case MEETING_STATUS_ENDED:
    {
        // 会议结束 清理标志位
        m_bAttendMeeting = false;
        m_bReadyMeeting = false;
        break;
    }
    case MEETING_STATUS_FAILED:
    {
        // 会议失败 清理标志位
        m_bAttendMeeting = false;
        m_bReadyMeeting = false;

        // 根据根据错误码查询错误信息
        CString strErrMsg = GetErrorDescriptionByErrorCode(MeetingFailCode(iResult));
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
        break;
    }
    case MEETING_STATUS_INMEETING:
    {
        // 进入会议成功 设置标志位
        m_bAttendMeeting = true;
        m_bReadyMeeting = false;
        break;
    }
    case MEETING_STATUS_LOCKED:
    {
        // 会议已经锁定
        CString strErrMsg;
        strErrMsg.Format(_T("会议已经锁定"));
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 2);
    }
    default:
        break;
    }

}

// 登录
void CBusinessLogic::DirectLogin()
{
    SDKError err = CZhumuSdkAgency::GetInstance()->LoginSDK(CUtils::s2ws(m_loginSDKParam.account), CUtils::s2ws(m_loginSDKParam.password));
    if (err != SDKERR_SUCCESS)
    {
        // 反馈登录错误
        FeedbackLoginResult(LOGIN_FAILED);
        // 弹出错误提示
        CString strErrMsg;
        strErrMsg.Format(_T("login SDK failure ! error code %d"), err);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
        LOGI << "[" << __FUNCTION__ << "] Zhumu SDK login SDK failure ! error code:" << err << std::endl;
    }
}

CString CBusinessLogic::GetErrorDescriptionByErrorCode(ZOOM_SDK_NAMESPACE::MeetingFailCode errCode)
{
    auto Iter = m_mapMeetFailCode.find(errCode);
    if (Iter != m_mapMeetFailCode.end())
    {
        return Iter->second;
    }
    return _T("未知的错误信息！");
}

// 注册主窗口句柄
void CBusinessLogic::RegisterMainDlgHwnd(HWND hWnd)
{
    m_hWndMainDlg = hWnd;
}

HWND CBusinessLogic::GetMainDlgHwnd()
{
    return m_hWndMainDlg;
}

// 瞩目SDK是否已经初始化 true-初始化 false-未初始化
bool CBusinessLogic::GetZhumuSdkAlreadyInit() const
{
    return m_bZhumuSdkAlreadyInit;
}

void CBusinessLogic::SetZhumuSdkAlreadyInit(bool val)
{
    m_bZhumuSdkAlreadyInit = val;
}

// 瞩目SDK是否正在登陆 true-正在登陆 false-未登录
bool CBusinessLogic::GetIsLanding() const
{
    return m_bIsLanding;
}

void CBusinessLogic::SetIsLanding(bool val)
{
    m_bIsLanding = val;
}

bool CBusinessLogic::GetAlreadyLanding() const
{
    return m_bAlreadyLanding;
}

void CBusinessLogic::SetAlreadyLanding(bool val)
{
    m_bAlreadyLanding = val;
}

bool CBusinessLogic::GetIsDirectLogin() const
{
    return m_bIsDirectLogin;
}

void CBusinessLogic::SetIsDirectLogin(bool val)
{
    m_bIsDirectLogin = val;
}

bool CBusinessLogic::GetIsAnonymousJoin() const
{
    return m_bIsAnonymousJoin;
}

void CBusinessLogic::SetIsAnonymousJoin(bool val)
{
    m_bIsAnonymousJoin = val;
}

bool CBusinessLogic::GetAlreadyAuth() const
{
    return m_bAlreadyAuth;
}

void CBusinessLogic::SetAlreadyAuth(bool val)
{
    m_bAlreadyAuth = val;
}

bool CBusinessLogic::GetReadyMeeting() const
{
    return m_bReadyMeeting;
}

void CBusinessLogic::SetReadyMeeting(bool val)
{
    m_bReadyMeeting = val;
}

bool CBusinessLogic::GetAttendMeeting() const
{
    return m_bAttendMeeting;
}

void CBusinessLogic::SetAttendMeeting(bool val)
{
    m_bAttendMeeting = val;
}

LoginSDKParam CBusinessLogic::GetLoginSDKParam() const
{
    return m_loginSDKParam;
}

void CBusinessLogic::SetLoginSDKParam(LoginSDKParam val)
{
    m_loginSDKParam = val;
}
