
// ZhumuSdkProgressDlg.h : ͷ�ļ�
//

#pragma once


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
    afx_msg LRESULT OnQuitProgress(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnCustomErrorMessage(WPARAM wParam, LPARAM lParam);

    
};
