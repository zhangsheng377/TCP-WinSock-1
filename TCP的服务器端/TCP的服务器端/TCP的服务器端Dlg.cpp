
// TCP�ķ�������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCP�ķ�������.h"
#include "TCP�ķ�������Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCP�ķ�������Dlg �Ի���



CTCP�ķ�������Dlg::CTCP�ķ�������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCP�ķ�������Dlg::IDD, pParent)
	, my_ServerIP(_T(""))
	, my_ServerPort(0)
	, my_ServerStatus(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCP�ķ�������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, my_ServerIP);
	DDX_Text(pDX, IDC_EDIT2, my_ServerPort);
	DDX_Text(pDX, IDC_EDIT3, my_ServerStatus);
}

BEGIN_MESSAGE_MAP(CTCP�ķ�������Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CTCP�ķ�������Dlg::OnBnClickedSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, &CTCP�ķ�������Dlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CTCP�ķ�������Dlg ��Ϣ�������

BOOL CTCP�ķ�������Dlg::OnInitDialog()
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

void CTCP�ķ�������Dlg::OnPaint()
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
HCURSOR CTCP�ķ�������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCP�ķ�������Dlg::OnBnClickedSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (my_SockListen.Create(my_ServerPort, SOCK_STREAM, NULL))
	{
		GetDlgItem(IDC_SEND)->EnableWindow(false);
		GetDlgItem(IDC_STOP)->EnableWindow(true);
		my_SockListen.Bind(my_ServerPort, my_ServerIP);
		if (my_SockListen.Listen())
		{
			my_ServerStatus = "���������ڼ���״̬!";
			UpdateData(false);
			my_SockListen.Accept(my_SockSend);					//���ڵȴ�����״̬,ֱ�������ӽ���ŷ���
			my_SockListen.Close();
			SetTimer(1, 2000, NULL);							//����һ����ʱ�����ڷ�����Ϣ
		}
		else
		{
			AfxMessageBox(L"Socket����ʧ��!");
		}
	}
}


void CTCP�ķ�������Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	static int iIndex = 0;
	char szSend[20];
	sprintf_s(szSend, "%010d", iIndex++);
	int iSend = my_SockSend.Send(szSend, 10, 0);
	my_ServerStatus.Format(L"���ڷ�������%010d", iIndex);
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


void CTCP�ķ�������Dlg::OnBnClickedStop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	my_SockSend.Close();
	my_ServerStatus = "������ֹͣ��������!";
	UpdateData(false);
	GetDlgItem(IDC_SEND)->EnableWindow(true);
	GetDlgItem(IDC_STOP)->EnableWindow(false);
}
