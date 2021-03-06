
// TCP的客户端Dlg.h : 头文件
//

#pragma once


// CTCP的客户端Dlg 对话框
class CTCP的客户端Dlg : public CDialogEx
{
// 构造
public:
	CTCP的客户端Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TCP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString my_ServerIP;
	int my_ServerPort;
	CString my_ReceiveData;

	CSocket m_SockReceive;
	afx_msg void OnBnClickedReceive();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStop();
};
