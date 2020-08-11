
// ZhumuSdkProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ZhumuSdkProgress.h"
#include "ZhumuSdkProgressDlg.h"
#include "afxdialogex.h"
#include "BusinessLogic.h"
#include "CustomData.h"
#include "plog\Log.h"
#include <winuser.h>

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

    //���ؽ���
    int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
    int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
    SetWindowPos(NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOZORDER);  //����0����,�Ƶ������  ����:MoveWindow(0,0,0,0);
    ShowWindow(SW_HIDE);
    ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);  //�Ƴ�������ͼ����ʾ

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


LRESULT CZhumuSdkProgressDlg::OnQuitProgress(WPARAM wParam, LPARAM lParam)
{
    // �رշ���
    CBusinessLogic::GetInstance()->StopTcpServer();

    // ������ĿSDK

    // �˳�����
    OnOK();
    LOGI << "Program normal exit";
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
        switch ((int)lParam)
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
    
    return 0;
}
