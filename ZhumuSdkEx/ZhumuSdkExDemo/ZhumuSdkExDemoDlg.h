
// ZhumuSdkExDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "ZhumuSdkEx.h"
#include "ZhumuSdkEx_def.h"
#include "ZhumuSdkEx_Event.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "setting_service_interface.h"


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
    virtual void OnMeetingSettingResult(SettingServerType tyep, SDKError errorCode);
public:
    void AddMsg(CString strMsg);        // ��ӷ�����Ϣ

public:
    afx_msg void OnBnClickedButton1();  // ����SDK
    afx_msg void OnBnClickedButton2();  // ��ʼ��SDK
    afx_msg void OnBnClickedButton3();  // ����SDK
    afx_msg void OnBnClickedButton4();  // ��¼SDK
    afx_msg void OnBnClickedButton5();  // ��¼�û���������
    afx_msg void OnBnClickedButton6();
    afx_msg void OnBnClickedButton7();
    afx_msg void OnBnClickedButton8();

    afx_msg void OnBnClickedCheckAutofullscreen();
    afx_msg void OnBnClickedCheckAlwaysshowctrlbar();
    afx_msg void OnBnClickedCheckAlwaysjoinmeetingbeforeadmin();
    afx_msg void OnBnClickedCheckAutojoinaudio();
    afx_msg void OnBnClickedCheckParticipantsunmute();
    afx_msg void OnBnClickedCheckEchocancellation();
    afx_msg void OnBnClickedCheckHdvideo();
    afx_msg void OnBnClickedCheckAutoturnoffvideo();

    CEdit m_editUserName;
    CEdit m_editPassword;
    CRichEditCtrl m_richeditMsg;
    CEdit m_editNormalStartMeetingNumber;
    CEdit m_editNormalStartVanityID;
    CEdit m_editNormalStartParticipantId;
    CButton m_btnNormalStartIsVideoOff;
    CButton m_btnNormalStartIsAudioOff;
    CButton m_btnNormalStartIsDirectShareDesktop;
    CEdit m_editNormalJoinMeetingNumber;
    CEdit m_editNormalJoinVanityID;
    CEdit m_editNormalJoinUserName;
    CEdit m_editNormalJoinPsw;
    CEdit m_editNormalJoinParticipantId;
    CEdit m_editNormalJoinWebinarToken;
    CButton m_btnNormalJoinIsVideoOff;
    CButton m_btnNormalJoinIsAudioOff;
    CButton m_btnNormalJoinIsDirectShareDesktop;
    CButton m_btnAutoFullScreen;
    CButton m_btnAlwaysShowCtrlBar;
    CButton m_btnAlwaysJoinMeetingBeforeAdmin;
    CButton m_btnAutoJoinAudio;
    CButton m_btnParticipantsUnmute;
    CButton m_btnEchoCancellation;
    CButton m_btnHDVideo;
    CButton m_btnAutoTurnOffVideo;

    ISettingService* m_pSettingService;


};
