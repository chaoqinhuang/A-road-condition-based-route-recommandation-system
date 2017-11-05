
// HackxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Hackx.h"
#include "HackxDlg.h"
#include "afxdialogex.h"
#include "hccom.h"
#include "CSeries.h"
#include "tchart1.h"
#include "CAxes.h"
#include "CAxis.h"
#include "CScroll.h"
#include <stdlib.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


bool sys_sta = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CHackxDlg 对话框



CHackxDlg::CHackxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HACKX_DIALOG, pParent)
	

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHackxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, btn_1);
	DDX_Control(pDX, IDC_TCHART1, m_chart);
	DDX_Control(pDX, IDC_TCHART2, h_chart);
}

BEGIN_MESSAGE_MAP(CHackxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHackxDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CHackxDlg 消息处理程序

BOOL CHackxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	/*CProgressCtrl *pProg = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	pProg->SetRange(0, 9);
	pProg->SetPos(0);*/

	CSeries data1 = (CSeries)m_chart.Series(0);
	CSeries data2 = (CSeries)h_chart.Series(0);
	for (int i = 0; i < 20; i++)
	{
		data1.AddXY(i, 0, NULL, NULL);
	}
	for (int i = 0; i < 20; i++)
	{
		data2.AddXY(i, 0, NULL, NULL);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHackxDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHackxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHackxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHackxDlg::OnBnClickedButton1()
{
	CString strText;
	MSG msg;
	int rank;
	// TODO: 在此添加控件通知处理程序代码
	if (sys_sta==0) {
		if (HC_Init()) {
			AfxMessageBox(L"蓝牙连接失败"); return;
		}
		sys_sta = 1;
		SetTimer(0, 100, NULL);
		btn_1.SetWindowTextW(L"结束");
	}
	else {
		sys_sta = 0;
		KillTimer(0);
	}
	/*strText.Format(L"%d", Read_Data[0]);
	SetDlgItemText(RANK_STATIC, strText);
	rank = Read_Data[0];
	CProgressCtrl *pProg = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	pProg->SetPos(rank);
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	while (1)
	{
		if (HC_Read()) {
			CProgressCtrl *pProg = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
			pProg->SetPos(Read_Data[0]);
			strText.Format(L"%d", Read_Data[0]);
			SetDlgItemText(RANK_STATIC, strText);
		}
	}*/
}


void CHackxDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strText;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 0) {
		if (HC_Read())
		{

			CSeries chart_T = (CSeries)m_chart.Series(0);
			CSeries chart_H = (CSeries)h_chart.Series(0);
			
			//chart_T.Clear();

			chart_T.Add(Read_Data[0], L"label1", 1);
			chart_H.Add(Read_Data[1], L"label2", 1);
			
			strText.Format(L"%d", Read_Data[0]);
			SetDlgItemText(RANK_STATIC, strText);
			strText.Format(L"%d", Read_Data[1]);
			SetDlgItemText(H_STATIC, strText);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
