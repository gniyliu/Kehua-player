#include "mscomm.h"
#include "StructVar.h"	// Added by ClassView
#include "OperateConst.h"

#if !defined(AFX_EEPROMDLG_H__2A571950_672F_44C0_AD22_7E8E76779C53__INCLUDED_)
#define AFX_EEPROMDLG_H__2A571950_672F_44C0_AD22_7E8E76779C53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EepromDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEepromDlg dialog

class CEepromDlg : public CDialog
{
// Construction
public:
	CMSComm CommEeprom;
	CommStruct EepromCommSet;
	void EepromCommOpen();
	CEepromDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEepromDlg)
	enum { IDD = IDD_DIALOG_EEPROM };
	CEdit	m_ctrlData;
	CEdit	m_ctrlAddress;
	CEdit	m_nReceived;
	CString	m_strReceived;
	CString	m_strAddress;
	CString	m_strData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEepromDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEepromDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCommMscommEeprom();
	afx_msg void OnClearReceived();
	afx_msg void OnClearSend();
	afx_msg void OnSend();
	afx_msg void OnChangeAddressText();
	afx_msg void OnChangeDataText();
	afx_msg void OnButtonRead8574();
	afx_msg void OnButtonWrite8575();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EEPROMDLG_H__2A571950_672F_44C0_AD22_7E8E76779C53__INCLUDED_)
