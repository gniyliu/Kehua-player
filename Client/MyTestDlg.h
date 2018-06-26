// MyTestDlg.h : header file
//
#include "mscomm.h"
#include "DallasDlg.h"
#include "EepromDlg.h"
#include "RelayDlg.h"

#if !defined(AFX_MYTESTDLG_H__0AA03D93_0165_4D5E_A31A_6F40C038C5C0__INCLUDED_)
#define AFX_MYTESTDLG_H__0AA03D93_0165_4D5E_A31A_6F40C038C5C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyTestDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CMyTestDlg dialog

struct CommFigData{
	char Parity;
	int StopBits;
	int DataBits;
	int Baud;
	int Port;
	};

class CMyTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyTestDlg);
	friend class CMyTestDlgAutoProxy;

// Construction
public:
	CDallasDlg DlgDallas;
	CEepromDlg DlgEeprom;
	CRelayDlg DlgRelay;

	void SaveCommSet(void);
	void InitPortSetVar();
	CommFigData CommSet;
	CString strSettings;
	
	int PortNo;
	int BaudNo;
	int DataBitsNo;
	int StopBitsNo;
	int ParityNo;
	
	CMyTestDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMyTestDlg();

// Dialog Data
	//{{AFX_DATA(CMyTestDlg)
	enum { IDD = IDD_MYTEST_DIALOG };
	CComboBox	m_ctrlStopBits;
	CComboBox	m_ctrlPort;
	CComboBox	m_ctrlParity;
	CComboBox	m_ctrlDataBits;
	CComboBox	m_ctrlBaud;
	BOOL	m_ctrlCheckedPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMyTestDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CMyTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeBaud();
	afx_msg void OnSelchangeDatabits();
	afx_msg void OnSelchangeParity();
	afx_msg void OnSelchangePort();
	afx_msg void OnSelchangeStopbits();
	afx_msg void OnCheckPort();
	afx_msg void OnSetDallas();
	afx_msg void OnSetEeprom();
	afx_msg void OnSetRelay();
	afx_msg void OnOpenNotepad();
	afx_msg void OnComSever();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTESTDLG_H__0AA03D93_0165_4D5E_A31A_6F40C038C5C0__INCLUDED_)
