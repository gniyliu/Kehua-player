// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "MyTest.h"
#include "DlgProxy.h"
#include "MyTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTestDlgAutoProxy

IMPLEMENT_DYNCREATE(CMyTestDlgAutoProxy, CCmdTarget)

CMyTestDlgAutoProxy::CMyTestDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CMyTestDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CMyTestDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CMyTestDlgAutoProxy::~CMyTestDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMyTestDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMyTestDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CMyTestDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMyTestDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CMyTestDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMyTest to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {20D8C2DE-92A1-48C5-A305-F414B3C2EC34}
static const IID IID_IMyTest =
{ 0x20d8c2de, 0x92a1, 0x48c5, { 0xa3, 0x5, 0xf4, 0x14, 0xb3, 0xc2, 0xec, 0x34 } };

BEGIN_INTERFACE_MAP(CMyTestDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMyTestDlgAutoProxy, IID_IMyTest, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {E558AC74-B803-4F71-8A5C-221687C0ECDF}
IMPLEMENT_OLECREATE2(CMyTestDlgAutoProxy, "MyTest.Application", 0xe558ac74, 0xb803, 0x4f71, 0x8a, 0x5c, 0x22, 0x16, 0x87, 0xc0, 0xec, 0xdf)

/////////////////////////////////////////////////////////////////////////////
// CMyTestDlgAutoProxy message handlers
