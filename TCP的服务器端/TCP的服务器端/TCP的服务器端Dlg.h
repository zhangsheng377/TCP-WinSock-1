
// TCP�ķ�������Dlg.h : ͷ�ļ�
//

#pragma once


// CTCP�ķ�������Dlg �Ի���
class CTCP�ķ�������Dlg : public CDialogEx
{
// ����
public:
	CTCP�ķ�������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString my_ServerIP;
	int my_ServerPort;
	CString my_ServerStatus;

	CSocket my_SockListen;
	CAsyncSocket my_SockSend;
	afx_msg void OnBnClickedSend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStop();
};
