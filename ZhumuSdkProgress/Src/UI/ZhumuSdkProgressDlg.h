
// ZhumuSdkProgressDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CZhumuSdkProgressDlg 对话框
class CZhumuSdkProgressDlg : public CDialogEx
{
// 构造
public:
	CZhumuSdkProgressDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZHUMUSDKPROGRESS_DIALOG };
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
    void CustomErrorMessage(CString strContent, int nType);

public:
    // 退出进程
    afx_msg LRESULT OnQuitProgress(WPARAM wParam, LPARAM lParam);
    // 错误消息提示
    afx_msg LRESULT OnCustomErrorMessage(WPARAM wParam, LPARAM lParam);
    // 初始化SDK
    afx_msg LRESULT OnInitZhumuSDk(WPARAM wParam, LPARAM lParam);
    // 登录SDK
    afx_msg LRESULT OnLoginZhumuSDk(WPARAM wParam, LPARAM lParam);
    // 开启预约会议
    afx_msg LRESULT OnStartAppointmentMeetingZhumuSDK(WPARAM wParam, LPARAM lParam);
    // 开启即时会议
    afx_msg LRESULT OnStartInstantMeetingZhumuSDK(WPARAM wParam, LPARAM lParam);
    // 加入会议
    afx_msg LRESULT OnJoinMeetingZhumuSDK(WPARAM wParam, LPARAM lParam);
    // 匿名加入会议
    afx_msg LRESULT OnAnonymityJoinMeetingZhumuSDK(WPARAM wParam, LPARAM lParam);
    
    

    
public:
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();

    CEdit m_editUserName;
    CEdit m_editPassword;
    CEdit m_editNormalJoinMeetingNumber;
    CEdit m_editNormalJoinVanityID;
    CEdit m_editNormalJoinUserName;
    CEdit m_editNormalJoinPsw;
    CEdit m_editNormalJoinParticipantId;
    CEdit m_editNormalJoinWebinarToken;
    CButton m_btnNormalJoinIsVideoOff;
    CButton m_btnNormalJoinIsAudioOff;
    CButton m_btnNormalJoinIsDirectShareDesktop;

    CEdit m_editNormalStartMeetingNumber;
    CEdit m_editNormalStartVanityID;
    CEdit m_editNormalStartParticipantId;
    CButton m_btnNormalStartIsVideoOff;
    CButton m_btnNormalStartIsAudioOff;
    CButton m_btnNormalStartIsDirectShareDesktop;
};
