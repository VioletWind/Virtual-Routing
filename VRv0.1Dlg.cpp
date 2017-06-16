
// VRv0.1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VRv0.1.h"
#include "VRv0.1Dlg.h"
#include "afxdialogex.h"
#include "socket.h"
#include "dv.h"
#include <iterator>
#define BUFFERSIZE 2048
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CVRv01Dlg �Ի���



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
}

BEGIN_MESSAGE_MAP(CVRv01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CVRv01Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BSEND, &CVRv01Dlg::OnBnClickedBsend)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CVRv01Dlg ��Ϣ�������

BOOL CVRv01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CListBox* pRT = (CListBox*)GetDlgItem(IDC_LDST);
	m_strMessage = "";
	host = Host("Host0", 3, 0, "127.0.0.1", 65530);
	fd = socketBind(host.Port);
	CostMatrix = {
		{0,1,3,7},
		{1,0,1,DV_MAX},
		{3,1,0,2},
		{7,DV_MAX,2,0}
	};
	NumToHost[0] = "Host0";
	NumToHost[1] = "Host1";
	NumToHost[2] = "Host2";
	NumToHost[3] = "Host3";
	vHost["Host0"] = Host("Host0", 3, 0, "127.0.0.1", 65530);
	vHost["Host1"] = Host("Host1", 2, 1, "127.0.0.1", 65531);
	vHost["Host2"] = Host("Host2", 3, 2, "127.0.0.1", 65532);
	vHost["Host3"] = Host("Host3", 2, 3, "127.0.0.1", 65533);
	/*RouterTable["Host0"] = RouterTab("Host0", "Host0", 0);
	RouterTable["Host1"] = RouterTab("Host1", "Host1", 1);
	RouterTable["Host2"] = RouterTab("Host2", "Host2", 3);
	RouterTable["Host3"] = RouterTab("Host3", "Host3", 7);*/
	/*AdjTable["Host0"] = RouterTab("Host0", "Host0", 0);
	AdjTable["Host1"] = RouterTab("Host1", "Host1", 1);
	AdjTable["Host2"] = RouterTab("Host2", "Host2", 3);
	AdjTable["Host3"] = RouterTab("Host3", "Host3", 7);*/
	dvInit(CostMatrix, NumToHost, RouterTable, host);
	/*IPPortToHost["127.0.0.1+65530"] = "Host0";
	IPPortToHost["127.0.0.1+65531"] = "Host1";
	IPPortToHost["127.0.0.1+65532"] = "Host2";
	IPPortToHost["127.0.0.1+65533"] = "Host3";
	HostToIPPort["Host0"] = "127.0.0.1+65530";
	HostToIPPort["Host1"] = "127.0.0.1+65531";
	HostToIPPort["Host2"] = "127.0.0.1+65532";
	HostToIPPort["Host3"] = "127.0.0.1+65533";*/
	for (int i = 0; i < 4; ++i) {
		IPPortToHost["127.0.0.1+6553" + to_string(i)] = "Host" + to_string(i);
		HostToIPPort["Host" + to_string(i)] = "127.0.0.1+6553" + to_string(i);
	}
	/*for (auto it = IPPortToHost.begin(); it != IPPortToHost.end(); ++it) {
		MessageBox((it->first + it->second).c_str());
		Sleep(2000);
	}*/
	CListBox *pRList = &(m_ctlDst);
	CListBox *pNList = &(m_ctlNext);
	CListBox *pCList = &(m_ctlCost);
	for (auto it = RouterTable.begin(); it != RouterTable.end(); ++it) {
		pRList->AddString(it->second.dst.c_str());
		pNList->AddString(it->second.hop.c_str());
		pCList->AddString(to_string(it->second.cost).c_str());
	}
	CWinThread* mThread = AfxBeginThread(MainThreadFun, this);
	CWinThread* rThread = AfxBeginThread(RecvThreadFun, this);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVRv01Dlg::OnPaint()
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
HCURSOR CVRv01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVRv01Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//��ʼ��
	//��ʱ���͸���
	pDlg->SetTimer(1, 30000, NULL);
	for (auto it = pDlg->AdjTable.begin(); it != pDlg->AdjTable.end(); ++it) {
		pDlg->SetTimer(pDlg->vHost.find((it->second).dst)->second.index + 1024, 180000, NULL);
	}
	return 0;
}

UINT CVRv01Dlg::RecvThreadFun(LPVOID pParam) {
	CVRv01Dlg * pDlg = (CVRv01Dlg*)pParam;
	//�ҳ���Դ·��
	string  content, fromIP;
	int fromPort;
	content = "Router\n4\n1\n127.0.0.1\n65531\nHost0 Host0 1\nHost1 Host1 0\nHost2 Host2 1\nHost3 Host3 5\n";
	fromPort = 65531;
	fromIP = "127.0.0.1";
	//for (;;) {
		//fromPort = socketReceive(pDlg->fd, content, fromIP);
	if (fromPort == -1) {
		int err = WSAGetLastError();
		pDlg->MessageBox((to_string(err) + "Recv").c_str());
	}
	else {
		string srcHost = (pDlg->IPPortToHost).find(fromIP + "+" + to_string(fromPort))->second;
		Host srcRouter = pDlg->vHost.find(srcHost)->second;
		vector<string> v;
		SplitString(content, v, "\n");
		if (v[0] == "Message") {
			if (v[2] == pDlg->host.name) {
				//���͸��Լ�
				pDlg->m_ctlRecvd.AddString((v[1] + ": " + v[3]).c_str());
				pDlg->m_ctlDeb.AddString(("Received message from " + v[1]).c_str());
			}
			else {
				//ת��
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
			//���趨ʱ��
			Sleep(5000);
			pDlg->KillTimer(srcRouter.index + 1024);
			//pDlg->MessageBox("kill");
			pDlg->SetTimer(srcRouter.index + 1024, 180000, NULL);
			//ת���ַ���Ϊ·�ɱ�����
			map<string, struct RouterTab> srcTab;
			dvReceive(content, srcTab, srcRouter);
			pDlg->m_ctlDeb.AddString(("Received routertable from " + srcHost).c_str());
			pDlg->m_ctlDeb.AddString("Updating routertable...");
			//lock
			WaitForSingleObject(pDlg->hMutex, INFINITE);
			dvUpdate(srcRouter, srcTab, pDlg->AdjTable, pDlg->RouterTable, pDlg->host);
			//unlock
			ReleaseMutex(pDlg->hMutex);
			//ͬ���б�
			CListBox *pRList = &(pDlg->m_ctlDst);
			CListBox *pNList = &(pDlg->m_ctlNext);
			CListBox *pCList = &(pDlg->m_ctlCost);
			pRList->ResetContent();
			pNList->ResetContent();
			pCList->ResetContent();
			for (auto it = pDlg->RouterTable.begin(); it != pDlg->RouterTable.end(); ++it){
				pRList->AddString(it->second.dst.c_str());
				pNList->AddString(it->second.hop.c_str());
				pCList->AddString(to_string(it->second.cost).c_str());
			}
		}
		else {
			pDlg->MessageBox(("Unrecognizable: " + content).c_str());
		}
		}
	//}	
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
		//ʹ��GetDlgItemText()����UpdateData()�� �ɸĽ�
		if (sMessage == "") {
			pDlg->MessageBox("Please type your message");
		}
		else {
			//����·�ɱ�
			//::MessageBox(NULL, sHostname, sMessage, MB_OK);
			//�ҵ���Ӧ��IP�Ͷ˿ڣ��������Ϣ������SocketSend()����
			auto it = pDlg->RouterTable.find(LPCSTR(sHostname));
			if (it == pDlg->RouterTable.end()) {
				pDlg->MessageBox("Not in RouterTable");
			}
			else {
				//������һ��
				auto itt = pDlg->HostToIPPort.find(it->second.hop);
				if (itt == pDlg->HostToIPPort.end()) {
					pDlg->MessageBox("Not in HostTable!");
				}
				else {
					//���Ҫ���͵���Ϣ������
					vector<string> v;
					SplitString(itt->second, v, "+");//Ҳ������AfxExtractSubString 
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWinThread* sThread = AfxBeginThread(SendThreadFun, this);
}


void CVRv01Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent) {
	case 1://��ʱ���͸���
	{
		string contentToSend;
		dvSend(contentToSend, RouterTable, host);
		//MessageBox(contentToSend.c_str());
		for (auto it = AdjTable.begin(); it != AdjTable.end(); ++it) {
			if (it->first != host.name) {
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
	default:
		//ĳ���ڵ�ʧЧ
		string content;
		int vnum = nIDEvent - 1024;
		string hostname = NumToHost.find(vnum)->second;
		//lock
		WaitForSingleObject(hMutex, INFINITE);
		dvDisable(RouterTable, AdjTable, hostname);
		//unlock
		ReleaseMutex(hMutex);
		string contentToSend;
		dvSend(content, RouterTable, host);
		MessageBox(content.c_str());
		//lock
		WaitForSingleObject(hMutex, INFINITE);
		dvDelete(RouterTable, AdjTable, hostname, host);
		dvSend(content, RouterTable, host);
		//MessageBox(content.c_str());
		//unlock
		ReleaseMutex(hMutex);
		for (auto it = AdjTable.begin(); it != AdjTable.end(); ++it) {
			if ((it->first) != host.name) {
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
		break;
	}	
	CDialogEx::OnTimer(nIDEvent);
}
