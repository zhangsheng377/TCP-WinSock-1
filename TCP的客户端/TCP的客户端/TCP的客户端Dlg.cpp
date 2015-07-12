
// TCP的客户端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TCP的客户端.h"
#include "TCP的客户端Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCP的客户端Dlg 对话框



CTCP的客户端Dlg::CTCP的客户端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCP的客户端Dlg::IDD, pParent)
	, my_ServerIP(_T(""))
	, my_ServerPort(0)
	, my_ReceiveData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCP的客户端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, my_ServerIP);
	DDX_Text(pDX, IDC_EDIT2, my_ServerPort);
	DDX_Text(pDX, IDC_EDIT3, my_ReceiveData);
}

BEGIN_MESSAGE_MAP(CTCP的客户端Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RECEIVE, &CTCP的客户端Dlg::OnBnClickedReceive)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, &CTCP的客户端Dlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CTCP的客户端Dlg 消息处理程序

BOOL CTCP的客户端Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTCP的客户端Dlg::OnPaint()
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
HCURSOR CTCP的客户端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCP的客户端Dlg::OnBnClickedReceive()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_SockReceive.Create())
	{
		m_SockReceive.Connect(my_ServerIP, my_ServerPort);
		SetTimer(1, 2000, NULL);
		my_ReceiveData = "成功连接服务器!";
		UpdateData(false);
		GetDlgItem(IDC_RECEIVE)->EnableWindow(false);
		GetDlgItem(IDC_STOP)->EnableWindow(true);
	}
	else
	{
		AfxMessageBox(L"Socket创建失败!");
	}
}


void CTCP的客户端Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	char szRecv[20];
	int iRecv = m_SockReceive.Receive(szRecv, 10, 0);
	if (iRecv >= 0)
	{
		szRecv[iRecv] = NULL;
		my_ReceiveData = szRecv;
		my_ReceiveData = L"接收数据为:" + my_ReceiveData;
	}
	else
	{
		my_ReceiveData = "没有收到数据!";
	}
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


void CTCP的客户端Dlg::OnBnClickedStop()
{
	// TODO:  在此添加控件通知处理程序代码
	KillTimer(1);
	m_SockReceive.Close();
	my_ReceiveData = "停止接收数据!";
	UpdateData(false);
	GetDlgItem(IDC_RECEIVE)->EnableWindow(true);
	GetDlgItem(IDC_STOP)->EnableWindow(false);
}
