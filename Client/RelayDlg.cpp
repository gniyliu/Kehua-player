// RelayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyTest.h"
#include "RelayDlg.h"

#include <iostream>
using namespace std;

#include"tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRelayDlg dialog


CRelayDlg::CRelayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRelayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRelayDlg)
	m_strReceived = _T("");
	//}}AFX_DATA_INIT
}


void CRelayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRelayDlg)
	DDX_Control(pDX, IDC_RELAY_SEL, m_ctrlRelaySel);
	DDX_Control(pDX, IDC_EDIT1, m_nReceived);
	DDX_Text(pDX, IDC_EDIT1, m_strReceived);
	DDV_MaxChars(pDX, m_strReceived, 5000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRelayDlg, CDialog)
	//{{AFX_MSG_MAP(CRelayDlg)
	ON_BN_CLICKED(IDC_CLEAR_RECEIVED, OnClearReceived)
	ON_BN_CLICKED(IDC_CLEAR_SEND, OnClearSend)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_BUTTON_READ_AD, OnButtonReadAd)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnKey_1)
	ON_BN_CLICKED(IDC_BUTTON2, OnKey_1_Open)
	ON_BN_CLICKED(IDC_BUTTON4, OnKey_2_Open)
	ON_BN_CLICKED(IDC_BUTTON6, OnKey_3_Open)
	ON_BN_CLICKED(IDC_BUTTON8, OnKey_4_Open)
	ON_BN_CLICKED(IDC_BUTTON10, OnKey_5_Open)
	ON_BN_CLICKED(IDC_BUTTON12, OnKey_6_Open)
	ON_BN_CLICKED(IDC_BUTTON14, OnKey_7_Open)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CRelayDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CRelayDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CRelayDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CRelayDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON11, &CRelayDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON13, &CRelayDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON15, &CRelayDlg::OnBnClickedButton15)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRelayDlg message handlers
#define MAX_RELAY_NUMBER	11
const char *ssRelayNumber[MAX_RELAY_NUMBER] = {"1","2","3","4","5","6","7","8","9","10","11"};
BOOL CRelayDlg::OnInitDialog()
{
	int i;
	CDialog::OnInitDialog();
//		ShowWindow(SW_HIDE);
	ShowWindow(SW_MINIMIZE);

	// TODO: Add extra initialization here
	m_strReceived.Empty();
	((CButton *)GetDlgItem(IDC_HEX))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_ASCII))->SetCheck(FALSE);

	((CButton *)GetDlgItem(IDC_RELAY_ON))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RELAY_OFF))->SetCheck(FALSE);

#if EN_CONSOLE_DISPLAY
	AllocConsole();
	freopen("CON","w",stdout);
#endif
	dwProcessId_0 = 0;
	dwProcessId_1 = 0;
	dwProcessId_2 = 0;
	dwProcessId_3 = 0;
	dwProcessId_4 = 0;
	dwProcessId_5 = 0;
	dwProcessId_6 = 0;
	dwProcessId_7 = 0;
	dwProcessId_8 = 0;
	dwProcessId_9 = 0;

	g_K11K12Stat = 0x03;
	
	g_BlackScreenStatus = 0;
	g_BlackScreenSwitchStatus = 0;
	g_PlayStatus = 0;
	g_SecondCnt = 0;
	g_Player_Mp4_Cnt = 0;
	g_Player_3_MouseClick = 0;
	g_Player_5_MouseClick = 0;
	this->SetTimer(ID_TIMER_1, 1000, NULL);
	this->SetTimer(ID_TIMER_2, 3000, NULL);

#if SELF_TEST
	g_SelfTestTimer = SELF_TEST_KEY_START;
	this->SetTimer(ID_TIMER_SELF_TEST, 5000, NULL);
#endif

	OnBlackScreen();
	Sleep(1000);
//	OnKey_Mp4_Open();
//	Sleep(200);
//	OnKey_1_Open();
//	Sleep(200);
//	OnKey_2_Open();
//	Sleep(200);
//	OnKey_3_Open();
//	Sleep(200);
//	OnKey_4_Open();
//	Sleep(200);
//	OnKey_5_Open();
//	Sleep(200);
//	OnKey_6_Open();
//	Sleep(200);
//	OnKey_7_Open();
//	Sleep(200);
//	OnKey_8_Open();
//	Sleep(200);
//	OnKey_9_Open();
//	Sleep(200);

	OnKey_Mp4_Open();

	RelayNo = 3;
	for(i=0; i<MAX_RELAY_NUMBER; i++)
		m_ctrlRelaySel.AddString(_T(ssRelayNumber[i]));
	m_ctrlRelaySel.SetCurSel(RelayNo);


	DWORD style = WS_VISIBLE|WS_CHILD;
	if(!CommRelay.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM_RELAY))
	{
		AfxMessageBox("Failed to create OLE Communications Control");
		TRACE0("Failed to create OLE Communications Control\n");
	}
	RelayCommOpen();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CRelayDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CRelayDlg)
	ON_EVENT(CRelayDlg, IDC_MSCOMM_RELAY, 1 /* OnComm */, OnCommMscommRelay, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

unsigned int g_PlayerTopStatus_1;

//BOOL CALLBACK EnumWindowsProc(HWND hWnd,LPARAM lParam)
//{
//DWORD thread_id;
//DWORD process_id;

//#if EN_CONSOLE_DISPLAY
//	cout<<g_PlayerTopStatus_1<<endl;
//#endif

// if ( GetParent(hWnd)==NULL  &&  IsWindowVisible(hWnd) )  //判断是否顶层窗口并且可见
// {
//  char WindowTitle[100]={0};
//  ::GetWindowText(hWnd,WindowTitle,100);

//#if EN_CONSOLE_DISPLAY
//  cout<<GetWindowThreadProcessId(hWnd,&process_id)<<" pid is"<<process_id<<endl;
//#endif

//  SetWindowPos(hWnd,HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
//  ::MessageBox(NULL,WindowTitle,NULL,MB_OK);
// }
// return true;
//}

//void CRelayDlg::SwitchPlayerTop()
//{
//	g_PlayerTopStatus_1 = g_PlayerTopStatus;
//	EnumWindows(EnumWindowsProc ,NULL );

//}

void CRelayDlg::OnCommMscommRelay()
{
	if(IsDlgButtonChecked(IDC_ASCII))
		RelayCommSet.bHexAscii = FALSE;
	else
		RelayCommSet.bHexAscii = TRUE;

	if(m_strReceived.GetLength() >= 4000)
		m_strReceived.Empty();

	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.
	CString strtemp;

	int nEvent;

    nEvent = CommRelay.GetCommEvent();

    switch(nEvent)
	{
	case 2:
		variant_inp = CommRelay.GetInput();   //读缓冲区
		safearray_inp = variant_inp;           //VARIANT型变量转换为ColeSafeArray型变量
		len=safearray_inp.GetOneDimSize(); //得到有效数据长度
		for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组

		if(rxdata[0] == 0xff)
		{
			switch(rxdata[1])
			{
//			case KID_K1:	g_PlayerTopStatus = PLAY_1_MASK;	g_SecondCnt = 0;	SwitchPlayerTop();	break;
//			case KID_K2:	g_PlayerTopStatus = PLAY_2_MASK;	g_SecondCnt = 0;	SwitchPlayerTop();	break;
//			case KID_K3:	g_PlayerTopStatus = PLAY_3_MASK;	g_SecondCnt = 0;	SwitchPlayerTop();	break;
//			case KID_K4:	g_PlayerTopStatus = PLAY_4_MASK;	g_SecondCnt = 0;	SwitchPlayerTop();	break;
//			case KID_K5:	g_PlayerTopStatus = PLAY_5_MASK;	g_SecondCnt = 0;	SwitchPlayerTop();	break;
//			case KID_K6:	g_PlayerTopStatus = PLAY_6_MASK;	g_SecondCnt = 0;	SwitchPlayerTop();	break;
//			case KID_K7:	g_PlayerTopStatus = PLAY_7_MASK;	g_SecondCnt = 0;	SwitchPlayerTop();	break;
//			case KID_K8:	g_PlayerTopStatus = PLAY_8_MASK;	g_SecondCnt = 0;	SwitchPlayerTop();	break;

			case KID_K1:	if(g_PlayStatus & PLAY_1_MASK)	g_SecondCnt = 0;	else	{OnKey_1_Open();	this->SetTimer(ID_TIMER_KEY_DEFAULT, PLAY_TIMER_DEFAULT, NULL);}break;
			case KID_K2:	if(g_PlayStatus & PLAY_2_MASK)	g_SecondCnt = 0;	else	{OnKey_2_Open();	this->SetTimer(ID_TIMER_KEY_DEFAULT, PLAY_TIMER_DEFAULT, NULL);}break;
			case KID_K3:	if(g_PlayStatus & PLAY_3_MASK)	g_SecondCnt = 0;	else	{OnKey_3_Open();	this->SetTimer(ID_TIMER_KEY_DEFAULT, PLAY_TIMER_DEFAULT, NULL);}break;
			case KID_K5:	if(g_PlayStatus & PLAY_MP4_MASK)	g_SecondCnt = 0;	else	{OnKey_Mp4_Open();	}break;
//			case KID_K5:	if(g_PlayStatus & PLAY_5_MASK)	g_SecondCnt = 0;	else	OnKey_5_Open();	break;
//			case KID_K6:	if(g_PlayStatus & PLAY_6_MASK)	g_SecondCnt = 0;	else	OnKey_6_Open();	break;
//			case KID_K7:	if(g_PlayStatus & PLAY_7_MASK)	g_SecondCnt = 0;	else	OnKey_7_Open();	break;
//			case KID_K8:	if(g_PlayStatus & PLAY_8_MASK)	g_SecondCnt = 0;	else	OnKey_8_Open();	break;
//			case KID_K9:	if(g_PlayStatus & PLAY_9_MASK)	g_SecondCnt = 0;	else	OnKey_9_Open();	break;
//			case KID_K9:	if(g_PlayStatus & PLAY_MP4_MASK)	g_SecondCnt = 0;	else	OnKey_Mp4_Open();	break;
//			case KID_K10:	if(g_PlayStatus & PLAY_10_MASK)	g_SecondCnt = 0;	else	OnKey_10_Open();	break;
//			case KID_K11:	if(g_PlayStatus & PLAY_11_MASK)	g_SecondCnt = 0;	else	OnKey_11_Open();	break;
//			case KID_K12:	if(g_PlayStatus & PLAY_12_MASK)	g_SecondCnt = 0;	else	OnKey_12_Open();	break;
			}

		}
		if(rxdata[0] == 0xa5)
		{
			g_K11K12Stat = rxdata[1];
		}

		for(k=0;k<len;k++)             //将数组转换为Cstring型变量
		{
			BYTE bt=*(char*)(rxdata+k);      //字符型

			if(RelayCommSet.bHexAscii)
				strtemp.Format("%02X ",bt); //将字符以十六进制方式送入临时变量strtemp存放，注意这里加入一个空隔
			else
				strtemp.Format("%c",bt); //将字符送入临时变量strtemp存放

			m_strReceived += strtemp;    //加入接收编辑框对应字符串
		}
		break;
	case 3:  //CTS线状态发生了变化
		break;
	case 4:  //DSR线状态发生了变化
		break;
	case 5:  //CD线状态发生了变化
		break;
	case 6:  //Ring Indicator发生变化
		break;
    }

	UpdateData(FALSE);
	m_nReceived.Invalidate();
}

void CRelayDlg::RelayCommOpen()
{
	if(CommRelay.GetPortOpen())		CommRelay.SetPortOpen(FALSE);

	CommRelay.SetCommPort(RelayCommSet.nPort);
	CommRelay.SetInBufferSize(1024);
	CommRelay.SetOutBufferSize(512);

	if(!CommRelay.GetPortOpen())	CommRelay.SetPortOpen(TRUE);
	else	AfxMessageBox("cannot open serial port");
	CommRelay.SetInputMode(1);
	CommRelay.SetSettings(RelayCommSet.strSettings);
	CommRelay.SetRThreshold(1);
	CommRelay.SetInputLen(0);
}

void CRelayDlg::OnClearReceived()
{
	// TODO: Add your control notification handler code here
	m_strReceived.Empty();
	UpdateData(FALSE);
	m_nReceived.Invalidate();

}

void CRelayDlg::OnClearSend()
{
	// TODO: Add your control notification handler code here

}

void CRelayDlg::OnSend()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = m_ctrlRelaySel.GetCurSel()+MODULE_RELAY_MIN;

	if(IsDlgButtonChecked(IDC_RELAY_ON))
		RelayCommSet.sendBytes[1] = OPERATE_RELAY_ON;
	else
		RelayCommSet.sendBytes[1] = OPERATE_RELAY_OFF;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

    CommRelay.SetOutput(COleVariant(array)); // 发送数据
}

void CRelayDlg::OnButtonReadAd()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = MODULE_AD1110;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

    CommRelay.SetOutput(COleVariant(array)); // 发送数据
}

void CRelayDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
//	ShowWindow(SW_HIDE);
	// Do not call CDialog::OnPaint() for painting messages
}

void CRelayDlg::OnKey_1()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = 0xff;
	RelayCommSet.sendBytes[1] = KID_K1;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

    CommRelay.SetOutput(COleVariant(array)); // 发送数据
}

void CRelayDlg::OnSelfTest(void)
{
#if SELF_TEST
	int i;

	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = 0xff;
	RelayCommSet.sendBytes[1] = g_SelfTestTimer;

	if(g_SelfTestTimer < SELF_TEST_KEY_STOP)	++g_SelfTestTimer;
	else	g_SelfTestTimer = SELF_TEST_KEY_START;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

	CByteArray array;
	array.RemoveAll();
	array.SetSize(SEND_DATA_LENGTH);

	for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

	CommRelay.SetOutput(COleVariant(array)); // 发送数据
#endif
}

void CRelayDlg::ClosePlayer(unsigned int status)
{
	g_SecondCnt = 0;
	g_Player_3_MouseClick = 0;
	g_Player_5_MouseClick = 0;

#if EN_CONSOLE_DISPLAY
	HANDLE snapshot;
	HANDLE hProcess;
	PROCESSENTRY32 processinfo;
	processinfo.dwSize = sizeof(processinfo);
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

//	system("cls");
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"************-----List-------************"<<endl;
	cout<<"dwProcessId_0(mp4) "<<dwProcessId_0<<endl;
	cout<<"dwProcessId_1(flv) "<<dwProcessId_1<<endl;
	cout<<"dwProcessId_2(ppt) "<<dwProcessId_2<<endl;
	cout<<"dwProcessId_3(ppt) "<<dwProcessId_3<<endl;
	cout<<"dwProcessId_4(ppt) "<<dwProcessId_4<<endl;
	cout<<"dwProcessId_5(ppt) "<<dwProcessId_5<<endl;
	cout<<"dwProcessId_6(ppt) "<<dwProcessId_6<<endl;
	cout<<"dwProcessId_7(ppt) "<<dwProcessId_7<<endl;
	cout<<"dwProcessId_8(ppt) "<<dwProcessId_8<<endl;
	cout<<"dwProcessId_9(ppt) "<<dwProcessId_9<<endl;

	if(snapshot != NULL)
	{
		BOOL status = Process32First(snapshot, &processinfo);
		while(status)
		{
//			cout<<processinfo.szExeFile<<endl;

			if(_stricmp("pptview.exe",processinfo.szExeFile)==0)
			{
				cout<<processinfo.szExeFile<<"   ID is "<<processinfo.th32ProcessID<<endl;
				hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,processinfo.th32ProcessID);
			}
	//			return processinfo.th32ProcessID;
			status = Process32Next(snapshot,&processinfo);
		}
	}
#endif

	SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)/2);

	if(g_PlayStatus & PLAY_1_MASK)	OnKey_1_Open();
	if(g_PlayStatus & PLAY_2_MASK)	OnKey_2_Open();
	if(g_PlayStatus & PLAY_3_MASK)	OnKey_3_Open();
	if(g_PlayStatus & PLAY_4_MASK)	OnKey_4_Open();
	if(g_PlayStatus & PLAY_5_MASK)	OnKey_5_Open();
	if(g_PlayStatus & PLAY_6_MASK)	OnKey_6_Open();
	if(g_PlayStatus & PLAY_7_MASK)	OnKey_7_Open();
	if(g_PlayStatus & PLAY_8_MASK)	OnKey_8_Open();
	if(g_PlayStatus & PLAY_9_MASK)	OnKey_9_Open();
//	if(g_PlayStatus & PLAY_10_MASK)	OnKey_10_Open();
//	if(g_PlayStatus & PLAY_11_MASK)	OnKey_11_Open();
//	if(g_PlayStatus & PLAY_12_MASK)	OnKey_12_Open();
	if(g_PlayStatus & PLAY_MP4_MASK)	OnKey_Mp4_Open();
}

BOOL IsWow64();

void CRelayDlg::OnKey_1_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwX = 0;
	si.dwY = 0;
	si.dwFlags=STARTF_USESHOWWINDOW | STARTF_USEPOSITION ;


	//	Office 2010 pptview
	if(g_PlayStatus & PLAY_1_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_1_MASK;
	}
	else
	{
		ClosePlayer(0);
		this->SetTimer(ID_TIMER_KEY_1, 19000+3000, NULL);
		this->KillTimer(ID_TIMER_KEY_2);
		this->KillTimer(ID_TIMER_KEY_3);
		this->KillTimer(ID_TIMER_KEY_5);
#if 1
		if(IsWow64())
		{
//			AfxMessageBox("64bit system");
			bool fRet=CreateProcess("C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe",
				" \"c:\\program files (x86)\\Kehua setup\\Source\\二、空调制冷介绍.mp4\" /fullscreen",			//	参数，特别注意,需要全路径
				NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);
		}
		else
		{
//			AfxMessageBox("32bit system");
			bool fRet=CreateProcess("C:\\Program Files\\Windows Media Player\\wmplayer.exe",
				" \"c:\\program files\\Kehua setup\\Source\\二、空调制冷介绍.mp4\" /fullscreen",			//	参数，特别注意,需要全路径
				NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);
		}
		dwProcessId_1 = pi.dwProcessId;


//		Sleep(300);
#endif

		OnBlackScreenSwitch();
		g_PlayStatus |= PLAY_1_MASK;
	}

//	ShellExecute(NULL,"open","..\\POWERCUBE500_Client_Source\\1.ppt",NULL,NULL,SW_SHOWNORMAL);

}

void CRelayDlg::OnKey_2_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//	Office 2010 pptview
	if(g_PlayStatus & PLAY_2_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_2_MASK;
	}
	else
	{
		ClosePlayer(0);
		this->KillTimer(ID_TIMER_KEY_1);
		this->SetTimer(ID_TIMER_KEY_2, 18000+3000, NULL);
		this->KillTimer(ID_TIMER_KEY_3);
		this->KillTimer(ID_TIMER_KEY_5);
#if 1
		if(IsWow64())
		{
//			AfxMessageBox("64bit system");
			bool fRet=CreateProcess("C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe",
				" \"c:\\program files (x86)\\Kehua setup\\Source\\三、UPS配电柜介绍.mp4\" /fullscreen",			//	参数，特别注意,需要全路径
				NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);
		}
		else
		{
//			AfxMessageBox("32bit system");
			bool fRet=CreateProcess("C:\\Program Files\\Windows Media Player\\wmplayer.exe",
				" \"c:\\program files\\Kehua setup\\Source\\三、UPS配电柜介绍.mp4\" /fullscreen",			//	参数，特别注意,需要全路径
				NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);
		}
		dwProcessId_2 = pi.dwProcessId;


//		Sleep(300);
#endif

		OnBlackScreenSwitch();
		g_PlayStatus |= PLAY_2_MASK;
	}
}

void CRelayDlg::OnKey_3_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//	Office 2010 pptview
	if(g_PlayStatus & PLAY_3_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_3_MASK;
	}
	else
	{
		ClosePlayer(0);
		this->KillTimer(ID_TIMER_KEY_1);
		this->KillTimer(ID_TIMER_KEY_2);
		this->SetTimer(ID_TIMER_KEY_3, 22000+3000, NULL);
		this->KillTimer(ID_TIMER_KEY_5);
#if 1
		if(IsWow64())
		{
//			AfxMessageBox("64bit system");
			bool fRet=CreateProcess("C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe",
				" \"c:\\program files (x86)\\Kehua setup\\Source\\四、机房监控介绍.mp4\" /fullscreen",			//	参数，特别注意,需要全路径
				NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);
		}
		else
		{
//			AfxMessageBox("32bit system");
			bool fRet=CreateProcess("C:\\Program Files\\Windows Media Player\\wmplayer.exe",
				" \"c:\\program files\\Kehua setup\\Source\\四、机房监控介绍.mp4\" /fullscreen",			//	参数，特别注意,需要全路径
				NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);
		}
		dwProcessId_3 = pi.dwProcessId;


//		Sleep(300);
#endif

		OnBlackScreenSwitch();
		g_PlayStatus |= PLAY_3_MASK;
	}
}

void CRelayDlg::OnKey_4_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//	Office 2010 pptview
	if(g_PlayStatus & PLAY_4_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_4_MASK;
	}
	else
	{
		ClosePlayer(0);

		bool fRet=CreateProcess("..\\POWERCUBE500_Client_Source\\Office14\\PPTVIEW.EXE",
			"/S /F /N1 ..\\POWERCUBE500_Client_Source\\Cases.pptx",			//	参数，特别注意
			NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);

	dwProcessId_4 = pi.dwProcessId;
		OnBlackScreenSwitch();

		g_PlayStatus |= PLAY_4_MASK;
	}
}

void CRelayDlg::OnKey_5_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//	Office 2010 pptview
	if(g_PlayStatus & PLAY_5_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_5_MASK;
	}
	else
	{
		ClosePlayer(0);

		bool fRet=CreateProcess("..\\POWERCUBE500_Client_Source\\Office14\\PPTVIEW.EXE",
			"/S /F /N1 ..\\POWERCUBE500_Client_Source\\SolarMax.pptx",			//	参数，特别注意
			NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);

	dwProcessId_5 = pi.dwProcessId;
		OnBlackScreenSwitch();

		g_PlayStatus |= PLAY_5_MASK;
	}
}

void CRelayDlg::OnKey_6_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//	Office 2010 pptview
	if(g_PlayStatus & PLAY_6_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_6_MASK;
	}
	else
	{
		ClosePlayer(0);

		bool fRet=CreateProcess("..\\POWERCUBE500_Client_Source\\Office14\\PPTVIEW.EXE",
			"/S /F /N1 ..\\POWERCUBE500_Client_Source\\Cases.pptx",			//	参数，特别注意
			NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);

	dwProcessId_6 = pi.dwProcessId;
		OnBlackScreenSwitch();

		g_PlayStatus |= PLAY_6_MASK;
	}
}

void CRelayDlg::OnKey_7_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//	swf
	if(g_PlayStatus & PLAY_7_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_7_MASK;
	}
	else
	{
		ClosePlayer(0);

		bool fRet=CreateProcess("..\\POWERCUBE500_Client_Source\\Office14\\PPTVIEW.EXE",
			"/S /F /N1 ..\\POWERCUBE500_Client_Source\\GridMax.pptx",			//	参数，特别注意
			NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);

	dwProcessId_7 = pi.dwProcessId;
		OnBlackScreenSwitch();

		g_PlayStatus |= PLAY_7_MASK;
	}
}

void CRelayDlg::OnKey_8_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwX = 0;
	si.dwY = 0;
	si.dwFlags=STARTF_USESHOWWINDOW | STARTF_USEPOSITION ;


	//	Office 2010 pptview
	if(g_PlayStatus & PLAY_8_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_8_MASK;
	}
	else
	{
		ClosePlayer(0);

		bool fRet;
		fRet=CreateProcess("..\\POWERCUBE500_Client_Source\\POWERCUBE500_flash_2.EXE",
					NULL,			//	参数，特别注意
					NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);

		dwProcessId_1 = pi.dwProcessId;
		g_PlayStatus |= PLAY_8_MASK;
	}

}

void CRelayDlg::OnKey_9_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwX = 0;
	si.dwY = 0;
	si.dwFlags=STARTF_USESHOWWINDOW | STARTF_USEPOSITION ;


	//	Office 2010 pptview
	if(g_PlayStatus & PLAY_9_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_9_MASK;
	}
	else
	{
		ClosePlayer(0);

		bool fRet;
		fRet=CreateProcess("..\\POWERCUBE500_Client_Source\\POWERCUBE500_flash_3.EXE",
					NULL,			//	参数，特别注意
					NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);

		dwProcessId_1 = pi.dwProcessId;
		g_PlayStatus |= PLAY_9_MASK;
	}

}

#include "windows.h"
typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

LPFN_ISWOW64PROCESS fnIsWow64Process;

BOOL IsWow64()
{
    BOOL bIsWow64 = FALSE;

    fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
        {
            // handle error
        }
    }
    return bIsWow64;
}

void CRelayDlg::OnKey_Mp4_Open()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//	swf
	if(g_PlayStatus & PLAY_MP4_MASK)
	{
		TerminateProcess(pi.hProcess,0);
		g_PlayStatus &= ~PLAY_MP4_MASK;
	}
	else
	{
		g_Player_Mp4_Cnt = 0;
		ClosePlayer(0);
		this->KillTimer(ID_TIMER_KEY_1);
		this->KillTimer(ID_TIMER_KEY_2);
		this->KillTimer(ID_TIMER_KEY_3);
		this->SetTimer(ID_TIMER_KEY_5, 67000+3000, NULL);

#if 1
		if(IsWow64())
		{
//			AfxMessageBox("64bit system");
			bool fRet=CreateProcess("C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe",
				" \"c:\\program files (x86)\\Kehua setup\\\\Source\\一、模块化整体介绍.mp4\" /fullscreen",			//	参数，特别注意,需要全路径
				NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);
		}
		else
		{
//			AfxMessageBox("32bit system");
			bool fRet=CreateProcess("C:\\Program Files\\Windows Media Player\\wmplayer.exe",
				" \"c:\\program files\\Kehua setup\\Source\\一、模块化整体介绍.mp4\" /fullscreen",			//	参数，特别注意,需要全路径
				NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);
		}
		dwProcessId_0 = pi.dwProcessId;


//		Sleep(300);
#endif
		OnBlackScreenSwitch();
		g_PlayStatus |= PLAY_MP4_MASK;
	}
}

void CRelayDlg::OnBlackScreen()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow= SW_SHOW;
	si.dwX = 0;
	si.dwY = 0;
	si.dwFlags=STARTF_USESHOWWINDOW | STARTF_USEPOSITION ;

	//	swf
	if(g_BlackScreenStatus)
	{
		g_BlackScreenStatus = 0;
		TerminateProcess(pi.hProcess,0);
	}
	else
	{
		g_BlackScreenStatus = 1;
		bool fRet=CreateProcess("..\\Source\\MFC_BlackWindow.EXE",
			NULL,			//	参数，特别注意
			NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);

	}
}


void CRelayDlg::OnBlackScreenSwitch()
{
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwX = 0;
	si.dwY = 0;
	si.dwFlags=STARTF_USESHOWWINDOW | STARTF_USEPOSITION ;

	//	swf
	if(g_BlackScreenSwitchStatus)
	{
		g_BlackScreenSwitchStatus = 0;
		TerminateProcess(pi.hProcess,0);
	}
	else
	{
		g_BlackScreenSwitchStatus = 1;

		bool fRet=CreateProcess("..\\Source\\MFC_BlackWindow.EXE",
			NULL,			//	参数，特别注意
			NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);


#if EN_CONSOLE_DISPLAY
	cout<<"  Black screen  "<<endl;
#endif
			this->SetTimer(ID_TIMER_3, 200, NULL);
	}
}


void CRelayDlg::OnTimer(UINT_PTR nIDEvent)
{
	g_SecondCnt ++;
	g_Player_Mp4_Cnt ++;
    switch(nIDEvent)
    {
    default:
        break;

#if SELF_TEST
	case ID_TIMER_SELF_TEST:
		OnSelfTest();
	break;
#endif

	case ID_TIMER_KEY_1:
		OnKey_1_Open();
		OnKey_1_Open();
		break;
	case ID_TIMER_KEY_2:
		OnKey_2_Open();
		OnKey_2_Open();
		break;
	case ID_TIMER_KEY_3:
		OnKey_3_Open();
		OnKey_3_Open();
		break;
	case ID_TIMER_KEY_5:
		OnKey_5_Open();
		OnKey_5_Open();
		break;

	case ID_TIMER_KEY_DEFAULT:
		this->KillTimer(ID_TIMER_KEY_1);
		this->KillTimer(ID_TIMER_KEY_2);
		this->KillTimer(ID_TIMER_KEY_3);
		this->KillTimer(ID_TIMER_KEY_5);
		this->KillTimer(ID_TIMER_KEY_DEFAULT);
		OnKey_Mp4_Open();
		break;
		

	case ID_TIMER_3:
		if(g_BlackScreenSwitchStatus)
		{
			OnBlackScreenSwitch();
		}
		this->KillTimer(ID_TIMER_3);
		break;

	case ID_TIMER_2:
		ShowWindow(SW_MINIMIZE);
		this->KillTimer(ID_TIMER_2);
		break;
		
    case ID_TIMER_1:
		if( (g_PlayStatus & PLAY_2_MASK)
			||(g_PlayStatus & PLAY_4_MASK)
			)
		{
			if(g_SecondCnt % MOUSE_CLICK_TIMER_FOR_KEY_3 == 0)
			{
				CWnd *Cwnd;
				HWND Hwnd;
//				Cwnd = GetActiveWindow();
				Cwnd = GetTopWindow();
				Hwnd = Cwnd->GetSafeHwnd();

				LPARAM lParam = MAKELPARAM(2,2);
				if(INVALID_HANDLE_VALUE != Hwnd)
				{
					if(++g_Player_3_MouseClick < 2)
					{
						mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
						mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
					}
				}
				if(g_SecondCnt == MOUSE_CLICK_TIMER_FOR_KEY_3*2)	//	TIMEOUT_CLOSE)
				{
					ClosePlayer(0);
					OnKey_Mp4_Open();
				}
			}
		}
		else if( (g_PlayStatus & PLAY_1_MASK)
						||(g_PlayStatus & PLAY_3_MASK)	
						)
		{
			if(g_SecondCnt % MOUSE_CLICK_TIMER_FOR_KEY_5 == 0)
			{
				CWnd *Cwnd;
				HWND Hwnd;
//				Cwnd = GetActiveWindow();
				Cwnd = GetTopWindow();
				Hwnd = Cwnd->GetSafeHwnd();

				LPARAM lParam = MAKELPARAM(2,2);
				if(INVALID_HANDLE_VALUE != Hwnd)
				{
					if(++g_Player_5_MouseClick < 3)
					{
						mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
						mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
					}
				}
				if(g_SecondCnt == MOUSE_CLICK_TIMER_FOR_KEY_5*3)	//	TIMEOUT_CLOSE)
				{
					ClosePlayer(0);
					OnKey_Mp4_Open();
				}
			}
		}
		else if(g_PlayStatus | PLAY_MP4_MASK)
		{
			if(g_Player_Mp4_Cnt == PLAYER_Mp4_TIMER)
			{
				OnKey_Mp4_Open();
				Sleep(500);
				OnKey_Mp4_Open();
			}
		}

        break;
    }
	CDialog::OnTimer(nIDEvent);
}


void CRelayDlg::OnBnClickedButton3()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = 0xff;
	RelayCommSet.sendBytes[1] = KID_K2;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

    CommRelay.SetOutput(COleVariant(array)); // 发送数据
}


void CRelayDlg::OnBnClickedButton5()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = 0xff;
	RelayCommSet.sendBytes[1] = KID_K3;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

    CommRelay.SetOutput(COleVariant(array)); // 发送数据
}


void CRelayDlg::OnBnClickedButton7()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = 0xff;
	RelayCommSet.sendBytes[1] = KID_K4;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

    CommRelay.SetOutput(COleVariant(array)); // 发送数据
}


void CRelayDlg::OnBnClickedButton9()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = 0xff;
	RelayCommSet.sendBytes[1] = KID_K5;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

    CommRelay.SetOutput(COleVariant(array)); // 发送数据
}


void CRelayDlg::OnBnClickedButton11()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = 0xff;
	RelayCommSet.sendBytes[1] = KID_K6;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

    CommRelay.SetOutput(COleVariant(array)); // 发送数据
}


void CRelayDlg::OnBnClickedButton13()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		RelayCommSet.sendBytes[i] = 0x00;

	RelayCommSet.sendBytes[0] = 0xff;
	RelayCommSet.sendBytes[1] = KID_K7;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		RelayCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= RelayCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, RelayCommSet.sendBytes[i]);

    CommRelay.SetOutput(COleVariant(array)); // 发送数据
}

void CRelayDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessage(WM_CLOSE);
}


BOOL CRelayDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnBlackScreen();
	this->KillTimer(ID_TIMER_KEY_1);
	this->KillTimer(ID_TIMER_KEY_2);
	this->KillTimer(ID_TIMER_KEY_3);
	this->KillTimer(ID_TIMER_KEY_5);
	this->KillTimer(ID_TIMER_KEY_DEFAULT);

#if EN_CONSOLE_DISPLAY
	FreeConsole();
#endif

	return CDialog::DestroyWindow();
}
