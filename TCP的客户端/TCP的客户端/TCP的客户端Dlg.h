
// TCP�Ŀͻ���Dlg.h : ͷ�ļ�
//

#pragma once


// CTCP�Ŀͻ���Dlg �Ի���
class CTCP�Ŀͻ���Dlg : public CDialogEx
{
// ����
public:
	CTCP�Ŀͻ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
};
