
// VRv0.1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "dv.h"

// CVRv01Dlg 对话框
class CVRv01Dlg : public CDialogEx
{
// 构造
public:
	CVRv01Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VRV01_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListBox m_ctlSent;//已发
	CListBox m_ctlRecvd;//已收
	CString m_strMessage;//要发送的信息
	CListBox m_ctlDst;//目标主机
	CListBox m_ctlNext;//下一跳
	CListBox m_ctlDeb;//状态信息
	afx_msg void OnBnClickedBsend();
	static UINT MainThreadFun(LPVOID pParam);
	static UINT RecvThreadFun(LPVOID pParam);
	static UINT SendThreadFun(LPVOID pParam);
	vector<vector<int> > CostMatrix;//费用矩阵
	map<int, string> NumToHost;//下标到主机名的映射
	map<string, Host> vHost;
	map<string, RouterTab> RouterTable;
	map<string, RouterTab> AdjTable;
	map<string, string> IPPortToHost;
	map<string, string> HostToIPPort;
	int fd;
	struct Host host;
	HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

