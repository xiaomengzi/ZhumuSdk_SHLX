
// ZhumuSdkExDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ZhumuSdkExDemo.h"
#include "ZhumuSdkExDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CZhumuSdkExDemoDlg �Ի���



CZhumuSdkExDemoDlg::CZhumuSdkExDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_ZHUMUSDKEXDEMO_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZhumuSdkExDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_USERNAME, m_editUserName);
    DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
    DDX_Control(pDX, IDC_RICHEDIT21, m_richeditMsg);
}

BEGIN_MESSAGE_MAP(CZhumuSdkExDemoDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CZhumuSdkExDemoDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CZhumuSdkExDemoDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CZhumuSdkExDemoDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CZhumuSdkExDemoDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CZhumuSdkExDemoDlg ��Ϣ�������

BOOL CZhumuSdkExDemoDlg::OnInitDialog()
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

    // TODO: �ڴ���Ӷ���ĳ�ʼ������
    m_editPassword.SetWindowTextW(_T("zm123456"));
    m_editUserName.SetWindowTextW(_T("mengxw@suirui.com"));

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZhumuSdkExDemoDlg::OnPaint()
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
    // �����ı�
    m_richeditMsg.ReplaceSel(_T("\r\n=========================\r\n"));
    m_richeditMsg.ReplaceSel(strMsg);
    m_richeditMsg.ReplaceSel(_T("\r\n=========================\r\n"));
    m_richeditMsg.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


void CZhumuSdkExDemoDlg::OnBnClickedButton1()
{
    SDKError err = ZHUMUSDKEX_NAMESPACE::Zhumu_CreateSDK(this, "D:\\07 GitHub\\01 Suirui\\ZhumuSdk_SHLX\\ZhumuSdkProgress\\Bin\\Debug\\ZhumuSdkProgress.exe");

    CString strMsg;
    strMsg.Format(_T(" SDKError %d = ZHUMUSDKEX_NAMESPACE::Zhumu_CreateSDK(crateParam);"), err);
    AddMsg(strMsg);
}


void CZhumuSdkExDemoDlg::OnBnClickedButton2()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    ZmSdkInitParam initParam;
    SDKError err = ZHUMUSDKEX_NAMESPACE::Zhumu_InitSDK(initParam);

    CString strMsg;
    strMsg.Format(_T(" SDKError %d =  ZHUMUSDKEX_NAMESPACE::Zhumu_InitSDK(initParam);"), err);
    AddMsg(strMsg);
}


void CZhumuSdkExDemoDlg::OnBnClickedButton3()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    
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

    ZHUMUSDKEX_NAMESPACE::Zhumu_SLoginSDK(loginParam);

}


