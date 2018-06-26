// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__202D0536_FF0C_47AD_A657_828D734423CA__INCLUDED_)
#define AFX_DLGPROXY_H__202D0536_FF0C_47AD_A657_828D734423CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyTestDlg;

/////////////////////////////////////////////////////////////////////////////
// CMyTestDlgAutoProxy command target

class CMyTestDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMyTestDlgAutoProxy)

	CMyTestDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CMyTestDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTestDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyTestDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CMyTestDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMyTestDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMyTestDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__202D0536_FF0C_47AD_A657_828D734423CA__INCLUDED_)
