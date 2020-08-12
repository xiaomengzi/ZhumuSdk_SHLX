
// ZhumuSdkProgressDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CZhumuSdkProgressDlg �Ի���
class CZhumuSdkProgressDlg : public CDialogEx
{
// ����
public:
	CZhumuSdkProgressDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZHUMUSDKPROGRESS_DIALOG };
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
    void CustomErrorMessage(CString strContent, int nType);

public:
    // �˳�����
    afx_msg LRESULT OnQuitProgress(WPARAM wParam, LPARAM lParam);
    // ������Ϣ��ʾ
    afx_msg LRESULT OnCustomErrorMessage(WPARAM wParam, LPARAM lParam);
    // ��ʼ��SDK
    afx_msg LRESULT OnInitZhumuSDk(WPARAM wParam, LPARAM lParam);
    // ��¼SDK
    afx_msg LRESULT OnLoginZhumuSDk(WPARAM wParam, LPARAM lParam);
    // ����ԤԼ����
    afx_msg LRESULT OnStartAppointmentMeetingZhumuSDK(WPARAM wParam, LPARAM lParam);
    // ������ʱ����
    afx_msg LRESULT OnStartInstantMeetingZhumuSDK(WPARAM wParam, LPARAM lParam);
    // �������
    afx_msg LRESULT OnJoinMeetingZhumuSDK(WPARAM wParam, LPARAM lParam);
    // �����������
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
