
// ZhumuSdkProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ZhumuSdkProgress.h"
#include "ZhumuSdkProgressDlg.h"
#include "afxdialogex.h"
#include "zoom_sdk_def.h"
#include "ZhumuSdkAgency.h"
#include "BusinessLogic.h"
#include "plog\Log.h"
#include "writer.h"
#include "reader.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace ZOOM_SDK_NAMESPACE;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // �Ի�������
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZhumuSdkProgressDlg �Ի���



CZhumuSdkProgressDlg::CZhumuSdkProgressDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_ZHUMUSDKPROGRESS_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZhumuSdkProgressDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_editUserName);
    DDX_Control(pDX, IDC_EDIT2, m_editPassword);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINMEETINGNUMBER, m_editNormalJoinMeetingNumber);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINVANITYID, m_editNormalJoinVanityID);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINUSERNAME, m_editNormalJoinUserName);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINPSW, m_editNormalJoinPsw);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINPARTICIPANTID, m_editNormalJoinParticipantId);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINWEBINARTOKEN, m_editNormalJoinWebinarToken);
    DDX_Control(pDX, IDC_CHECK_NORMALJOINISVIDEOOFF, m_btnNormalJoinIsVideoOff);
    DDX_Control(pDX, IDC_CHECK_NORMALJOINISAUDIOOFF, m_btnNormalJoinIsAudioOff);
    DDX_Control(pDX, IDC_CHECK_NORMALJOINISDIRECTSHAREDESKTOP, m_btnNormalJoinIsDirectShareDesktop);
    DDX_Control(pDX, IDC_EDIT_NORMALSTARTMEETINGNUMBER, m_editNormalStartMeetingNumber);
    DDX_Control(pDX, IDC_EDIT_NORMALSTARTVANITYID, m_editNormalStartVanityID);
    DDX_Control(pDX, IDC_EDIT_NORMALSTARTPARTICIPANTID, m_editNormalStartParticipantId);
    DDX_Control(pDX, IDC_NORMALSTARTISVIDEOOFF, m_btnNormalStartIsVideoOff);
    DDX_Control(pDX, IDC_CHECK_NORMALSTARTISAUDIOOFF, m_btnNormalStartIsAudioOff);
    DDX_Control(pDX, IDC_CHECK_NORMALSTARTISDIRECTSHAREDESKTOP, m_btnNormalStartIsDirectShareDesktop);
}

BEGIN_MESSAGE_MAP(CZhumuSdkProgressDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()

    ON_REGISTERED_MESSAGE(WMUSER_BUSINESS_QUIT, &CZhumuSdkProgressDlg::OnQuitProgress)
    ON_REGISTERED_MESSAGE(WMUSER_BUSINESS_CUSTOM_ERROR, &CZhumuSdkProgressDlg::OnCustomErrorMessage)
    ON_REGISTERED_MESSAGE(WMUSER_INIT_ZHUMUSDK, &CZhumuSdkProgressDlg::OnInitZhumuSDk)
    ON_REGISTERED_MESSAGE(WMUSER_LOGIN_ZHUMUSDK, &CZhumuSdkProgressDlg::OnLoginZhumuSDk)
    ON_REGISTERED_MESSAGE(WMUSER_START_APPOINTMENTMEETING_ZHUMUSDK, &CZhumuSdkProgressDlg::OnStartAppointmentMeetingZhumuSDK)
    ON_REGISTERED_MESSAGE(WMUSER_START_INSTANTMEETING_ZHUMUSDK, &CZhumuSdkProgressDlg::OnStartInstantMeetingZhumuSDK)
    ON_REGISTERED_MESSAGE(WMUSER_JOINMEETING_ZHUMUSDK, &CZhumuSdkProgressDlg::OnJoinMeetingZhumuSDK)
    ON_REGISTERED_MESSAGE(WMUSER_ANONYMITY_JOINMEETING_ZHUMUSDK, &CZhumuSdkProgressDlg::OnAnonymityJoinMeetingZhumuSDK)
    ON_REGISTERED_MESSAGE(WMUSER_SETTINGMEETING_ZHUMUSDK, &CZhumuSdkProgressDlg::OnSettingMeetingZhumuSDK)
    
    
    ON_BN_CLICKED(IDC_BUTTON1, &CZhumuSdkProgressDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CZhumuSdkProgressDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CZhumuSdkProgressDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CZhumuSdkProgressDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CZhumuSdkProgressDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CZhumuSdkProgressDlg ��Ϣ�������

BOOL CZhumuSdkProgressDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // ��������...���˵�����ӵ�ϵͳ�˵��С�

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    ////���ؽ���
    //int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
    //int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
    //SetWindowPos(NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOZORDER);  //����0����,�Ƶ������  ����:MoveWindow(0,0,0,0);
    //ShowWindow(SW_HIDE);
    //ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);  //�Ƴ�������ͼ����ʾ

    // ע�������ھ��
    CBusinessLogic::GetInstance()->RegisterMainDlgHwnd(this->GetSafeHwnd());

    // ����tcp������
    CBusinessLogic::GetInstance()->StartTcpServer();

    m_editPassword.SetWindowTextW(_T("zm123456"));
    m_editUserName.SetWindowTextW(_T("mengxw@suirui.com"));

    m_editNormalJoinMeetingNumber.SetWindowTextW(_T("202444421"));
    m_editNormalJoinVanityID.SetWindowTextW(_T("zm123456"));
    m_editNormalJoinUserName.SetWindowTextW(_T("zm123456"));
    m_editNormalJoinPsw.SetWindowTextW(_T("zm123456"));
    m_editNormalJoinParticipantId.SetWindowTextW(_T("zm123456"));
    m_editNormalJoinWebinarToken.SetWindowTextW(_T("zm123456"));
    m_btnNormalJoinIsVideoOff.SetCheck(1);
    m_btnNormalJoinIsAudioOff.SetCheck(1);
    m_btnNormalJoinIsDirectShareDesktop.SetCheck(0);

    m_editNormalStartMeetingNumber.SetWindowTextW(_T("202444421"));
    m_editNormalStartVanityID.SetWindowTextW(_T("zm123456"));
    m_editNormalStartParticipantId.SetWindowTextW(_T("zm123456"));
    m_btnNormalStartIsVideoOff.SetCheck(1);
    m_btnNormalStartIsAudioOff.SetCheck(1);
    m_btnNormalStartIsDirectShareDesktop.SetCheck(0);
    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CZhumuSdkProgressDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZhumuSdkProgressDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CZhumuSdkProgressDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CZhumuSdkProgressDlg::CustomErrorMessage(CString strContent, int nType)
{
    switch (nType)
    {
    case 1:
    {
        // ����
        MessageBox(strContent, _T("Message"), MB_OKCANCEL | MB_ICONERROR);
        break;
    }
    case 2:
    {
        // ����
        MessageBox(strContent, _T("Message"), MB_OKCANCEL | MB_ICONWARNING);
        break;
    }
    default:
    {
        // ��Ϣ
        MessageBox(strContent, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
        break;
    }
    }
}

LRESULT CZhumuSdkProgressDlg::OnQuitProgress(WPARAM wParam, LPARAM lParam)
{
    // �رշ���
    CBusinessLogic::GetInstance()->StopTcpServer();

    // ������ĿSDK
    CZhumuSdkAgency::GetInstance()->Destory();

    // �˳�����
    OnOK();
    LOGI << "[" << __FUNCTION__ << "] Program normal exit!" << std::endl;
    return 0;
}


LRESULT CZhumuSdkProgressDlg::OnCustomErrorMessage(WPARAM wParam, LPARAM lParam)
{
    CString* pStrErrMsg = (CString*)wParam;
    if (nullptr != pStrErrMsg)
    {
        CString strContent(*pStrErrMsg);
        delete pStrErrMsg;
        pStrErrMsg = nullptr;
        CustomErrorMessage(strContent, (int)lParam);
    }
    return 0;
}


LRESULT CZhumuSdkProgressDlg::OnInitZhumuSDk(WPARAM wParam, LPARAM lParam)
{
    LOGI << "[" << __FUNCTION__ << "]  In!" << std::endl;

    std::string* pStrErrMsg = (std::string*)wParam;
    if (nullptr == pStrErrMsg)
    {
        return 0;
    }
    std::string strContent(*pStrErrMsg);
    CString strMsg;

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        std::string strBandingName = root["bandingName"].asString();
        std::string strSupportUrl = root["supportUrl"].asString();
        int         nSdkLangId = root["sdkLangId"].asInt();

        strBandingName = CUtils::UTF_82ASCII(strBandingName);
        strSupportUrl = CUtils::UTF_82ASCII(strSupportUrl);

        // ƴ�ӳ�ʼ������
        ZOOM_SDK_NAMESPACE::InitParam zm_param;
        zm_param.strWebDomain = g_strWebDomain.c_str();
        zm_param.strBrandingName = CUtils::s2ws(strBandingName).c_str();
        zm_param.emLanguageID = SDK_LANGUAGE_ID(nSdkLangId);
        zm_param.strSupportUrl = CUtils::s2ws(strSupportUrl).c_str();
        zm_param.uiWindowIconSmallID = IDI_ICON1;
        zm_param.uiWindowIconBigID = IDI_ICON1;
        zm_param.enableLogByDefault = true;

        SDKError err = CZhumuSdkAgency::GetInstance()->InitZhunmuSDK(zm_param);

        // ��ʼ���ɹ��������
        CBusinessLogic::GetInstance()->FeedbackInitResult(err);
        if (err != SDKError::SDKERR_SUCCESS)
        {
            strMsg.Format(_T("init SDK error !error code %d"), err);
            CustomErrorMessage(strMsg, 1);
            LOGI << "[" << __FUNCTION__ << "]  Zhumu SDK Failed to initialize!error code :" << err << std::endl;
        }
        else
        {
            CBusinessLogic::GetInstance()->SetZhumuSdkAlreadyInit(true);
            bool bSuccess = false;
            // ��ʼ��֤
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateAuthService();
            if (err == SDKError::SDKERR_SUCCESS)
            {
                err = CZhumuSdkAgency::GetInstance()->AuthSDK(const_cast<wchar_t*>(g_strAuthAppKey.c_str()), const_cast<wchar_t*>(g_strAuthAppSecret.c_str()));
                if (err == SDKError::SDKERR_SUCCESS)
                {
                    bSuccess = true;
                }
            }
            if (false == bSuccess)
            {
                CBusinessLogic::GetInstance()->FeedbackAuthResult(AUTHRET_UNKNOWN);
                strMsg.Format(_T("Authentication failed! error code:%d"), err);
                CustomErrorMessage(strMsg, 1);
            }
        }
    }
    else
    {
        LOGE << "json reader error! content:[" << strContent << "] " << __FUNCTION__;
    }

    delete reader;
    return 0;

}

LRESULT CZhumuSdkProgressDlg::OnLoginZhumuSDk(WPARAM wParam, LPARAM lParam)
{
    LOGI << "[" << __FUNCTION__ << "] In!" << std::endl;
    std::string* pStrErrMsg = (std::string*)wParam;
    if (nullptr == pStrErrMsg)
    {
        return 0;
    }
    std::string strContent(*pStrErrMsg);
    CString strMsg;

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        std::string strAccount = root["account"].asString();
        std::string strPassword = root["password"].asString();

        LoginSDKParam       loginSDKParam;        // ��¼��ĿSDK����


        std::string strAccountTemp = CUtils::UTF_82ASCII(strAccount);;
        std::string strPasswordTemp = CUtils::UTF_82ASCII(strPassword);;
        // �����¼����SDK����
        loginSDKParam.account = strAccountTemp;
        loginSDKParam.password = strPasswordTemp;
        // �����ݱ���
        CBusinessLogic::GetInstance()->SetIsDirectLogin(true);
        CBusinessLogic::GetInstance()->SetLoginSDKParam(loginSDKParam);

        if (true == CBusinessLogic::GetInstance()->GetAlreadyAuth())
        {
            // �Ѿ�ͨ����֤��ֱ�ӵ�¼
            SDKError err = CZhumuSdkAgency::GetInstance()->LoginSDK(CUtils::s2ws(strAccountTemp), CUtils::s2ws(strPasswordTemp));
            if (err != SDKERR_SUCCESS)
            {
                // ������¼����
                CBusinessLogic::GetInstance()->FeedbackLoginResult(LOGIN_FAILED);
                // ����������ʾ
                strMsg.Format(_T(" login SDK failure! error code : %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "] Zhumu SDK login SDK failure ! error code:" << err << std::endl;
            }
        }
        else
        {
            // δͨ����֤�����Ƚ��е�¼��֤
            bool bSuccess = false;
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateAuthService();
            if (err == SDKError::SDKERR_SUCCESS)
            {
                err = CZhumuSdkAgency::GetInstance()->AuthSDK(const_cast<wchar_t*>(g_strAuthAppKey.c_str()), const_cast<wchar_t*>(g_strAuthAppSecret.c_str()));
                if (err == SDKError::SDKERR_SUCCESS)
                {
                    bSuccess = true;
                }
            }
            if (false == bSuccess)
            {
                CBusinessLogic::GetInstance()->FeedbackAuthResult(AUTHRET_UNKNOWN);
                CBusinessLogic::GetInstance()->FeedbackLoginResult(LOGIN_FAILED);

                strMsg.Format(_T(" login SDK failure! error code : %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "] authentication failure ! error code: " << err << std::endl;
            }
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }

    delete reader;
    return 0;
}

LRESULT CZhumuSdkProgressDlg::OnStartAppointmentMeetingZhumuSDK(WPARAM wParam, LPARAM lParam)
{
    LOGI << "[" << __FUNCTION__ << "] In!" << std::endl;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return 0;
    }
    if (false == CBusinessLogic::GetInstance()->GetAlreadyLanding()
        || true == CBusinessLogic::GetInstance()->GetIsLanding())
    {
        LOGE << "[" << __FUNCTION__ << "] Logging in or already logged in to the SDK!" << std::endl;
        return 0;
    }
    if (true == CBusinessLogic::GetInstance()->GetReadyMeeting()
        || true == CBusinessLogic::GetInstance()->GetAttendMeeting())
    {
        LOGE << "[" << __FUNCTION__ << "] Joining or having joined a meeting!" << std::endl;
        return 0;
    }

    std::string* pStrErrMsg = (std::string*)wParam;
    if (nullptr == pStrErrMsg)
    {
        return 0;
    }

    std::string strContent(*pStrErrMsg);
    CString strMsg;

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        UINT64		nMeetingNumber = root["meetingNumber"].asInt64();
        std::string strParticipantId = root["participantId"].asString();
        bool bIsVideoOff = root["isVideoOff"].asBool();
        bool bIsAudioOff = root["isAudioOff"].asBool();
        bool bIsDirectShareDesktop = root["isDirectShareDesktop"].asBool();

        std::string strParticipantIdTemp = CUtils::UTF_82ASCII(strParticipantId);

        CBusinessLogic::GetInstance()->SetReadyMeeting(true);

        ZOOM_SDK_NAMESPACE::StartParam startParam;
        startParam.userType = SDK_UT_NORMALUSER;
        startParam.param.normaluserStart.meetingNumber = nMeetingNumber;
        startParam.param.normaluserStart.participantId = CUtils::s2ws(strParticipantIdTemp).c_str();
        startParam.param.normaluserStart.isVideoOff = bIsVideoOff;
        startParam.param.normaluserStart.isAudioOff = bIsAudioOff;
        startParam.param.normaluserStart.isDirectShareDesktop = bIsDirectShareDesktop;

        if (true == CBusinessLogic::GetInstance()->GetAlreadyAuth())
        {
            // �Ѿ�ͨ����֤��ֱ�ӵ�¼
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateMeetingService();
            if (err == SDKERR_SUCCESS)
            {
                err = CZhumuSdkAgency::GetInstance()->StartAppointmentMeeting(startParam);
            }
            if (err != SDKERR_SUCCESS)
            {
                CBusinessLogic::GetInstance()->SetReadyMeeting(false);

                // ������¼����
                CBusinessLogic::GetInstance()->FeedbackMeetingStatusResult(MEETING_STATUS_FAILED, 0);
                // ����������ʾ
                strMsg.Format(_T(" The meeting failed to start ! error code: %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "]The meeting failed to start ! error code:" << err << std::endl;
            }
        }
        else
        {
            // δͨ����֤�����Ƚ��е�¼��֤
            bool bSuccess = false;
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateAuthService();
            if (err == SDKError::SDKERR_SUCCESS)
            {
                err = CZhumuSdkAgency::GetInstance()->AuthSDK(const_cast<wchar_t*>(g_strAuthAppKey.c_str()), const_cast<wchar_t*>(g_strAuthAppSecret.c_str()));
                if (err == SDKError::SDKERR_SUCCESS)
                {
                    bSuccess = true;
                }
            }
            if (false == bSuccess)
            {
                CBusinessLogic::GetInstance()->FeedbackAuthResult(AUTHRET_UNKNOWN);
                CBusinessLogic::GetInstance()->FeedbackLoginResult(LOGIN_FAILED);

                strMsg.Format(_T(" login SDK failure! error code : %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "] authentication failure ! error code: " << err << std::endl;
            }
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }

    delete reader;
    return 0;
}

LRESULT CZhumuSdkProgressDlg::OnStartInstantMeetingZhumuSDK(WPARAM wParam, LPARAM lParam)
{
    LOGI << "[" << __FUNCTION__ << "] In!" << std::endl;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return 0;
    }
    if (false == CBusinessLogic::GetInstance()->GetAlreadyLanding()
        || true == CBusinessLogic::GetInstance()->GetIsLanding())
    {
        LOGE << "[" << __FUNCTION__ << "] Logging in or already logged in to the SDK!" << std::endl;
        return 0;
    }
    if (true == CBusinessLogic::GetInstance()->GetReadyMeeting()
        || true == CBusinessLogic::GetInstance()->GetAttendMeeting())
    {
        LOGE << "[" << __FUNCTION__ << "] Joining or having joined a meeting!" << std::endl;
        return 0;
    }

    std::string* pStrErrMsg = (std::string*)wParam;
    if (nullptr == pStrErrMsg)
    {
        return 0;
    }

    std::string strContent(*pStrErrMsg);
    CString strMsg;

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        std::string strMeetingTopic = root["meetingTopic"].asString();
        std::string strParticipantId = root["meetingParticipants"].asString();
        bool bIsVideoOff = root["isVideoOff"].asBool();
        bool bIsAudioOff = root["isAudioOff"].asBool();
        bool bIsDirectShareDesktop = root["isDirectShareDesktop"].asBool();

        std::string strParticipantIdTemp = CUtils::UTF_82ASCII(strParticipantId);

        CBusinessLogic::GetInstance()->SetReadyMeeting(true);

        ZOOM_SDK_NAMESPACE::StartParam startParam;
        startParam.userType = SDK_UT_NORMALUSER;
        startParam.param.normaluserStart.participantId = CUtils::s2ws(strParticipantIdTemp).c_str();
        startParam.param.normaluserStart.isVideoOff = bIsVideoOff;
        startParam.param.normaluserStart.isAudioOff = bIsAudioOff;
        startParam.param.normaluserStart.isDirectShareDesktop = bIsDirectShareDesktop;

        if (true == CBusinessLogic::GetInstance()->GetAlreadyAuth())
        {
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateMeetingService();
            if (err == SDKERR_SUCCESS)
            {
                err = CZhumuSdkAgency::GetInstance()->StartInstantMeeting(startParam);
            }
            if (err != SDKERR_SUCCESS)
            {
                CBusinessLogic::GetInstance()->SetReadyMeeting(false);

                // ������¼����
                CBusinessLogic::GetInstance()->FeedbackMeetingStatusResult(MEETING_STATUS_FAILED, 0);
                // ����������ʾ
                strMsg.Format(_T(" The meeting failed to start ! error code: %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "]The meeting failed to start ! error code:" << err << std::endl;
            }
        }
        else
        {
            // δͨ����֤�����Ƚ��е�¼��֤
            bool bSuccess = false;
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateAuthService();
            if (err == SDKError::SDKERR_SUCCESS)
            {
                err = CZhumuSdkAgency::GetInstance()->AuthSDK(const_cast<wchar_t*>(g_strAuthAppKey.c_str()), const_cast<wchar_t*>(g_strAuthAppSecret.c_str()));
                if (err == SDKError::SDKERR_SUCCESS)
                {
                    bSuccess = true;
                }
            }
            if (false == bSuccess)
            {
                CBusinessLogic::GetInstance()->FeedbackAuthResult(AUTHRET_UNKNOWN);
                CBusinessLogic::GetInstance()->FeedbackLoginResult(LOGIN_FAILED);

                strMsg.Format(_T(" login SDK failure! error code : %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "] authentication failure ! error code: " << err << std::endl;
            }
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }

    delete reader;
    return 0;
}

LRESULT CZhumuSdkProgressDlg::OnJoinMeetingZhumuSDK(WPARAM wParam, LPARAM lParam)
{
    LOGI << "[" << __FUNCTION__ << "] In!" << std::endl;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return 0;
    }
    if (false == CBusinessLogic::GetInstance()->GetAlreadyLanding()
        || true == CBusinessLogic::GetInstance()->GetIsLanding())
    {
        LOGE << "[" << __FUNCTION__ << "] Logging in or already logged in to the SDK!" << std::endl;
        return 0;
    }
    if (true == CBusinessLogic::GetInstance()->GetReadyMeeting()
        || true == CBusinessLogic::GetInstance()->GetAttendMeeting())
    {
        LOGE << "[" << __FUNCTION__ << "] Joining or having joined a meeting!" << std::endl;
        return 0;
    }

    std::string* pStrErrMsg = (std::string*)wParam;
    if (nullptr == pStrErrMsg)
    {
        return 0;
    }

    std::string strContent(*pStrErrMsg);
    CString strMsg;

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        UINT64		nMeetingNumber = root["meetingNumber"].asInt64();
        std::string strUserName = root["userName"].asString();
        std::string strPsw = root["psw"].asString();
        bool bIsVideoOff = root["isVideoOff"].asBool();
        bool bIsAudioOff = root["isAudioOff"].asBool();
        bool bIsDirectShareDesktop = root["isDirectShareDesktop"].asBool();

        std::string strUserNameTemp = CUtils::UTF_82ASCII(strUserName);
        std::string strPswTemp = CUtils::UTF_82ASCII(strPsw);

        CBusinessLogic::GetInstance()->SetReadyMeeting(true);

        JoinParam joinParam;
        joinParam.userType = SDK_UT_NORMALUSER;
        joinParam.param.normaluserJoin.meetingNumber = nMeetingNumber;
        joinParam.param.normaluserJoin.userName = CUtils::s2ws(strUserNameTemp).c_str();
        joinParam.param.normaluserJoin.psw = CUtils::s2ws(strPswTemp).c_str();
        joinParam.param.normaluserJoin.isVideoOff = bIsVideoOff;
        joinParam.param.normaluserJoin.isAudioOff = bIsAudioOff;
        joinParam.param.normaluserJoin.isDirectShareDesktop = bIsDirectShareDesktop;

        if (true == CBusinessLogic::GetInstance()->GetAlreadyAuth())
        {
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateMeetingService();
            if (err == SDKERR_SUCCESS)
            {
                SDKError err = CZhumuSdkAgency::GetInstance()->JoinMeeting(joinParam);
            }
            if (err != SDKERR_SUCCESS)
            {
                CBusinessLogic::GetInstance()->SetReadyMeeting(false);
                // ������¼����
                CBusinessLogic::GetInstance()->FeedbackMeetingStatusResult(MEETING_STATUS_FAILED, 0);
                // ����������ʾ
                strMsg.Format(_T(" Failed to join the meeting ! error code: %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "] Failed to join the meeting ! error code:" << err << std::endl;
            }
        }
        else
        {
            // δͨ����֤�����Ƚ��е�¼��֤
            bool bSuccess = false;
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateAuthService();
            if (err == SDKError::SDKERR_SUCCESS)
            {
                err = CZhumuSdkAgency::GetInstance()->AuthSDK(const_cast<wchar_t*>(g_strAuthAppKey.c_str()), const_cast<wchar_t*>(g_strAuthAppSecret.c_str()));
                if (err == SDKError::SDKERR_SUCCESS)
                {
                    bSuccess = true;
                }
            }
            if (false == bSuccess)
            {
                CBusinessLogic::GetInstance()->FeedbackAuthResult(AUTHRET_UNKNOWN);
                CBusinessLogic::GetInstance()->FeedbackMeetingStatusResult(MEETING_STATUS_FAILED, 0);

                strMsg.Format(_T(" Failed to join the meeting! error code : %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "] authentication failure ! error code: " << err << std::endl;
            }
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }

    delete reader;
    return 0;
}

LRESULT CZhumuSdkProgressDlg::OnAnonymityJoinMeetingZhumuSDK(WPARAM wParam, LPARAM lParam)
{
    LOGI << "[" << __FUNCTION__ << "] In!" << std::endl;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return 0;
    }
    if (true == CBusinessLogic::GetInstance()->GetReadyMeeting()
        || true == CBusinessLogic::GetInstance()->GetAttendMeeting())
    {
        LOGE << "[" << __FUNCTION__ << "] Joining or having joined a meeting!" << std::endl;
        return 0;
    }

    std::string* pStrErrMsg = (std::string*)wParam;
    if (nullptr == pStrErrMsg)
    {
        return 0;
    }

    std::string strContent(*pStrErrMsg);
    CString strMsg;

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        UINT64		nMeetingNumber = root["meetingNumber"].asInt64();
        std::string strUserName = root["userName"].asString();
        std::string strPsw = root["psw"].asString();
        bool bIsVideoOff = root["isVideoOff"].asBool();
        bool bIsAudioOff = root["isAudioOff"].asBool();
        bool bIsDirectShareDesktop = root["isDirectShareDesktop"].asBool();

        std::string strUserNameTemp = CUtils::UTF_82ASCII(strUserName);
        std::string strPswTemp = CUtils::UTF_82ASCII(strPsw);

        CBusinessLogic::GetInstance()->SetReadyMeeting(true);

        JoinParam joinParam;
        joinParam.userType = SDK_UT_WITHOUT_LOGIN;
        joinParam.param.withoutloginuserJoin.meetingNumber = nMeetingNumber;
        joinParam.param.withoutloginuserJoin.userName = CUtils::s2ws(strUserNameTemp).c_str();
        joinParam.param.withoutloginuserJoin.psw = CUtils::s2ws(strPswTemp).c_str();
        joinParam.param.withoutloginuserJoin.isVideoOff = bIsVideoOff;
        joinParam.param.withoutloginuserJoin.isAudioOff = bIsAudioOff;
        joinParam.param.withoutloginuserJoin.isDirectShareDesktop = bIsDirectShareDesktop;

        if (true == CBusinessLogic::GetInstance()->GetAlreadyAuth())
        {
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateMeetingService();
            if (err == SDKERR_SUCCESS)
            {
                SDKError err = CZhumuSdkAgency::GetInstance()->AnonymityJoinMeeting(joinParam);
            }
            if (err != SDKERR_SUCCESS)
            {
                CBusinessLogic::GetInstance()->SetReadyMeeting(false);
                // ������¼����
                CBusinessLogic::GetInstance()->FeedbackMeetingStatusResult(MEETING_STATUS_FAILED, 0);
                // ����������ʾ
                strMsg.Format(_T(" Failed to join the meeting ! error code: %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "] Failed to join the meeting ! error code:" << err << std::endl;
            }
        }
        else
        {
            // δͨ����֤�����Ƚ��е�¼��֤
            bool bSuccess = false;
            SDKError err = CZhumuSdkAgency::GetInstance()->CreateAuthService();
            if (err == SDKError::SDKERR_SUCCESS)
            {
                err = CZhumuSdkAgency::GetInstance()->AuthSDK(const_cast<wchar_t*>(g_strAuthAppKey.c_str()), const_cast<wchar_t*>(g_strAuthAppSecret.c_str()));
                if (err == SDKError::SDKERR_SUCCESS)
                {
                    bSuccess = true;
                }
            }
            if (false == bSuccess)
            {
                CBusinessLogic::GetInstance()->FeedbackAuthResult(AUTHRET_UNKNOWN);
                CBusinessLogic::GetInstance()->FeedbackMeetingStatusResult(MEETING_STATUS_FAILED, 0);

                strMsg.Format(_T(" Failed to join the meeting! error code : %d"), err);
                CustomErrorMessage(strMsg, 1);
                LOGE << "[" << __FUNCTION__ << "] authentication failure ! error code: " << err << std::endl;
            }
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }

    delete reader;
    return 0;
}

LRESULT CZhumuSdkProgressDlg::OnSettingMeetingZhumuSDK(WPARAM wParam, LPARAM lParam)
{
    LOGI << "[" << __FUNCTION__ << "] In!" << std::endl;

    if (false == CBusinessLogic::GetInstance()->GetZhumuSdkAlreadyInit())
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return 0;
    }

    std::string* pStrErrMsg = (std::string*)wParam;
    if (nullptr == pStrErrMsg)
    {
        return 0;
    }

    std::string strContent(*pStrErrMsg);

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
        CBusinessLogic::GetInstance()->FeedbackMeetingSettingResult(settingType, err);
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strContent << "] " << std::endl;
    }
}

void CZhumuSdkProgressDlg::OnBnClickedButton1()
{
    ZOOM_SDK_NAMESPACE::InitParam zm_param;
    zm_param.strWebDomain = L"https://launcher.zhumu.me";
    zm_param.strBrandingName = L"TiYiYun";
    zm_param.emLanguageID = LANGUAGE_Chinese_Simplified;
    zm_param.strSupportUrl = L"https://www.cloudmeeting.com";;
    zm_param.uiWindowIconSmallID = IDI_ICON1;
    zm_param.uiWindowIconBigID = IDI_ICON1;
    zm_param.enableLogByDefault = true;

    SDKError err = CZhumuSdkAgency::GetInstance()->InitZhunmuSDK(zm_param);

    {
        CString strMsg;
        strMsg.Format(_T("%d = ZOOM_SDK_NAMESPACE::InitSDK(zm_param)"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
    }
}

void CZhumuSdkProgressDlg::OnBnClickedButton2()
{
    SDKError err = CZhumuSdkAgency::GetInstance()->CreateAuthService();
    {
        CString strMsg;
        strMsg.Format(_T("%d = CreateAuthService(&m_pAuthService)"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
    }

    err = CZhumuSdkAgency::GetInstance()->AuthSDK(L"kaiM02SkFATpUuPrvAXvEFN2qVOAhHlH3UQc", L"frmtL8kBo6vlcpUn2JNbqoicT3jxdnDnSM5e");
    {
        CString strMsg;
        strMsg.Format(_T("%d = AuthSDK(...)"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
    }
}

void CZhumuSdkProgressDlg::OnBnClickedButton3()
{
    CString strUserName;
    CString strPassword;

    m_editUserName.GetWindowTextW(strUserName);
    m_editPassword.GetWindowTextW(strPassword);

    std::string strName = CT2A(strUserName);
    std::string strUserPassword = CT2A(strPassword);

    SDKError err = CZhumuSdkAgency::GetInstance()->LoginSDK(CUtils::s2ws(strName), CUtils::s2ws(strUserPassword));
    {
        CString strMsg;
        strMsg.Format(_T("%d = LoginSDK(...)"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
    }
}

void CZhumuSdkProgressDlg::OnBnClickedButton4()
{
    
    CString strNormalStartMeetingNumber;
    CString strNormalStartVanityID;
    CString strNormalStartUserName;
    CString strNormalStartParticipantId;

    m_editNormalStartMeetingNumber.GetWindowTextW(strNormalStartMeetingNumber);
    m_editNormalStartVanityID.GetWindowTextW(strNormalStartVanityID);
    m_editNormalStartParticipantId.GetWindowTextW(strNormalStartParticipantId);

    std::string strVanityID = CT2A(strNormalStartVanityID);
    std::string strParticipantId = CT2A(strNormalStartParticipantId);

    SDKError err = CZhumuSdkAgency::GetInstance()->CreateMeetingService();
    {
        CString strMsg;
        strMsg.Format(_T("%d = CreateMeetingService()"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
    }

    ZOOM_SDK_NAMESPACE::StartParam startParam;
    startParam.userType = SDK_UT_NORMALUSER;
    //startParam.param.normaluserStart.meetingNumber = _ttoi64(strNormalStartMeetingNumber);
    //startParam.param.normaluserStart.vanityID = CUtils::s2ws(strVanityID).c_str();
    //startParam.param.normaluserStart.participantId = CUtils::s2ws(strParticipantId).c_str();
    //startParam.param.normaluserStart.meetingNumber = 201229199;
//     startParam.param.normaluserStart.vanityID = L"";
     startParam.param.normaluserStart.participantId = L"";
    startParam.param.normaluserStart.isVideoOff = m_btnNormalStartIsVideoOff.GetCheck() == 1 ? false : true;
    startParam.param.normaluserStart.isAudioOff = m_btnNormalStartIsVideoOff.GetCheck() == 1 ? false : true;
    startParam.param.normaluserStart.isDirectShareDesktop = m_btnNormalStartIsDirectShareDesktop.GetCheck() == 1 ? true : false;

    err = CZhumuSdkAgency::GetInstance()->StartAppointmentMeeting(startParam);
    {
        CString strMsg;
        strMsg.Format(_T("%d = StartMeetingNormal(...)"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
    }
}


void CZhumuSdkProgressDlg::OnBnClickedButton5()
{
    CString strNormalJoinMeetingNumber;
    CString strNormalJoinVanityID;
    CString strNormalJoinUserName;
    CString strNormalJoinPsw;
    CString strNormalJoinParticipantId;
    CString strNormalJoinWebinarToken;

    m_editNormalJoinMeetingNumber.GetWindowTextW(strNormalJoinMeetingNumber);
    m_editNormalJoinVanityID.GetWindowTextW(strNormalJoinVanityID);
    m_editNormalJoinUserName.GetWindowTextW(strNormalJoinUserName);
    m_editNormalJoinPsw.GetWindowTextW(strNormalJoinPsw);
    m_editNormalJoinParticipantId.GetWindowTextW(strNormalJoinParticipantId);
    m_editNormalJoinWebinarToken.GetWindowTextW(strNormalJoinWebinarToken);


    std::string strVanityID = CT2A(strNormalJoinVanityID);;
    std::string strUserName = CT2A(strNormalJoinUserName);;
    std::string strPsw = CT2A(strNormalJoinPsw);;
    std::string strParticipantId = CT2A(strNormalJoinParticipantId);;
    std::string strWebinarToken = CT2A(strNormalJoinWebinarToken);;


    // TODO: �ڴ���ӿؼ�֪ͨ����������
    SDKError err = CZhumuSdkAgency::GetInstance()->CreateMeetingService();
    {
        CString strMsg;
        strMsg.Format(_T("%d = CreateMeetingService()"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
    }

    JoinParam joinParam;
    joinParam.userType = SDK_UT_NORMALUSER;
    joinParam.param.normaluserJoin.meetingNumber = _ttoi64(strNormalJoinMeetingNumber);
    joinParam.param.normaluserJoin.userName = CUtils::s2ws(strUserName).c_str();
    joinParam.param.normaluserJoin.psw = CUtils::s2ws(strPsw).c_str();
    joinParam.param.normaluserJoin.participantId = CUtils::s2ws(strParticipantId).c_str();
    joinParam.param.normaluserJoin.isVideoOff = m_btnNormalJoinIsVideoOff.GetCheck() == 1 ? true : false;
    joinParam.param.normaluserJoin.isAudioOff = m_btnNormalJoinIsAudioOff.GetCheck() == 1 ? true : false;
    joinParam.param.normaluserJoin.isDirectShareDesktop = m_btnNormalJoinIsDirectShareDesktop.GetCheck() == 1 ? true : false;

    err = CZhumuSdkAgency::GetInstance()->JoinMeeting(joinParam);
    {
        CString strMsg;
        strMsg.Format(_T("%d = JoinMeetingNormal(joinParam)"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
    }
}
