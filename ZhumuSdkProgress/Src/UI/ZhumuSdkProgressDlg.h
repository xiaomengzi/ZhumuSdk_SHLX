
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

    
public:
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
};
