
// ZhumuSdkExDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZhumuSdkExDemo.h"
#include "ZhumuSdkExDemoDlg.h"
#include "afxdialogex.h"
#include "ZhumuSdkEx.h"
#include "SwtichAudioDev.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CZhumuSdkExDemoDlg 对话框



CZhumuSdkExDemoDlg::CZhumuSdkExDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_ZHUMUSDKEXDEMO_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pSettingService = nullptr;
}

void CZhumuSdkExDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_USERNAME, m_editUserName);
    DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
    DDX_Control(pDX, IDC_RICHEDIT21, m_richeditMsg);

    DDX_Control(pDX, IDC_EDIT_NORMALSTARTMEETINGNUMBER, m_editNormalStartMeetingNumber);
    DDX_Control(pDX, IDC_EDIT_NORMALSTARTVANITYID, m_editNormalStartVanityID);
    DDX_Control(pDX, IDC_EDIT_NORMALSTARTPARTICIPANTID, m_editNormalStartParticipantId);
    DDX_Control(pDX, IDC_NORMALSTARTISVIDEOOFF, m_btnNormalStartIsVideoOff);
    DDX_Control(pDX, IDC_CHECK_NORMALSTARTISAUDIOOFF, m_btnNormalStartIsAudioOff);
    DDX_Control(pDX, IDC_CHECK_NORMALSTARTISDIRECTSHAREDESKTOP, m_btnNormalStartIsDirectShareDesktop);

    DDX_Control(pDX, IDC_EDIT_NORMALJOINMEETINGNUMBER, m_editNormalJoinMeetingNumber);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINVANITYID, m_editNormalJoinVanityID);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINUSERNAME, m_editNormalJoinUserName);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINPSW, m_editNormalJoinPsw);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINPARTICIPANTID, m_editNormalJoinParticipantId);
    DDX_Control(pDX, IDC_EDIT_NORMALJOINWEBINARTOKEN, m_editNormalJoinWebinarToken);
    DDX_Control(pDX, IDC_CHECK_NORMALJOINISVIDEOOFF, m_btnNormalJoinIsVideoOff);
    DDX_Control(pDX, IDC_CHECK_NORMALJOINISAUDIOOFF, m_btnNormalJoinIsAudioOff);
    DDX_Control(pDX, IDC_CHECK_NORMALJOINISDIRECTSHAREDESKTOP, m_btnNormalJoinIsDirectShareDesktop);
    DDX_Control(pDX, IDC_CHECK_AUTOFULLSCREEN, m_btnAutoFullScreen);
    DDX_Control(pDX, IDC_CHECK_ALWAYSSHOWCTRLBAR, m_btnAlwaysShowCtrlBar);
    DDX_Control(pDX, IDC_CHECK_ALWAYSJOINMEETINGBEFOREADMIN, m_btnAlwaysJoinMeetingBeforeAdmin);
    DDX_Control(pDX, IDC_CHECK_AUTOJOINAUDIO, m_btnAutoJoinAudio);
    DDX_Control(pDX, IDC_CHECK_PARTICIPANTSUNMUTE, m_btnParticipantsUnmute);
    DDX_Control(pDX, IDC_CHECK_ECHOCANCELLATION, m_btnEchoCancellation);
    DDX_Control(pDX, IDC_CHECK_HDVIDEO, m_btnHDVideo);
    DDX_Control(pDX, IDC_CHECK_AUTOTURNOFFVIDEO, m_btnAutoTurnOffVideo);
    DDX_Control(pDX, IDC_COMBO1, m_comboxMicList);
    DDX_Control(pDX, IDC_EDIT_EXEPATH, m_editExePath);
    DDX_Control(pDX, IDC_EDIT_NORMALSTARTMEETINGNUMBER2, m_editBindingName);
    DDX_Control(pDX, IDC_EDIT_NORMALSTARTMEETINGNUMBER3, m_editSupportUrl);
    DDX_Control(pDX, IDC_EDIT_NORMALSTARTMEETINGNUMBER4, m_editWebDomain);
    DDX_Control(pDX, IDC_EDIT_NORMALSTARTMEETINGNUMBER5, m_editTimeOut);
    DDX_Control(pDX, IDC_NORMALSTARTISVIDEOOFF2, m_btnAsynchronous);
    DDX_Control(pDX, IDC_COMBO2, m_conboxLanguageId);
}

BEGIN_MESSAGE_MAP(CZhumuSdkExDemoDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CZhumuSdkExDemoDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CZhumuSdkExDemoDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CZhumuSdkExDemoDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CZhumuSdkExDemoDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CZhumuSdkExDemoDlg::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON6, &CZhumuSdkExDemoDlg::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CZhumuSdkExDemoDlg::OnBnClickedButton7)
    ON_BN_CLICKED(IDC_BUTTON8, &CZhumuSdkExDemoDlg::OnBnClickedButton8)
    ON_BN_CLICKED(IDC_CHECK_AUTOFULLSCREEN, &CZhumuSdkExDemoDlg::OnBnClickedCheckAutofullscreen)
    ON_BN_CLICKED(IDC_CHECK_ALWAYSSHOWCTRLBAR, &CZhumuSdkExDemoDlg::OnBnClickedCheckAlwaysshowctrlbar)
    ON_BN_CLICKED(IDC_CHECK_ALWAYSJOINMEETINGBEFOREADMIN, &CZhumuSdkExDemoDlg::OnBnClickedCheckAlwaysjoinmeetingbeforeadmin)
    ON_BN_CLICKED(IDC_CHECK_AUTOJOINAUDIO, &CZhumuSdkExDemoDlg::OnBnClickedCheckAutojoinaudio)
    ON_BN_CLICKED(IDC_CHECK_PARTICIPANTSUNMUTE, &CZhumuSdkExDemoDlg::OnBnClickedCheckParticipantsunmute)
    ON_BN_CLICKED(IDC_CHECK_ECHOCANCELLATION, &CZhumuSdkExDemoDlg::OnBnClickedCheckEchocancellation)
    ON_BN_CLICKED(IDC_CHECK_HDVIDEO, &CZhumuSdkExDemoDlg::OnBnClickedCheckHdvideo)
    ON_BN_CLICKED(IDC_CHECK_AUTOTURNOFFVIDEO, &CZhumuSdkExDemoDlg::OnBnClickedCheckAutoturnoffvideo)
    ON_BN_CLICKED(IDC_BUTTON9, &CZhumuSdkExDemoDlg::OnBnClickedButton9)
    ON_BN_CLICKED(IDC_BUTTON10, &CZhumuSdkExDemoDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CZhumuSdkExDemoDlg 消息处理程序

BOOL CZhumuSdkExDemoDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
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

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码
    m_editPassword.SetWindowTextW(_T("zm123456"));
    m_editUserName.SetWindowTextW(_T("mengxw@suirui.com"));
    m_editExePath.SetWindowTextW(_T("D:\\07 GitHub\\01 Suirui\\ZhumuSdk_SHLX\\ZhumuSdkProgress\\Bin\\Debug\\ZhumuSdkProgress.exe"));

    m_editNormalStartMeetingNumber.SetWindowTextW(_T("202444421"));
    m_editNormalStartVanityID.SetWindowTextW(_T("mengxw@suirui.com"));
    m_editNormalStartParticipantId.SetWindowTextW(_T("mengxw@suirui.com"));
    m_btnNormalStartIsVideoOff.SetCheck(1);
    m_btnNormalStartIsAudioOff.SetCheck(0);
    m_btnNormalStartIsDirectShareDesktop.SetCheck(0);

    m_editNormalJoinMeetingNumber.SetWindowTextW(_T("202444421"));
    m_editNormalJoinVanityID.SetWindowTextW(_T("zm123456"));
    m_editNormalJoinUserName.SetWindowTextW(_T("zm123456"));
    m_editNormalJoinPsw.SetWindowTextW(_T("zm123456"));
    m_editNormalJoinParticipantId.SetWindowTextW(_T("zm123456"));
    m_editNormalJoinWebinarToken.SetWindowTextW(_T("zm123456"));
    m_btnNormalJoinIsVideoOff.SetCheck(1);
    m_btnNormalJoinIsAudioOff.SetCheck(1);
    m_btnNormalJoinIsDirectShareDesktop.SetCheck(0);

    m_editBindingName.SetWindowTextW(_T("TiYiYun"));
    m_editSupportUrl.SetWindowTextW(_T("https://www.cloudmeeting.com"));
    m_editWebDomain.SetWindowTextW(_T("https://launcher.zhumu.me"));
    m_editTimeOut.SetWindowTextW(_T("10000"));

    CSwtichAudioDev::Instance()->EnumAudioDevice();
    int ictn = CSwtichAudioDev::Instance()->m_strFriedlyName.GetCount();
    for (int i = 0; i < ictn; i++)
    {
        m_comboxMicList.AddString(CSwtichAudioDev::Instance()->m_strFriedlyName.GetAt(i));
        m_comboxMicList.SetItemData(i, i);
    }
    m_comboxMicList.SetCurSel(0);

    m_conboxLanguageId.AddString(_T("LANGUAGE_English"));
    m_conboxLanguageId.SetItemData(0, 1);
    m_conboxLanguageId.AddString(_T("LANGUAGE_Chinese_Simplified"));
    m_conboxLanguageId.SetItemData(1, 2);
    m_conboxLanguageId.AddString(_T("LANGUAGE_Chinese_Traditional"));
    m_conboxLanguageId.SetItemData(2, 3);
    m_conboxLanguageId.SetCurSel(1);


    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZhumuSdkExDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZhumuSdkExDemoDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZhumuSdkExDemoDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CZhumuSdkExDemoDlg::onInitRet(SDKError status)
{
    CString strMsg;
    strMsg.Format(_T("onInitRet %d"), status);
    AddMsg(strMsg);
}

void CZhumuSdkExDemoDlg::onAuthRet(AuthResult status)
{
    CString strMsg;
    strMsg.Format(_T("onAuthRet %d"), status);
    AddMsg(strMsg);
}

void CZhumuSdkExDemoDlg::onLoginRet(LOGINSTATUS status)
{
    CString strMsg;
    strMsg.Format(_T("onLoginRet %d"), status);
    AddMsg(strMsg);
}

void CZhumuSdkExDemoDlg::onMeetingStatus(MeetingStatus status, MeetingFailCode code)
{
    CString strMsg;
    strMsg.Format(_T("MeetingStatus %d, MeetingFailCode %d"), status, code);
    AddMsg(strMsg);
}

void CZhumuSdkExDemoDlg::onExitApp()
{

}

void CZhumuSdkExDemoDlg::AddMsg(CString strMsg)
{
    m_richeditMsg.SetSel(-1, -1);
    // 插入文本
    m_richeditMsg.ReplaceSel(_T("\r\n=========================\r\n"));
    m_richeditMsg.ReplaceSel(strMsg);
    m_richeditMsg.ReplaceSel(_T("\r\n=========================\r\n"));
    m_richeditMsg.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


void CZhumuSdkExDemoDlg::OnBnClickedButton1()
{

    CString strPath;
    m_editExePath.GetWindowTextW(strPath);
    std::string strPathTemp = CT2A(strPath);

    SDKError err = ZHUMUSDKEX_NAMESPACE::Zhumu_CreateSDK(this, strPathTemp.c_str());

    CString strMsg;
    strMsg.Format(_T(" SDKError %d = ZHUMUSDKEX_NAMESPACE::Zhumu_CreateSDK(crateParam);"), err);
    AddMsg(strMsg);
}


void CZhumuSdkExDemoDlg::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码

    CString cstrBindingName;
    CString cstrSupportUrl;
    CString cstrWebDomain;
    CString cstrTimeOut;

    m_editBindingName.GetWindowTextW(cstrBindingName);
    m_editSupportUrl.GetWindowTextW(cstrSupportUrl);
    m_editWebDomain.GetWindowTextW(cstrWebDomain);
    m_editTimeOut.GetWindowTextW(cstrTimeOut);

    std::string strBindingName = CT2A(cstrBindingName);
    std::string strSupportUrl = CT2A(cstrSupportUrl);
    std::string strWebDomain = CT2A(cstrWebDomain);

    ZmSdkInitParam initParam;
    initParam.bindingName = const_cast<char*>(strBindingName.c_str()); 
    initParam.supportUrl = const_cast<char*>(strSupportUrl.c_str());
    initParam.webDomain = const_cast<char*>(strWebDomain.c_str());
    initParam.asynchronous = m_btnAsynchronous.GetCheck() == 1 ? true : false;
    initParam.timeOut = _ttoi(cstrTimeOut);                  // 同步超时时间 单位毫秒 默认10秒

    int nIndex = m_conboxLanguageId.GetCurSel();
    if (-1 == nIndex)
    {
        return;
    }
    int nData = m_conboxLanguageId.GetItemData(nIndex);
    SDK_LANGUAGE_ID languageId = SDK_LANGUAGE_ID(m_conboxLanguageId.GetItemData(nIndex));

    initParam.language = languageId;

    SDKError err = ZHUMUSDKEX_NAMESPACE::Zhumu_InitSDK(initParam);

    CString strMsg;
    strMsg.Format(_T(" SDKError %d =  ZHUMUSDKEX_NAMESPACE::Zhumu_InitSDK(initParam);"), err);
    AddMsg(strMsg);

    if (nullptr == m_pSettingService)
    {
        err = ZHUMUSDKEX_NAMESPACE::Zhumu_CreateSettingService(&m_pSettingService);
        CString strMsg;
        strMsg.Format(_T(" SDKError %d =  ZHUMUSDKEX_NAMESPACE::Zhumu_CreateSettingService(&m_pSettingService);"), err);
        AddMsg(strMsg);
    }
}


void CZhumuSdkExDemoDlg::OnBnClickedButton3()
{
    // TODO: 在此添加控件通知处理程序代码

    SDKError err = ZHUMUSDKEX_NAMESPACE::Zhumu_DestorySDK();

    CString strMsg;
    strMsg.Format(_T(" SDKError %d = ZHUMUSDKEX_NAMESPACE::Zhumu_DestorySDK();"), err);
    AddMsg(strMsg);
}


void CZhumuSdkExDemoDlg::OnBnClickedButton4()
{
    CString strUserName;
    CString strPassword;

    m_editUserName.GetWindowTextW(strUserName);
    m_editPassword.GetWindowTextW(strPassword);

    std::string strName = CT2A(strUserName);
    std::string strUserPassword = CT2A(strPassword);

    ZmSdkLoginParam loginParam;
    loginParam.account = const_cast<char*>(strName.c_str());
    loginParam.password = const_cast<char*>(strUserPassword.c_str());

    SDKError err = ZHUMUSDKEX_NAMESPACE::Zhumu_SLoginSDK(loginParam);
    CString strMsg;
    strMsg.Format(_T(" SDKError %d = ZHUMUSDKEX_NAMESPACE::Zhumu_SLoginSDK(loginParam);"), err);
    AddMsg(strMsg);
}

void CZhumuSdkExDemoDlg::OnBnClickedButton5()
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

    ZmStartAppointmentMeetingParam startParam;
    startParam.meetingNumber = _ttoi64(strNormalStartMeetingNumber);
    startParam.participantId = const_cast<char*>(strParticipantId.c_str());
    startParam.isVideoOff = m_btnNormalStartIsVideoOff.GetCheck() == 1 ? false : true;
    startParam.isAudioOff = m_btnNormalStartIsAudioOff.GetCheck() == 1 ? false : true;
    startParam.isDirectShareDesktop = m_btnNormalStartIsDirectShareDesktop.GetCheck() == 1 ? true : false;

    SDKError err = ZHUMUSDKEX_NAMESPACE::Zhumu_StartAppointmentMeeting(startParam);
    CString strMsg;
    strMsg.Format(_T(" SDKError %d = ZHUMUSDKEX_NAMESPACE::Zhumu_NormalStartMeeting(startParam);"), err);
    AddMsg(strMsg);
}


void CZhumuSdkExDemoDlg::OnBnClickedButton6()
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

    ZmJoinMeetingParam joinParam;
    joinParam.meetingNumber = _ttoi64(strNormalJoinMeetingNumber);
    joinParam.userName = const_cast<char*>(strUserName.c_str());
    joinParam.psw = const_cast<char*>(strPsw.c_str());
    joinParam.isVideoOff = m_btnNormalJoinIsVideoOff.GetCheck() == 1 ? true : false;
    joinParam.isAudioOff = m_btnNormalJoinIsAudioOff.GetCheck() == 1 ? true : false;
    joinParam.isDirectShareDesktop = m_btnNormalJoinIsDirectShareDesktop.GetCheck() == 1 ? true : false;

    SDKError err = Zhumu_JoinMeeting(joinParam);
    {
        CString strMsg;
        strMsg.Format(_T("%d = JoinMeetingNormal(joinParam)"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
    }
}

void CZhumuSdkExDemoDlg::OnBnClickedButton7()
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

    ZmStartInstantMeetingParam startParam;
    startParam.meetingTopic = const_cast<char*>(strVanityID.c_str());
    startParam.meetingParticipants = const_cast<char*>(strParticipantId.c_str());
    startParam.isVideoOff = m_btnNormalStartIsVideoOff.GetCheck() == 1 ? false : true;
    startParam.isAudioOff = m_btnNormalStartIsAudioOff.GetCheck() == 1 ? false : true;
    startParam.isDirectShareDesktop = m_btnNormalStartIsDirectShareDesktop.GetCheck() == 1 ? true : false;

    SDKError err = ZHUMUSDKEX_NAMESPACE::Zhumu_StartInstantMeeting(startParam);
    CString strMsg;
    strMsg.Format(_T(" SDKError %d = ZHUMUSDKEX_NAMESPACE::Zhumu_StartInstantMeeting(startParam);"), err);
    AddMsg(strMsg);
}


void CZhumuSdkExDemoDlg::OnBnClickedButton8()
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

    ZmAnonymityJoinMeetingParam joinParam;
    joinParam.meetingNumber = _ttoi64(strNormalJoinMeetingNumber);
    joinParam.userName = const_cast<char*>(strUserName.c_str());
    joinParam.psw = const_cast<char*>(strPsw.c_str());
    joinParam.isVideoOff = m_btnNormalJoinIsVideoOff.GetCheck() == 1 ? true : false;
    joinParam.isAudioOff = m_btnNormalJoinIsAudioOff.GetCheck() == 1 ? true : false;
    joinParam.isDirectShareDesktop = m_btnNormalJoinIsDirectShareDesktop.GetCheck() == 1 ? true : false;

    SDKError err = Zhumu_AnonymityJoinMeeting(joinParam);
    {
        CString strMsg;
        strMsg.Format(_T("%d = JoinMeetingNormal(joinParam)"), err);
        MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
        AddMsg(strMsg);
    }
}







void CZhumuSdkExDemoDlg::OnBnClickedCheckAutofullscreen()
{
    if (nullptr != m_pSettingService)
    {
        bool bEnable = m_btnAutoFullScreen.GetCheck() == 1 ? true : false;

        SDKError err = m_pSettingService->EnableAutoFullScreenVideoWhenJoinMeeting(bEnable);
        {
            CString strMsg;
            strMsg.Format(_T("%d = EnableAutoFullScreenVideoWhenJoinMeeting()"), err);
            MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
            AddMsg(strMsg);
        }
    }
}


void CZhumuSdkExDemoDlg::OnBnClickedCheckAlwaysshowctrlbar()
{
    if (nullptr != m_pSettingService)
    {
        bool bEnable = m_btnAlwaysShowCtrlBar.GetCheck() == 1 ? true : false;

        SDKError err = m_pSettingService->EanbleAlwaysDisplayedMeetingCtrlBar(bEnable);
        {
            CString strMsg;
            strMsg.Format(_T("%d = EanbleAlwaysDisplayedMeetingCtrlBar()"), err);
            MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
            AddMsg(strMsg);
        }
    }
}


void CZhumuSdkExDemoDlg::OnBnClickedCheckAlwaysjoinmeetingbeforeadmin()
{
    if (nullptr != m_pSettingService)
    {
        bool bEnable = m_btnAlwaysJoinMeetingBeforeAdmin.GetCheck() == 1 ? true : false;

        SDKError err = m_pSettingService->EanbleAlwaysJoinMeetingbeforeAdmin(bEnable);
        {
            CString strMsg;
            strMsg.Format(_T("%d = EanbleAlwaysJoinMeetingbeforeAdmin()"), err);
            MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
            AddMsg(strMsg);
        }
    }
}


void CZhumuSdkExDemoDlg::OnBnClickedCheckAutojoinaudio()
{
    if (nullptr != m_pSettingService)
    {
        bool bEnable = m_btnAutoJoinAudio.GetCheck() == 1 ? true : false;

        SDKError err = m_pSettingService->EnableAutoJoinAudio(bEnable);
        {
            CString strMsg;
            strMsg.Format(_T("%d = EnableAutoJoinAudio()"), err);
            MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
            AddMsg(strMsg);
        }
    }
}


void CZhumuSdkExDemoDlg::OnBnClickedCheckParticipantsunmute()
{
    if (nullptr != m_pSettingService)
    {
        bool bEnable = m_btnParticipantsUnmute.GetCheck() == 1 ? true : false;

        SDKError err = m_pSettingService->EnableParticipantsUnmuteWhenMeeting(bEnable);
        {
            CString strMsg;
            strMsg.Format(_T("%d = EnableParticipantsUnmuteWhenMeeting()"), err);
            MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
            AddMsg(strMsg);
        }
    }
}


void CZhumuSdkExDemoDlg::OnBnClickedCheckEchocancellation()
{
    if (nullptr != m_pSettingService)
    {
        bool bEnable = m_btnEchoCancellation.GetCheck() == 1 ? true : false;

        SDKError err = m_pSettingService->EnableEchoCancellation(bEnable);
        {
            CString strMsg;
            strMsg.Format(_T("%d = EnableEchoCancellation()"), err);
            MessageBox(strMsg, _T("Message"), MB_OKCANCEL | MB_ICONINFORMATION);
            AddMsg(strMsg);
        }
    }
}


void CZhumuSdkExDemoDlg::OnBnClickedCheckHdvideo()
{
    if (nullptr != m_pSettingService)
    {
        bool bEnable = m_btnHDVideo.GetCheck() == 1 ? true : false;

        SDKError err = m_pSettingService->EnableHDVideo(bEnable);
        {
            CString strMsg;
            strMsg.Format(_T("%d = EnableHDVideo()"), err);
            AddMsg(strMsg);
        }
    }
}


void CZhumuSdkExDemoDlg::OnBnClickedCheckAutoturnoffvideo()
{
    if (nullptr != m_pSettingService)
    {
        bool bEnable = m_btnAutoTurnOffVideo.GetCheck() == 1 ? true : false;

        SDKError err = m_pSettingService->EnableAutoTurnOffVideoWhenJoinMeeting(bEnable);
        {
            CString strMsg;
            strMsg.Format(_T("%d = EnableAutoTurnOffVideoWhenJoinMeeting()"), err);
            AddMsg(strMsg);
        }
    }
}


void CZhumuSdkExDemoDlg::OnBnClickedButton9()
{
    //SDKError err = Zhumu_DirectSharing();
    //{
    //    CString strMsg;
    //    strMsg.Format(_T("%d =Zhumu_DirectSharing()"), err);
    //    AddMsg(strMsg);
    //}
}


void CZhumuSdkExDemoDlg::OnBnClickedButton10()
{
    int nIndex = m_comboxMicList.GetCurSel();
    if (-1 == nIndex)
    {
        return;
    }
    int nData = m_comboxMicList.GetItemData(nIndex);
    CString strName;
    CString strId;
    m_comboxMicList.GetLBText(nIndex, strName);
    strId = CSwtichAudioDev::Instance()->m_strId.GetAt(nData);

    std::string strMicName = CT2A(strName);
    std::string strMicId = CT2A(strId);

    if (nullptr != m_pSettingService)
    {
        SDKError err = m_pSettingService->SelectMic(strMicId.c_str(),strMicName.c_str());
        {
            CString strMsg;
            strMsg.Format(_T("%d = SelectMic(%s, %s"), err, strName, strId);
            AddMsg(strMsg);
        }
    }
}
