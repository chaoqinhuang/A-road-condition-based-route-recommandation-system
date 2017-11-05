
// HackxDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CHackxDlg �Ի���



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


// CHackxDlg ��Ϣ�������

BOOL CHackxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHackxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHackxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHackxDlg::OnBnClickedButton1()
{
	CString strText;
	MSG msg;
	int rank;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (sys_sta==0) {
		if (HC_Init()) {
			AfxMessageBox(L"��������ʧ��"); return;
		}
		sys_sta = 1;
		SetTimer(0, 100, NULL);
		btn_1.SetWindowTextW(L"����");
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
