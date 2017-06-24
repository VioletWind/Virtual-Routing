
// VRv0.1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VRv0.1.h"
#include "VRv0.1Dlg.h"
#include "afxdialogex.h"
#include "socket.h"
#include "dv.h"
#include <iterator>
#include <fstream>
#include <sstream>
#define BUFFERSIZE 2048
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CVRv01Dlg 对话框



CVRv01Dlg::CVRv01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VRV01_DIALOG, pParent)
	, m_strMessage(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVRv01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LSENT, m_ctlSent);
	DDX_Control(pDX, IDC_LRECVD, m_ctlRecvd);
	DDX_Text(pDX, IDC_EMSG, m_strMessage);
	DDV_MaxChars(pDX, m_strMessage, 1024);
	DDX_Control(pDX, IDC_LDST, m_ctlDst);
	DDX_Control(pDX, IDC_LNEXT, m_ctlNext);
	DDX_Control(pDX, IDC_LDEB, m_ctlDeb);
	DDX_Control(pDX, IDC_LCOST, m_ctlCost);
	DDX_Control(pDX, IDC_ENABLE, m_ctlEnable);
}

BEGIN_MESSAGE_MAP(CVRv01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CVRv01Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BSEND, &CVRv01Dlg::OnBnClickedBsend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ENABLE, &CVRv01Dlg::OnBnClickedEnable)
	ON_BN_CLICKED(IDC_BINIT, &CVRv01Dlg::OnBnClickedBinit)
END_MESSAGE_MAP()


// CVRv01Dlg 消息处理程序

BOOL CVRv01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	init = enable = false;
	GetDlgItem(IDC_BINIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_ENABLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BSEND)->EnableWindow(FALSE);
	/*m_strMessage = "";
	host = Host("Host0", 4, 0, "127.0.0.1", 65530);
	fd = socketBind(host.Port);
	CostMatrix = {
		{0, DV_MAX, 1, 3, 1},
		{DV_MAX, 0, DV_MAX, 1, 4},
		{1, DV_MAX, 0, 1, DV_MAX},
		{3, 1, 1, 0, DV_MAX},
		{1, 4, DV_MAX, DV_MAX, 0}
	};
	for (int i = 0; i < 5; ++i) {
		IPPortToHost["127.0.0.1+6553" + to_string(i)] = "Host" + to_string(i);
		HostToIPPort["Host" + to_string(i)] = "127.0.0.1+6553" + to_string(i);
		NumToHost[i] = ("Host" + to_string(i));
		int rNum = 0;
		for (auto it : CostMatrix[i]) {
		if (it != DV_MAX) rNum++;
		}
		vHost["Host" + to_string(i)] = Host("Host" + to_string(i), rNum, i, "127.0.0.1", 65530 + i);
	}
	dvInit(CostMatrix, NumToHost, RouterTable, host);
	dvInit(CostMatrix, NumToHost, AdjTable, host);
	CListBox *pRList = &(m_ctlDst);
	CListBox *pNList = &(m_ctlNext);
	CListBox *pCList = &(m_ctlCost);
	for (auto it = RouterTable.begin(); it != RouterTable.end(); ++it) {
		pRList->AddString(it->second.dst.c_str());
		pNList->AddString(it->second.hop.c_str());
		pCList->AddString(to_string(it->second.cost).c_str());
	}
	CWinThread* mThread = AfxBeginThread(MainThreadFun, this);
	CWinThread* rThread = AfxBeginThread(RecvThreadFun, this);*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVRv01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVRv01Dlg::OnPaint()
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
HCURSOR CVRv01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVRv01Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}
UINT CVRv01Dlg::MainThreadFun(LPVOID pParam) {
	CVRv01Dlg * pDlg = (CVRv01Dlg*)pParam;
	//初始化
	//定时发送更新
	pDlg->SetTimer(1, 30000, NULL);
	for (auto it = pDlg->AdjTable.begin(); it != pDlg->AdjTable.end(); ++it) {
		if (it->first != pDlg->host.name)
			pDlg->SetTimer(pDlg->vHost.find((it->second).dst)->second.index + 1024, 60000, NULL);
	}
	return 0;
}


UINT CVRv01Dlg::RecvThreadFun(LPVOID pParam) {
	CVRv01Dlg * pDlg = (CVRv01Dlg*)pParam;
	//找出来源路由
	string  content, fromIP;
	int fromPort;
	for (;;) {
		fromPort = socketReceive(pDlg->fd, content, fromIP);
		if (fromPort == -1) {
			int err = WSAGetLastError();
			pDlg->MessageBox((to_string(err) + "Recv").c_str());
		}
		else {
			string srcHost = (pDlg->IPPortToHost).find(fromIP + "+" + to_string(fromPort))->second;
			Host srcRouter = pDlg->vHost.find(srcHost)->second;
			vector<string> v;
			SplitString(content, v, "\n");
			if (v.empty() || ((v[0] != "Message") && (v[0] != "Router"))) {
				pDlg->MessageBox(("Unrecognizable: " + content).c_str());
			}
			else if (v[0] == "Message") {
				if (v[2] == pDlg->host.name) {
					//发送给自己
					pDlg->m_ctlRecvd.AddString((v[1] + ": " + v[3]).c_str());
					pDlg->m_ctlDeb.AddString(("Received message from " + v[1]).c_str());
				}
				else {
					//转发
					string forwardHost = pDlg->RouterTable.find(v[2])->second.hop;
					string forwardIP = (pDlg->HostToIPPort.find(forwardHost))->second;
					vector<string> to;
					SplitString(forwardIP, to, "+");
					pDlg->m_ctlDeb.AddString(("Forwarding message to " + forwardHost).c_str());
					socketSend(pDlg->fd, stoi(to[1]), to[0], content);
					//pDlg->MessageBox((to[0] + "\n" + to[1] + "\n" + content).c_str());
				}
			}
			else if (v[0] == "Router") {
				//重设定时器
				//pDlg->MessageBox(content.c_str());
				pDlg->KillTimer(srcRouter.index + 1024);
				//pDlg->MessageBox("kill");
				pDlg->SetTimer(srcRouter.index + 1024, 60000, NULL);
				//转换字符串为路由表并更新
				map<string, struct RouterTab> srcTab;
				dvReceive(content, srcTab, srcRouter);
				pDlg->m_ctlDeb.AddString(("Received routertable from " + srcHost).c_str());
				pDlg->m_ctlDeb.AddString("Updating routertable...");
				//lock
				WaitForSingleObject(pDlg->hMutex, INFINITE);
				dvUpdate(srcRouter, srcTab, pDlg->AdjTable, pDlg->RouterTable, pDlg->host);
				//unlock
				ReleaseMutex(pDlg->hMutex);
				//同步列表
				CListBox *pRList = &(pDlg->m_ctlDst);
				CListBox *pNList = &(pDlg->m_ctlNext);
				CListBox *pCList = &(pDlg->m_ctlCost);
				pRList->ResetContent();
				pNList->ResetContent();
				pCList->ResetContent();
				for (auto it = pDlg->RouterTable.begin(); it != pDlg->RouterTable.end(); ++it) {
					pRList->AddString(it->second.dst.c_str());
					pNList->AddString(it->second.hop.c_str());
					pCList->AddString(to_string(it->second.cost).c_str());
				}
			}
			else {
				pDlg->MessageBox(("Unrecognizable: " + content).c_str());
			}
		}
	}
	return 0;
}

UINT CVRv01Dlg::SendThreadFun(LPVOID pParam) {
	CVRv01Dlg * pDlg = (CVRv01Dlg*)pParam;
	CString sMessage, sHostname;
	CListBox* pRT = &(pDlg->m_ctlDst);
	int CurSel = pRT->GetCurSel();
	if (CurSel == CB_ERR) pDlg->MessageBox("Please select a host!");
	else {
		pRT->GetText(CurSel, sHostname);
		pDlg->GetDlgItemText(IDC_EMSG, sMessage);
		//pDlg->UpdateData(TRUE);
		//使用GetDlgItemText()而非UpdateData()， 可改进
		if (sMessage == "") {
			pDlg->MessageBox("Please type your message");
		}
		else {
			//搜索路由表
			//::MessageBox(NULL, sHostname, sMessage, MB_OK);
			//找到对应的IP和端口，打包好信息，调用SocketSend()发送
			auto it = pDlg->RouterTable.find(LPCSTR(sHostname));
			if (it == pDlg->RouterTable.end()) {
				pDlg->MessageBox("Not in RouterTable");
			}
			else {
				//查找下一跳
				auto itt = pDlg->HostToIPPort.find(it->second.hop);
				if (itt == pDlg->HostToIPPort.end()) {
					pDlg->MessageBox("Not in HostTable!");
				}
				else {
					//打包要发送的信息并发送
					vector<string> v;
					SplitString(itt->second, v, "+");//也可以用AfxExtractSubString 
					//pDlg->MessageBox((v[0] + " IP " + v[1] + " Port").c_str());
					string content = "Message\n";
					content += pDlg->host.name;
					content += "\n";
					content += sHostname;
					content += "\n";
					content += sMessage;
					pDlg->m_ctlDeb.AddString(("Sending message to " + sHostname));
					pDlg->m_ctlSent.AddString("To " + sHostname + ": " + sMessage);
					//pDlg->MessageBox((v[0] + "\n" + v[1] + "\n" + content).c_str());
					int result = socketSend(pDlg->fd, stoi(v[1]), v[0], content);
					if (result == -1) {
						int err = WSAGetLastError();
						pDlg->MessageBox((to_string(err) + "Send").c_str());
					}
				}
			}
		}
	}
	return 0;
}



void CVRv01Dlg::OnBnClickedBsend()
{
	// TODO: 在此添加控件通知处理程序代码
	CWinThread* sThread = AfxBeginThread(SendThreadFun, this);
}


void CVRv01Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (enable) {
		switch (nIDEvent) {
		case 1://定时发送更新
		{
			string contentToSend;
			dvSend(contentToSend, RouterTable, host);
			//MessageBox(contentToSend.c_str());
			for (auto it = AdjTable.begin(); it != AdjTable.end(); ++it) {
				if (it->first != host.name && it->second.cost < DV_MAX) {
					string toHostname = it->first;
					string toIPPort = HostToIPPort[toHostname];
					vector<string> v;
					SplitString(toIPPort, v, "+");
					m_ctlDeb.AddString(("Sending RouterTable to: " + toHostname).c_str());
					int result = socketSend(fd, stoi(v[1]), v[0], contentToSend);
					if (result == -1) {
						int err = WSAGetLastError();
						MessageBox((to_string(err) + "Send").c_str());
					}
				}
			}
			break;
		}
		case 2:
			KillTimer(2);
			dvDelete(RouterTable, AdjTable, host);
			break;
		default:
			KillTimer(nIDEvent);
			//某个节点失效
			int vnum = nIDEvent - 1024;	
			string hostname = NumToHost.find(vnum)->second;
			//lock
			WaitForSingleObject(hMutex, INFINITE);
			dvDisable(RouterTable, AdjTable, hostname);
			//unlock
			ReleaseMutex(hMutex);
			m_ctlDeb.AddString((hostname + "Down").c_str());
			string contentToSend;
			dvSend(contentToSend, RouterTable, host);
			//MessageBox(content.c_str());
			//lock
			WaitForSingleObject(hMutex, INFINITE);
			SetTimer(2, 35000, NULL);
			//dvDelete(RouterTable, AdjTable, hostname, host);
			//MessageBox(content.c_str());
			//unlock
			ReleaseMutex(hMutex);
			CListBox *pRList = &(m_ctlDst);
			CListBox *pNList = &(m_ctlNext);
			CListBox *pCList = &(m_ctlCost);
			pRList->ResetContent();
			pNList->ResetContent();
			pCList->ResetContent();
			for (auto it = RouterTable.begin(); it != RouterTable.end(); ++it) {
				pRList->AddString(it->second.dst.c_str());
				pNList->AddString(it->second.hop.c_str());
				pCList->AddString(to_string(it->second.cost).c_str());
			}
			//dvSend(content, RouterTable, host);
			for (auto it = AdjTable.begin(); it != AdjTable.end(); ++it) {
				if ((it->first) != host.name && it->second.cost < DV_MAX) {
					string toHostname = it->first;
					string toIPPort = HostToIPPort[toHostname];
					vector<string> v;
					SplitString(toIPPort, v, "+");
					m_ctlDeb.AddString(("Sending poisoned routertable to:" + toHostname).c_str());
					int result = socketSend(fd, stoi(v[1]), v[0], contentToSend);
					if (result == -1) {
						int err = WSAGetLastError();
						MessageBox((to_string(err) + "Send").c_str());
					}
				}
			}
			//}
			break;
		}
	}	
	CDialogEx::OnTimer(nIDEvent);
}


void CVRv01Dlg::OnBnClickedEnable()
{
	enable = !enable;
	if (enable) {
		GetDlgItem(IDC_BSEND)->EnableWindow(TRUE);
		m_ctlEnable.SetWindowTextA("关闭");
		SetTimer(1, 30000, NULL);
		for (auto it = AdjTable.begin(); it != AdjTable.end(); ++it) {
			SetTimer(vHost.find((it->second).dst)->second.index + 1024, 60000, NULL);
		}
	}
	else {
		KillTimer(1);
		for (auto it = AdjTable.begin(); it != AdjTable.end(); ++it) {
			KillTimer(vHost.find((it->second).dst)->second.index + 1024);
		}
		GetDlgItem(IDC_BSEND)->EnableWindow(FALSE);
		m_ctlEnable.SetWindowTextA("开启");
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CVRv01Dlg::OnBnClickedBinit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (init) {
		MessageBox("Initialized!");
		return;
	}
	char *filters = "配置文件(*.dat)|*.dat|";
	string sPath;
	CFileDialog fileDlg(TRUE, "dat", "*.dat",
		OFN_HIDEREADONLY, filters);
	if (fileDlg.DoModal() == IDOK) {
		sPath = fileDlg.GetPathName();		
	}if (sPath == "") return;
	ifstream ifs(sPath, ios::in);
	if (ifs.good()) {
		int tSize, tIndex;
		ifs >> tSize >> tIndex;
		vector<vector<int> >tm;
		map<string, string> tIPPortToHost, tHostToIPPort;
		map<int, string> tNumToHost;
		map<string, struct Host> tvHost;
		for (int i = 0; i < tSize; ++i) {
			vector<int> tv;
			int ti;
			for (int j = 0; j < tSize; ++j) {
				ifs >> ti;
				tv.push_back(ti);
			}tm.push_back(tv);
		}for (int i = 0; i < tSize; ++i) {
			int ti, tport;
			string tname, tIP;
			ifs >> ti >> tname >> tIP >> tport;
			tIPPortToHost[tIP + "+" + to_string(tport)] = tname;
			tHostToIPPort[tname] = tIP + "+" + to_string(tport);
			tNumToHost[ti] = tname;
			int tr = 0;
			for (auto it : tm[ti]) {
				if (it != DV_MAX) tr++;
			}
			tvHost[tname] = Host(tname, tr, ti, tIP, tport);
		}
		//lock
		WaitForSingleObject(hMutex, INFINITE); CostMatrix = tm;
		IPPortToHost = tIPPortToHost;
		HostToIPPort = tHostToIPPort;
		NumToHost = tNumToHost;
		vHost = tvHost;
		host = vHost[NumToHost[tIndex]];
		fd = socketBind(host.Port);
		dvInit(CostMatrix, NumToHost, RouterTable, host);
		dvInit(CostMatrix, NumToHost, AdjTable, host);
		//unlock;
		ReleaseMutex(hMutex);
		CListBox *pRList = &(m_ctlDst);
		CListBox *pNList = &(m_ctlNext);
		CListBox *pCList = &(m_ctlCost);
		for (auto it = RouterTable.begin(); it != RouterTable.end(); ++it) {
			pRList->AddString(it->second.dst.c_str());
			pNList->AddString(it->second.hop.c_str());
			pCList->AddString(to_string(it->second.cost).c_str());
		}init = enable = true;
		GetDlgItem(IDC_BINIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ENABLE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BSEND)->EnableWindow(TRUE);
		m_ctlEnable.SetWindowTextA("关闭");
		CWinThread* mThread = AfxBeginThread(MainThreadFun, this);
		CWinThread* rThread = AfxBeginThread(RecvThreadFun, this);
	}
	else {
		ifs.close();
		MessageBox(("Failed to open " + sPath).c_str());
		return;
	}ifs.close();
}
