
// ZhumuSdkExDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "ZhumuSdkEx.h"
#include "ZhumuSdkEx_def.h"
#include "ZhumuSdkEx_Event.h"
#include "afxwin.h"
#include "afxcmn.h"


using namespace ZHUMUSDKEX_NAMESPACE;
// CZhumuSdkExDemoDlg �Ի���
class CZhumuSdkExDemoDlg
    : public CDialogEx
    , public ZHUMUSDKEX_NAMESPACE::ZhumuSdkEx_Event
{
// ����
public:
	CZhumuSdkExDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZHUMUSDKEXDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
    virtual void onInitRet(SDKError status);
    //auth event
    virtual void onAuthRet(AuthResult status);
    //login event
    virtual void onLoginRet(LOGINSTATUS status);
    //meeting status event
    virtual void onMeetingStatus(MeetingStatus status, MeetingFailCode code);
    //exit app
    virtual void onExitApp();


public:
    void AddMsg(CString strMsg);        // ��ӷ�����Ϣ

public:
    afx_msg void OnBnClickedButton1();  // ����SDK
    afx_msg void OnBnClickedButton2();  // ��ʼ��SDK
    afx_msg void OnBnClickedButton3();  // ����SDK
    afx_msg void OnBnClickedButton4();  // ��¼SDK



    CEdit m_editUserName;
    CEdit m_editPassword;
    CRichEditCtrl m_richeditMsg;
};
