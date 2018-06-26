#include "mscomm.h"
#include "StructVar.h"	// Added by ClassView
#include "OperateConst.h"

#if !defined(AFX_RELAYDLG_H__D64452C0_DA79_4A3D_A673_A1F0C57E5459__INCLUDED_)
#define AFX_RELAYDLG_H__D64452C0_DA79_4A3D_A673_A1F0C57E5459__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RelayDlg.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CRelayDlg dialog

class CRelayDlg : public CDialog
{
// Construction
public:
	unsigned int g_PlayerTopStatus;
	unsigned int g_PlayStatus;
	unsigned int g_BlackScreenStatus;
	unsigned int g_BlackScreenSwitchStatus;
	unsigned int g_SecondCnt;
	unsigned int g_Player_3_MouseClick;
	unsigned int g_Player_5_MouseClick;
	unsigned int g_Player_Mp4_Cnt;

	unsigned int g_SelfTestTimer;
	
	unsigned int g_K11K12Stat;

DWORD dwProcessId_0;	//	mp4 pid
DWORD dwProcessId_1;
DWORD dwProcessId_2;
DWORD dwProcessId_3;
DWORD dwProcessId_4;
DWORD dwProcessId_5;
DWORD dwProcessId_6;
DWORD dwProcessId_7;
DWORD dwProcessId_8;
DWORD dwProcessId_9;

	int RelayNo;
	CMSComm CommRelay;
	CommStruct RelayCommSet;
	void RelayCommOpen();
	void ClosePlayer(unsigned int status);
	void OnKey_Mp4_Open();
	void OnKey_8_Open();
	void OnKey_9_Open();
	void OnBlackScreen();
	void OnBlackScreenSwitch();
	void SwitchPlayerTop();
	void OnSelfTest(void);
	CRelayDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRelayDlg)
	enum { IDD = IDD_DIALOG_RELAY };
	enum
	{
	  ID_TIMER_1 = 100,
	  ID_TIMER_2 = 101,
	  ID_TIMER_3 = 102,				//	用于切换黑屏自杀时间
	  ID_TIMER_4 = 103,
	  ID_TIMER_KEY_1 = 104,
	  ID_TIMER_KEY_2 = 105,
	  ID_TIMER_KEY_3 = 106,
	  ID_TIMER_KEY_5 = 107,
	  ID_TIMER_KEY_DEFAULT = 108,
	  ID_TIMER_SELF_TEST = 200,
	};
	CComboBox	m_ctrlRelaySel;
	CEdit	m_nReceived;
	CString	m_strReceived;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRelayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCommMscommRelay();
	afx_msg void OnClearReceived();
	afx_msg void OnClearSend();
	afx_msg void OnSend();
	afx_msg void OnButtonReadAd();
	afx_msg void OnPaint();
	afx_msg void OnKey_1();
	afx_msg void OnKey_1_Open();
	afx_msg void OnKey_2_Open();
	afx_msg void OnKey_3_Open();
	afx_msg void OnKey_4_Open();
	afx_msg void OnKey_5_Open();
	afx_msg void OnKey_6_Open();
	afx_msg void OnKey_7_Open();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton15();
	virtual BOOL DestroyWindow();
};

#define PLAY_1_MASK				0x01
#define PLAY_2_MASK				0x02
#define PLAY_3_MASK				0x04
#define PLAY_4_MASK				0x08
#define PLAY_5_MASK				0x10
#define PLAY_6_MASK				0x20
#define PLAY_7_MASK				0x40
#define PLAY_8_MASK				0x80
#define PLAY_9_MASK				0x100
#define PLAY_10_MASK			0x200
#define PLAY_11_MASK			0x400
#define PLAY_12_MASK			0x800
#define PLAY_MP4_MASK				0x8000

#define PLAY_TIMER_DEFAULT		(10*60000)
#define MOUSE_CLICK_TIMER_FOR_KEY_3				(5*60)
#define TIMEOUT_CLOSE					5*60	//	5 minute
#define PLAYER_Mp4_TIMER			180		//	second
#define MOUSE_CLICK_TIMER_FOR_KEY_5				((5*60))

enum KEY_ID{
KID_PWR,
KID_INC,
KID_DEC,

KID_K1,
KID_K2,
KID_K3,
KID_K4,
KID_K5,
KID_K6,
KID_K7,
KID_K8,
KID_K9,
KID_K10,
KID_K11,
KID_K12,

KID_NULL,
};

#define SELF_TEST		0		//	自动发送串口数据测试，自发自收
#define SELF_TEST_KEY_START		KID_K6
#define SELF_TEST_KEY_STOP		KID_K8

#define EN_CONSOLE_DISPLAY		0		//	允许控制台输出


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELAYDLG_H__D64452C0_DA79_4A3D_A673_A1F0C57E5459__INCLUDED_)
