
// HackxDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "tchart1.h"


// CHackxDlg �Ի���
class CHackxDlg : public CDialogEx
{
// ����
public:
	CHackxDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HACKX_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	CButton btn_1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CTchart1 m_chart;
	CTchart1 h_chart;
};
