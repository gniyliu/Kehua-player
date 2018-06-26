#include "mscomm.h"
#include "StructVar.h"	// Added by ClassView
#include "OperateConst.h"

#if !defined(AFX_DALLASDLG_H__4B97CBC8_2295_4E74_85EE_1C31FB585D33__INCLUDED_)
#define AFX_DALLASDLG_H__4B97CBC8_2295_4E74_85EE_1C31FB585D33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DallasDlg.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDallasDlg dialog

class CDallasDlg : public CDialog
{
// Construction
public:
	CommStruct DallasCommSet;
	void DallasCommOpen();
	CMSComm CommDallas;
	CDallasDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDallasDlg)
	enum { IDD = IDD_DIALOG_DALLAS };
	CEdit	m_ctrlData;
	CEdit	m_ctrlAddress;
	CComboBox	m_ctrlModule;
	CEdit	m_nReceived;
	CString	m_strReceived;
	CString	m_strAddress;
	CString	m_strData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDallasDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDallasDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnClearReceived();
	afx_msg void OnCommMscommDallas();
	afx_msg void OnSend();
	afx_msg void OnUpdateAddress();
	afx_msg void OnUpdateData();
	afx_msg void OnClearSend();
	afx_msg void OnChangeAddress();
	afx_msg void OnChangeData();
	afx_msg void OnMaxtextReceived();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DALLASDLG_H__4B97CBC8_2295_4E74_85EE_1C31FB585D33__INCLUDED_)
