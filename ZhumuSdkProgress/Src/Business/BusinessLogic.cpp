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
   m_hWndMainDlg = nullptr;
   m_bZhumuSdkAlreadyInit = false; // ��ĿSDK�Ƿ��Ѿ���ʼ�� true-��ʼ�� false-δ��ʼ��
   m_bIsLanding = false;           // ��ĿSDK�Ƿ����ڵ�½ true-���ڵ�½ false-δ��¼
   m_bAlreadyLanding = false;      // ��ĿSDK�Ƿ��Ѿ���¼ true-�Ѿ���¼ false-δ��¼
   m_bIsDirectLogin = false;       // ��¼SDK 
   m_bIsAnonymousJoin = false;     // �Ƿ�Ϊ�������
   m_bAlreadyAuth = false;         // �Ƿ��Ѿ���֤
   m_bReadyMeeting = false;        // �Ƿ�����׼������ true-����׼������ false-δ׼������
   m_bAttendMeeting = false;       // �Ƿ����ڲμӻ��� true-���ڲμӻ��� false-�μӻ���
   m_nWaitTimeOut = false;         // Э�鴦��ʱʱ��
   m_bAsynchronous = false;       // Э�鴦���Ƿ��첽
   m_bAuthResultReturned = false;  // ��֤����Ƿ񷵻� true-�Ѿ����� false-δ����
   m_bLoginResultReturned = false; // ��¼����Ƿ񷵻� true-�Ѿ����� false-δ����
   m_pZhumuSdkAgency = nullptr;
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
    m_mapMeetFailCode[MEETING_SUCCESS] = _T("��ʼ����ɹ���");//0,///<Start meeting successfully.
    m_mapMeetFailCode[MEETING_FAIL_NETWORK_ERR] = _T("�������");//1,///<Network error.
    m_mapMeetFailCode[MEETING_FAIL_RECONNECT_ERR] = _T("���Ӵ���");//2,///<Reconnect error.
    m_mapMeetFailCode[MEETING_FAIL_MMR_ERR] = _T("��ý��·��������");//3,///<Multi-media Router error.
    m_mapMeetFailCode[MEETING_FAIL_PASSWORD_ERR] = _T("�����Ǵ���ġ�");//4,///<Password is wrong.
    m_mapMeetFailCode[MEETING_FAIL_SESSION_ERR] = _T("�Ự�Ĵ���");//5,///<Session error.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_OVER] = _T("�����Ѿ������ˡ�");//6,///<Meeting is over.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_NOT_START] = _T("���黹û�п�ʼ��");//7,///<Meeting has not begun.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_NOT_EXIST] = _T("���鲻���ڡ�");//8,///<Meeting does not exist.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_USER_FULL] = _T("����������Ѿ����ˡ�");//9,///<The capacity of meeting is full.
    m_mapMeetFailCode[MEETING_FAIL_CLIENT_INCOMPATIBLE] = _T("�ͻ��˲����ݡ�");//10,///<The client is incompatible.
    m_mapMeetFailCode[MEETING_FAIL_NO_MMR] = _T("��ý��·������������");//11,///<The Multi-media router is not founded. 
    m_mapMeetFailCode[MEETING_FAIL_CONFLOCKED] = _T("������������");//12,///<The meeting is locked.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_RESTRICTED] = _T("����ͬһ�˺ŵ����ƣ�����ʧ�ܡ�");//13,///<The meeting is failed because of the restriction by the same account.
    m_mapMeetFailCode[MEETING_FAIL_MEETING_RESTRICTED_JBH] = _T("��������ͬ���ʻ����ƣ�������߱�����������֮ǰ���롣");//14,///<The meeting is restricted by the same account while the attendee is allowed to join before the host.
    m_mapMeetFailCode[MEETING_FAIL_CANNOT_EMIT_WEBREQUEST] = _T("�޷�����web����");//15,///<Unable to send web request.
    m_mapMeetFailCode[MEETING_FAIL_CANNOT_START_TOKENEXPIRE] = _T("���ƹ��ڡ�");//16,///The token is expired.
    m_mapMeetFailCode[SESSION_VIDEO_ERR] = _T("��ƵӲ�����������");//17,///<Video hardware or software error.
    m_mapMeetFailCode[SESSION_AUDIO_AUTOSTARTERR] = _T("��Ƶ�Զ����д���");//18,///<Audio autostart error.
    m_mapMeetFailCode[MEETING_FAIL_REGISTERWEBINAR_FULL] = _T("ע����������ֻ������Ѿ��ﵽ���ޡ�");//19,///<The number of webinar registered has reached the upper limit.
    m_mapMeetFailCode[MEETING_FAIL_REGISTERWEBINAR_HOSTREGISTER] = _T("ע���������ֻᣬ�����������ֻ������˵Ľ�ɫ��");//20,///<Register webinar with the role of webinar host.
    m_mapMeetFailCode[MEETING_FAIL_REGISTERWEBINAR_PANELISTREGISTER] = _T("��С���Ա�����ע���������ֻᡣ");//21,///<Register webinar with the role of panelist member.
    m_mapMeetFailCode[MEETING_FAIL_REGISTERWEBINAR_DENIED_EMAIL] = _T("�ñ��ܾ��ĵ����ʼ�ע���������ֻᡣ");//22,///<Register webinar with the denied email.
    m_mapMeetFailCode[MEETING_FAIL_ENFORCE_LOGIN] = _T("������������¼��");//23,///<Webinar request to login.
    m_mapMeetFailCode[CONF_FAIL_ZC_CERTIFICATE_CHANGED] = _T("Windows SDK��Ч��");//24,  ///<Invalid for Windows SDK.
    m_mapMeetFailCode[CONF_FAIL_VANITY_NOT_EXIST] = _T("�������ID�����ڡ�");//27, ///<Vanity conference ID does not exist.
    m_mapMeetFailCode[CONF_FAIL_JOIN_WEBINAR_WITHSAMEEMAIL] = _T("��ͬ�����ʼ�����������顣");//28, ///<Join webinar with the same email.
    m_mapMeetFailCode[CONF_FAIL_DISALLOW_HOST_MEETING] = _T("��������������������顣");//29, ///<Meeting settings is not allowed to start a meeting.
    m_mapMeetFailCode[MEETING_FAIL_WRITE_CONFIG_FILE] = _T("������д�������ļ���");//50,	///<Disabled to write the configure file.
    m_mapMeetFailCode[MEETING_FAIL_FORBID_TO_JOIN_INTERNAL_MEETING] = _T("��ֹ�μ��ڲ����顣");//60, ///<Forbidden to join the internal meeting.
    m_mapMeetFailCode[CONF_FAIL_REMOVED_BY_HOST] = _T("������ɾ����"); //61, ///<Removed by the host. 
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
/*                   �ϲ�Э����ô�����                                */
/************************************************************************/
int CBusinessLogic::InitZhumuSDK(std::string strContent)
{
    int nRet = -1;
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        bool        bAsynchronous = root["asynchronous"].asBool();
        int         nTimeOut = root["timeOut"].asInt();
        int         nSdkLangId = root["sdkLangId"].asInt();

        CBusinessLogic::GetInstance()->SetWaitTimeOut(nTimeOut);
        CBusinessLogic::GetInstance()->SetAsynchronous(bAsynchronous);
    }
    else
    {
        LOGE << "json reader error! content:[" << strContent << "] " << __FUNCTION__;
        return -1;
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

int CBusinessLogic::SettingMeetingZhumu(std::string strContent)
{
    int nRet = -1;

    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return nRet;
    }

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        SettingServerType settingType;
        SDKError    err = SDKERR_UNKNOWN;
        // �����ַ�����ƴ�ӳ�ʼ������
        std::string strMethod = root["method"].asString();
        auto body = root["body"];
        bool bEnable = body["enable"].asBool();
        if ("AutoFullScreen" == strMethod)
        {
            settingType = SETTIN_TYPE_AUTOFULLSCREEN;
            err = CZhumuSdkAgency::GetInstance()->EnableAutoFullScreenVideoWhenJoinMeeting(bEnable);
        }
        else if ("AlwaysShowCtrlBar" == strMethod)
        {
            settingType = SETTIN_TYPE_ALWAYSSHOWCTRLBAR;
            err = CZhumuSdkAgency::GetInstance()->EanbleAlwaysDisplayedMeetingCtrlBar(bEnable);
        }
        else if ("AlwaysJoinMeetingbeforeAdmin" == strMethod)
        {
            settingType = SETTIN_TYPE_ALWAYSJOINMEETINGBEFOREADMIN;
            err = CZhumuSdkAgency::GetInstance()->EanbleAlwaysJoinMeetingbeforeAdmin(bEnable);
        }
        else if ("AutoJoinAudio" == strMethod)
        {
            settingType = SETTIN_TYPE_AUTOJOINAUDIO;
            err = CZhumuSdkAgency::GetInstance()->EnableAutoJoinAudio(bEnable);
        }
        else if ("ParticipantsUnmute" == strMethod)
        {
            settingType = SETTIN_TYPE_PARTICIPANTSUNMUTE;
            err = CZhumuSdkAgency::GetInstance()->EnableParticipantsUnmuteWhenMeeting(bEnable);
        }
        else if ("EchoCancellation" == strMethod)
        {
            settingType = SETTIN_TYPE_ECHOCANCELLATION;
            err = CZhumuSdkAgency::GetInstance()->EnableEchoCancellation(bEnable);
        }
        else if ("HDVideo" == strMethod)
        {
            settingType = SETTIN_TYPE_HDVIDEO;
            err = CZhumuSdkAgency::GetInstance()->EnableHDVideo(bEnable);
        }
        else if ("AutoTurnOffVideo" == strMethod)
        {
            settingType = SETTIN_TYPE_AUTOJOINAUDIO;
            err = CZhumuSdkAgency::GetInstance()->EnableAutoTurnOffVideoWhenJoinMeeting(bEnable);
        }
        if (err == SDKERR_SUCCESS)
        {
            nRet = 0;
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }
    return nRet;
}

int CBusinessLogic::SelectMicZhumuSDK(std::string strContent)
{

    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    int nRet = -1;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return -1;
    }
    
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        std::string strDeviceId = root["deviceId"].asString();
        std::string strDeviceName = root["deviceName"].asString();
       
        strDeviceId = CUtils::UTF_82ASCII(strDeviceId);
        strDeviceName = CUtils::UTF_82ASCII(strDeviceName);

        SDKError err = CZhumuSdkAgency::GetInstance()->SelectMic(CUtils::s2ws(strDeviceId).c_str(), CUtils::s2ws(strDeviceName).c_str());
        if (err == SDKERR_SUCCESS)
        {
            nRet = 0;
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }
    delete reader;
    return nRet;
}

int CBusinessLogic::SetMicVolZhumuSDK(std::string strContent)
{
    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    int nRet = -1;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return -1;
    }

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        int nValue = root["value"].asInt();
        float fValue = (float)nValue * (float)255 / (float)100 ;

        SDKError err = CZhumuSdkAgency::GetInstance()->SetMicVol(fValue);
        if (err == SDKERR_SUCCESS)
        {
            nRet = 0;
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }
    delete reader;
    return nRet;
}

int CBusinessLogic::SelectSpeakerZhumuSDK(std::string strContent)
{
    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    int nRet = -1;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return -1;
    }

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        std::string strDeviceId = root["deviceId"].asString();
        std::string strDeviceName = root["deviceName"].asString();

        strDeviceId = CUtils::UTF_82ASCII(strDeviceId);
        strDeviceName = CUtils::UTF_82ASCII(strDeviceName);

        SDKError err = CZhumuSdkAgency::GetInstance()->SelectSpeaker(CUtils::s2ws(strDeviceId).c_str(), CUtils::s2ws(strDeviceName).c_str());
        if (err == SDKERR_SUCCESS)
        {
            nRet = 0;
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }
    delete reader;
    return nRet;
}

int CBusinessLogic::SetSpeakerVolZhumuSDK(std::string strContent)
{
    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    int nRet = -1;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return -1;
    }

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        int nValue = root["value"].asInt();
        float fValue = (float)nValue * (float)255 / (float)100;

        SDKError err = CZhumuSdkAgency::GetInstance()->SetSpeakerVol(fValue);
        if (err == SDKERR_SUCCESS)
        {
            nRet = 0;
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }
    delete reader;
    return nRet;
}

int CBusinessLogic::SelectCameraZhumuSDK(std::string strContent)
{
    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    int nRet = -1;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return -1;
    }

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        std::string strDeviceId = root["deviceId"].asString();
        strDeviceId = CUtils::UTF_82ASCII(strDeviceId);
        SDKError err = CZhumuSdkAgency::GetInstance()->SelectCamera(CUtils::s2ws(strDeviceId).c_str());
        if (err == SDKERR_SUCCESS)
        {
            nRet = 0;
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }
    delete reader;
    return nRet;
}

int CBusinessLogic::DirectSharingZhumu(std::string strContent)
{
    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    int nRet = -1;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return -1;
    }

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        UINT64 nMeetingNUmber = root["meetingNumber"].asInt64();
        SDKError err = CZhumuSdkAgency::GetInstance()->DirectSharing(nMeetingNUmber);
        if (err == SDKERR_SUCCESS)
        {
            nRet = 0;
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }
    delete reader;
    return nRet;
}

// ע�������ھ��
void CBusinessLogic::DestroyZhumuSDK()
{
    if (true == m_bAttendMeeting)
    {
        CZhumuSdkAgency::GetInstance()->LeaveMeeting();
    }
    if (true == m_bAlreadyLanding)
    {
        CZhumuSdkAgency::GetInstance()->LogOutSDK();
    }
    // �˳�sdk
    PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_QUIT, NULL, NULL);
}

/************************************************************************/
/*                   ִ�н��Э�鷴��������                             */
/************************************************************************/
// ������ʼ��SDK���
bool CBusinessLogic::FeedbackInitResult(ZOOM_SDK_NAMESPACE::SDKError ret)
{
    if (false == m_bAsynchronous)
    {
        return false;
    }
    bool bRet = false;

    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "InitResult";
    // Э������
    Json::Value body;
    body["initResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

// ������֤���
bool CBusinessLogic::FeedbackAuthResult(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
    if (false == m_bAsynchronous)
    {
        return false;
    }
    bool bRet = false;

    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "AuthResult";
    // Э������
    Json::Value body;
    body["authResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

// ������¼���
bool CBusinessLogic::FeedbackLoginResult(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret)
{
    if (false == m_bAsynchronous)
    {
        return false;
    }
    bool bRet = false;

    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "LoginResult";
    // Э������
    Json::Value body;
    body["loginResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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

    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "MeetingStatus";
    // Э������
    Json::Value body;
    body["meetingStatus"] = status;
    body["result"] = iResult;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

bool CBusinessLogic::FeedbackMeetingSettingResult(SettingServerType settingType, ZOOM_SDK_NAMESPACE::SDKError ret)
{
    bool bRet = false;

    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "MeetingSetting";
    // Э������
    Json::Value body;
    body["settingType"] = settingType;
    body["result"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
/*                   ��ĿSDK�ص�������                                 */
/************************************************************************/
void CBusinessLogic::AuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
    LOGI << "[" << __FUNCTION__ << "] Authentication Return :" << ret << std::endl;

    // ����֤����ص����ϲ�
    FeedbackAuthResult(ret);

    //��֤�ɹ������������Դȷ��ִ������
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
        // ����������ʾ
        CString strErrMsg;
        strErrMsg.Format(_T("authentication failure ! error code %d"), ret);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
        LOGI << "[" << __FUNCTION__ << "] Zhumu SDK authentication failure ! error code:" << ret << std::endl;
    }
    m_bAuthResultReturned = true;
}

void CBusinessLogic::LoginReturn(LOGINSTATUS ret, IAccountInfo* pAccountInfo)
{
    LOGI << "[" << __FUNCTION__ << "] Login Return:" << ret << std::endl;

    if (ret == LOGIN_SUCCESS)
    {
        m_bAlreadyLanding = true;
        m_bIsLanding = false;
        // ����֤����ص����ϲ�
        FeedbackLoginResult(ret);
        m_bLoginResultReturned = true;
    }
    else if (ret == LOGIN_FAILED)
    {
        m_bAlreadyLanding = false;
        m_bIsLanding = false;
        FeedbackLoginResult(ret);
        m_bLoginResultReturned = true;

        // ����������ʾ
        CString strErrMsg;
        strErrMsg.Format(_T("Login failure ! error code %d"), ret);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
    }
}

void CBusinessLogic::MeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/)
{
    LOGI << "[" << __FUNCTION__ << "] Meeting Status:" << status << " result:" << iResult << std::endl;
    // �κ�״̬���ص����ϲ�
    FeedbackMeetingStatusResult(status, iResult);

    // ���ݴ����������ʾ
    switch (status)
    {
    case MEETING_STATUS_DISCONNECTING:
    {
        // ����ʧȥ���� �����־λ
        m_bAttendMeeting = false;
        m_bReadyMeeting = false;
        break;
    }
    case MEETING_STATUS_ENDED:
    {
        // ������� �����־λ
        m_bAttendMeeting = false;
        m_bReadyMeeting = false;
        break;
    }
    case MEETING_STATUS_FAILED:
    {
        // ����ʧ�� �����־λ
        m_bAttendMeeting = false;
        m_bReadyMeeting = false;

        // ���ݸ��ݴ������ѯ������Ϣ
        CString strErrMsg = GetErrorDescriptionByErrorCode(MeetingFailCode(iResult));
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
        break;
    }
    case MEETING_STATUS_INMEETING:
    {
        // �������ɹ� ���ñ�־λ
        m_bAttendMeeting = true;
        m_bReadyMeeting = false;
        break;
    }
    case MEETING_STATUS_LOCKED:
    {
        // �����Ѿ�����
        CString strErrMsg;
        strErrMsg.Format(_T("�����Ѿ�����"));
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 2);
    }
    default:
        break;
    }

}

// ��¼
void CBusinessLogic::DirectLogin()
{
    SDKError err = CZhumuSdkAgency::GetInstance()->LoginSDK(CUtils::s2ws(m_loginSDKParam.account), CUtils::s2ws(m_loginSDKParam.password));
    if (err != SDKERR_SUCCESS)
    {
        // ������¼����
        FeedbackLoginResult(LOGIN_FAILED);
        // ����������ʾ
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
    return _T("δ֪�Ĵ�����Ϣ��");
}

// ע�������ھ��
void CBusinessLogic::RegisterMainDlgHwnd(HWND hWnd)
{
    m_hWndMainDlg = hWnd;
}

HWND CBusinessLogic::GetMainDlgHwnd()
{
    return m_hWndMainDlg;
}

// ��ĿSDK�Ƿ��Ѿ���ʼ�� true-��ʼ�� false-δ��ʼ��
bool CBusinessLogic::GetZhumuSdkAlreadyInit() const
{
    return m_bZhumuSdkAlreadyInit;
}

void CBusinessLogic::SetZhumuSdkAlreadyInit(bool val)
{
    m_bZhumuSdkAlreadyInit = val;
}

// ��ĿSDK�Ƿ����ڵ�½ true-���ڵ�½ false-δ��¼
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

int CBusinessLogic::GetWaitTimeOut() const
{
    return m_nWaitTimeOut;
}

void CBusinessLogic::SetWaitTimeOut(int val)
{
    m_nWaitTimeOut = val;
}

bool CBusinessLogic::GetAsynchronous() const
{
    return m_bAsynchronous;
}

void CBusinessLogic::SetAsynchronous(bool val)
{
    m_bAsynchronous = val;
}

bool CBusinessLogic::GetAuthResultReturned() const
{
    return m_bAuthResultReturned;
}

void CBusinessLogic::SetAuthResultReturned(bool val)
{
    m_bAuthResultReturned = val;
}

bool CBusinessLogic::GetLoginResultReturned() const
{
    return m_bLoginResultReturned;
}

void CBusinessLogic::SetLoginResultReturned(bool val)
{
    m_bLoginResultReturned = val;
}
