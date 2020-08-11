
// ZhumuSdkExDemoDlg.h : 头文件
//

#pragma once
#include "ZhumuSdkEx.h"
#include "ZhumuSdkEx_def.h"
#include "ZhumuSdkEx_Event.h"
#include "afxwin.h"
#include "afxcmn.h"


using namespace ZHUMUSDKEX_NAMESPACE;
// CZhumuSdkExDemoDlg 对话框
class CZhumuSdkExDemoDlg
    : public CDialogEx
    , public ZHUMUSDKEX_NAMESPACE::ZhumuSdkEx_Event
{
// 构造
public:
	CZhumuSdkExDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZHUMUSDKEXDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
    void AddMsg(CString strMsg);        // 添加反馈消息

public:
    afx_msg void OnBnClickedButton1();  // 创建SDK
    afx_msg void OnBnClickedButton2();  // 初始化SDK
    afx_msg void OnBnClickedButton3();  // 销毁SDK
    afx_msg void OnBnClickedButton4();  // 登录SDK



    CEdit m_editUserName;
    CEdit m_editPassword;
    CRichEditCtrl m_richeditMsg;
};
