
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
}

BEGIN_MESSAGE_MAP(CZhumuSdkProgressDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

    ON_REGISTERED_MESSAGE(WMUSER_BUSINESS_QUIT, &CZhumuSdkProgressDlg::OnQuitProgress)
    ON_REGISTERED_MESSAGE(WMUSER_BUSINESS_CUSTOM_ERROR, &CZhumuSdkProgressDlg::OnCustomErrorMessage)
    ON_REGISTERED_MESSAGE(WMUSER_INIT_ZHUMUSDK, &CZhumuSdkProgressDlg::OnInitZhumuSDk)
    ON_REGISTERED_MESSAGE(WMUSER_LOGIN_ZHUMUSDK, &CZhumuSdkProgressDlg::OnLoginZhumuSDk)
    

    ON_BN_CLICKED(IDC_BUTTON1, &CZhumuSdkProgressDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CZhumuSdkProgressDlg::OnBnClickedButton2)
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

    // �˳�����
    OnOK();
    LOGI << "[" << __FUNCTION__ << "] Program normal exit!"<< std::endl;
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
