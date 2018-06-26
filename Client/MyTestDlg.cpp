// MyTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyTest.h"
#include "MyTestDlg.h"
#include "DlgProxy.h"
#include "ConstString.h"
#include "DallasDlg.h"
#include "EepromDlg.h"
#include "RelayDlg.h"
#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTestDlg dialog

IMPLEMENT_DYNAMIC(CMyTestDlg, CDialog);

CMyTestDlg::CMyTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyTestDlg)
	m_ctrlCheckedPort = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMyTestDlg::~CMyTestDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMyTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyTestDlg)
	DDX_Control(pDX, IDC_STOPBITS, m_ctrlStopBits);
	DDX_Control(pDX, IDC_PORT, m_ctrlPort);
	DDX_Control(pDX, IDC_PARITY, m_ctrlParity);
	DDX_Control(pDX, IDC_DATABITS, m_ctrlDataBits);
	DDX_Control(pDX, IDC_BAUD, m_ctrlBaud);
	DDX_Check(pDX, IDC_CHECK_PORT, m_ctrlCheckedPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyTestDlg, CDialog)
	//{{AFX_MSG_MAP(CMyTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_BAUD, OnSelchangeBaud)
	ON_CBN_SELCHANGE(IDC_DATABITS, OnSelchangeDatabits)
	ON_CBN_SELCHANGE(IDC_PARITY, OnSelchangeParity)
	ON_CBN_SELCHANGE(IDC_PORT, OnSelchangePort)
	ON_CBN_SELCHANGE(IDC_STOPBITS, OnSelchangeStopbits)
	ON_BN_CLICKED(IDC_CHECK_PORT, OnCheckPort)
	ON_BN_CLICKED(IDC_SET_DALLAS, OnSetDallas)
	ON_BN_CLICKED(IDC_SET_EEPROM, OnSetEeprom)
	ON_BN_CLICKED(IDC_SET_RELAY, OnSetRelay)
	ON_BN_CLICKED(IDC_BUTTON1, OnOpenNotepad)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CMyTestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

extern BOOL IsWow64();

/////////////////////////////////////////////////////////////////////////////
// CMyTestDlg message handlers
BOOL CMyTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitPortSetVar();

#if 1
	if(	PathFileExists("register.txt") )
	{
		//		system("install.bat");
		CString  str_wt=_T("register");
		CString str_rd;
		CStdioFile  File;

		File.Open("register.txt",CFile::modeReadWrite);//如果文件事先不存在的话，就需要CFile::modeCreate，否则就不需要。

		File.ReadString(str_rd);
		if (str_wt.CompareNoCase(str_rd) != 0)	//	不相同
		{
			File.WriteString(str_wt);
		   	if(IsWow64())
				system("install(x64).bat");
			else
				system("install.bat");
		}
		File.Close();
	}
	else
	{
		HANDLE hFile = CreateFile(_T("register.txt"),
				 GENERIC_WRITE, FILE_SHARE_READ,
				 NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//创建文件并获得文件句柄

		   if (hFile == INVALID_HANDLE_VALUE)//如果创建失败
			  AfxMessageBox(_T("Couldn't create the register file!"));
		   else
		   {
		   	if(IsWow64())
				system("install(x64).bat");
			else
				system("install.bat");
		   }
	}
#endif


	int i;
	for(i=0;i<MAX_STR_PORT;i++)
		m_ctrlPort.AddString(_T(ssPort[i]));
	m_ctrlPort.SetCurSel(PortNo);

	for(i=0;i<MAX_STR_BAUD;i++)
		m_ctrlBaud.AddString(_T(ssBaud[i]));
	m_ctrlBaud.SetCurSel(BaudNo);

	for(i=0;i<MAX_STR_DATA_BITS;i++)
		m_ctrlDataBits.AddString(_T(ssDataBits[i]));
	m_ctrlDataBits.SetCurSel(DataBitsNo);

	for(i=0;i<MAX_STR_STOP_BITS;i++)
		m_ctrlStopBits.AddString(_T(ssStopBits[i]));
	m_ctrlStopBits.SetCurSel(StopBitsNo);

	for(i=0;i<MAX_STR_PARITY;i++)
		m_ctrlParity.AddString(_T(ssParity[i]));
	m_ctrlParity.SetCurSel(ParityNo);

	m_ctrlCheckedPort = TRUE;

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CMyTestDlg::OnClose()
{
	if (CanExit())
		CDialog::OnClose();
}

void CMyTestDlg::OnOK()
{
	if (CanExit())
		CDialog::OnOK();
}

void CMyTestDlg::OnCancel()
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CMyTestDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CMyTestDlg::OnSelchangeBaud()
{
	// TODO: Add your control notification handler code here
	SaveCommSet	();
}

void CMyTestDlg::OnSelchangeDatabits()
{
	// TODO: Add your control notification handler code here
	SaveCommSet	();
}

void CMyTestDlg::OnSelchangeParity()
{
	// TODO: Add your control notification handler code here
	SaveCommSet	();
}

void CMyTestDlg::OnSelchangePort()
{
	// TODO: Add your control notification handler code here
	SaveCommSet	();
}

void CMyTestDlg::OnSelchangeStopbits()
{
	// TODO: Add your control notification handler code here
	SaveCommSet	();
}

void CMyTestDlg::InitPortSetVar()
{
	CommSet.Parity = 'N';
	CommSet.StopBits = 1;
	CommSet.DataBits = 8;
	CommSet.Baud = 38400;
	CommSet.Port = 6;
	strSettings	= "38400,N,8,1";
//	strSettings	= "115200,N,8,1";

	PortNo = 5;
	BaudNo = 7;
//	BaudNo = 9;
	DataBitsNo = 4;
	StopBitsNo = 0;
	ParityNo = 0;
}


void CMyTestDlg::SaveCommSet()
{
	CommSet.Port = m_ctrlPort.GetCurSel()+1;

	switch(m_ctrlBaud.GetCurSel())
	{
	case 0:		CommSet.Baud = 300;		break;
	case 1:		CommSet.Baud = 600;		break;
	case 2:		CommSet.Baud = 1200;	break;
	case 3:		CommSet.Baud = 2400;	break;
	case 4:		CommSet.Baud = 9600;	break;
	case 5:		CommSet.Baud = 14400;	break;
	case 6:		CommSet.Baud = 19200;	break;
	case 7:		CommSet.Baud = 38400;	break;
	case 8:		CommSet.Baud = 57600;	break;
	case 9:		CommSet.Baud = 115200;	break;
	default:	CommSet.Baud = 19200;	break;
	}

	switch(m_ctrlParity.GetCurSel())
	{
	case 0:		CommSet.Parity = 'N';	break;
	case 1:		CommSet.Parity = 'E';	break;
	case 2:		CommSet.Parity = 'O';	break;
	case 3:		CommSet.Parity = 'M';	break;
	case 4:		CommSet.Parity = 'S';	break;
	default:	CommSet.Parity = 'N';	break;
	}

	switch(m_ctrlDataBits.GetCurSel())
	{
	case 0:		CommSet.DataBits = 4;	break;
	case 1:		CommSet.DataBits = 5;	break;
	case 2:		CommSet.DataBits = 6;	break;
	case 3:		CommSet.DataBits = 7;	break;
	case 4:		CommSet.DataBits = 8;	break;
	default:	CommSet.DataBits = 8;	break;
	}

	switch(m_ctrlStopBits.GetCurSel())
	{
	case 0:		CommSet.StopBits = 1;	break;
	case 1:		CommSet.StopBits = 2;	break;
	default:	CommSet.StopBits = 1;	break;
	}

	strSettings.Format(_T("%d,%C,%d,%d"),CommSet.Baud,CommSet.Parity,CommSet.DataBits,CommSet.StopBits);
}

void CMyTestDlg::OnCheckPort()
{
	// TODO: Add your control notification handler code here
	if(IsDlgButtonChecked(IDC_CHECK_PORT))
	{
	}
	else
	{
	}
}


BEGIN_EVENTSINK_MAP(CMyTestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CMyTestDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CMyTestDlg::OnSetDallas()
{
	SaveCommSet();
	if(IsDlgButtonChecked(IDC_CHECK_PORT))
	{
		DlgDallas.m_strReceived.Empty();
		DlgDallas.m_strAddress.Empty();
		DlgDallas.m_strData.Empty();
		DlgDallas.DallasCommSet.nPort = CommSet.Port;
		DlgDallas.DallasCommSet.strSettings = strSettings;
		UpdateData();
		DlgDallas.DoModal();
	}
}

void CMyTestDlg::OnSetEeprom()
{
	if(IsDlgButtonChecked(IDC_CHECK_PORT))
	{
		DlgEeprom.m_strReceived.Empty();
		DlgEeprom.EepromCommSet.nPort = CommSet.Port;
		DlgEeprom.EepromCommSet.strSettings = strSettings;
		UpdateData();
		DlgEeprom.DoModal();
	}
}

void CMyTestDlg::OnSetRelay()
{
	if(IsDlgButtonChecked(IDC_CHECK_PORT))
	{
//		ShowWindow(SW_HIDE);
		ShowWindow(SW_MINIMIZE);
		DlgRelay.m_strReceived.Empty();
		DlgRelay.RelayCommSet.nPort = CommSet.Port;
		DlgRelay.RelayCommSet.strSettings = strSettings;
		UpdateData();
		DlgRelay.DoModal();
	}
}

void CMyTestDlg::OnOpenNotepad()
{
	// TODO: Add your control notification handler code here
//	WinExec("Notepad.exe Readme.txt", SW_SHOW);
	ShellExecute(NULL,"open","Readme.txt",NULL,NULL,SW_SHOWNORMAL);
}



void CMyTestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}
