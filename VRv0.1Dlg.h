
// VRv0.1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CVRv01Dlg �Ի���
class CVRv01Dlg : public CDialogEx
{
// ����
public:
	CVRv01Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VRV01_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListBox m_ctlSent;//�ѷ�
	CListBox m_ctlRecvd;//����
	CString m_strMessage;//Ҫ���͵���Ϣ
	CListBox m_ctlDst;//Ŀ������
	CListBox m_ctlNext;//��һ��
	CListBox m_ctlDeb;//״̬��Ϣ
	afx_msg void OnBnClickedBsend();
	static UINT ThreadFun(LPVOID pParam);
};

