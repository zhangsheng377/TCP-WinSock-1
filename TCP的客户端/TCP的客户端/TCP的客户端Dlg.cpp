
// TCP�Ŀͻ���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCP�Ŀͻ���.h"
#include "TCP�Ŀͻ���Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCP�Ŀͻ���Dlg �Ի���



CTCP�Ŀͻ���Dlg::CTCP�Ŀͻ���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCP�Ŀͻ���Dlg::IDD, pParent)
	, my_ServerIP(_T(""))
	, my_ServerPort(0)
	, my_ReceiveData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCP�Ŀͻ���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, my_ServerIP);
	DDX_Text(pDX, IDC_EDIT2, my_ServerPort);
	DDX_Text(pDX, IDC_EDIT3, my_ReceiveData);
}

BEGIN_MESSAGE_MAP(CTCP�Ŀͻ���Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RECEIVE, &CTCP�Ŀͻ���Dlg::OnBnClickedReceive)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, &CTCP�Ŀͻ���Dlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CTCP�Ŀͻ���Dlg ��Ϣ�������

BOOL CTCP�Ŀͻ���Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTCP�Ŀͻ���Dlg::OnPaint()
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
HCURSOR CTCP�Ŀͻ���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCP�Ŀͻ���Dlg::OnBnClickedReceive()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_SockReceive.Create())
	{
		m_SockReceive.Connect(my_ServerIP, my_ServerPort);
		SetTimer(1, 2000, NULL);
		my_ReceiveData = "�ɹ����ӷ�����!";
		UpdateData(false);
		GetDlgItem(IDC_RECEIVE)->EnableWindow(false);
		GetDlgItem(IDC_STOP)->EnableWindow(true);
	}
	else
	{
		AfxMessageBox(L"Socket����ʧ��!");
	}
}


void CTCP�Ŀͻ���Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	char szRecv[20];
	int iRecv = m_SockReceive.Receive(szRecv, 10, 0);
	if (iRecv >= 0)
	{
		szRecv[iRecv] = NULL;
		my_ReceiveData = szRecv;
		my_ReceiveData = L"��������Ϊ:" + my_ReceiveData;
	}
	else
	{
		my_ReceiveData = "û���յ�����!";
	}
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


void CTCP�Ŀͻ���Dlg::OnBnClickedStop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	m_SockReceive.Close();
	my_ReceiveData = "ֹͣ��������!";
	UpdateData(false);
	GetDlgItem(IDC_RECEIVE)->EnableWindow(true);
	GetDlgItem(IDC_STOP)->EnableWindow(false);
}
