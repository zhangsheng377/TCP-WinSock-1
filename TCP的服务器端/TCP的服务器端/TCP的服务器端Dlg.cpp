
// TCP的服务器端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TCP的服务器端.h"
#include "TCP的服务器端Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCP的服务器端Dlg 对话框



CTCP的服务器端Dlg::CTCP的服务器端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCP的服务器端Dlg::IDD, pParent)
	, my_ServerIP(_T(""))
	, my_ServerPort(0)
	, my_ServerStatus(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCP的服务器端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, my_ServerIP);
	DDX_Text(pDX, IDC_EDIT2, my_ServerPort);
	DDX_Text(pDX, IDC_EDIT3, my_ServerStatus);
}

BEGIN_MESSAGE_MAP(CTCP的服务器端Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CTCP的服务器端Dlg::OnBnClickedSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, &CTCP的服务器端Dlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CTCP的服务器端Dlg 消息处理程序

BOOL CTCP的服务器端Dlg::OnInitDialog()
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

void CTCP的服务器端Dlg::OnPaint()
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
HCURSOR CTCP的服务器端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCP的服务器端Dlg::OnBnClickedSend()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (my_SockListen.Create(my_ServerPort, SOCK_STREAM, NULL))
	{
		GetDlgItem(IDC_SEND)->EnableWindow(false);
		GetDlgItem(IDC_STOP)->EnableWindow(true);
		my_SockListen.Bind(my_ServerPort, my_ServerIP);
		if (my_SockListen.Listen())
		{
			my_ServerStatus = "服务器处于监听状态!";
			UpdateData(false);
			my_SockListen.Accept(my_SockSend);					//处于等待连接状态,直到有连接进入才返回
			my_SockListen.Close();
			SetTimer(1, 2000, NULL);							//创建一个定时器用于发送消息
		}
		else
		{
			AfxMessageBox(L"Socket创建失败!");
		}
	}
}


void CTCP的服务器端Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	static int iIndex = 0;
	char szSend[20];
	sprintf_s(szSend, "%010d", iIndex++);
	int iSend = my_SockSend.Send(szSend, 10, 0);
	my_ServerStatus.Format(L"正在发送数据%010d", iIndex);
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


void CTCP的服务器端Dlg::OnBnClickedStop()
{
	// TODO:  在此添加控件通知处理程序代码
	KillTimer(1);
	my_SockSend.Close();
	my_ServerStatus = "服务器停止发送数据!";
	UpdateData(false);
	GetDlgItem(IDC_SEND)->EnableWindow(true);
	GetDlgItem(IDC_STOP)->EnableWindow(false);
}
