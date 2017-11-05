
// HackxDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "tchart1.h"


// CHackxDlg 对话框
class CHackxDlg : public CDialogEx
{
// 构造
public:
	CHackxDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HACKX_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	CButton btn_1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CTchart1 m_chart;
	CTchart1 h_chart;
};
