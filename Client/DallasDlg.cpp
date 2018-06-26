// DallasDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyTest.h"
#include "DallasDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDallasDlg dialog


CDallasDlg::CDallasDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDallasDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDallasDlg)
	m_strReceived = _T("");
	m_strAddress = _T("");
	m_strData = _T("");
	//}}AFX_DATA_INIT
}


void CDallasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDallasDlg)
	DDX_Control(pDX, IDC_DATA, m_ctrlData);
	DDX_Control(pDX, IDC_ADDRESS, m_ctrlAddress);
	DDX_Control(pDX, IDC_MODULE, m_ctrlModule);
	DDX_Control(pDX, IDC_RECEIVED, m_nReceived);
	DDX_Text(pDX, IDC_RECEIVED, m_strReceived);
	DDV_MaxChars(pDX, m_strReceived, 5000);
	DDX_Text(pDX, IDC_ADDRESS, m_strAddress);
	DDV_MaxChars(pDX, m_strAddress, 4);
	DDX_Text(pDX, IDC_DATA, m_strData);
	DDV_MaxChars(pDX, m_strData, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDallasDlg, CDialog)
	//{{AFX_MSG_MAP(CDallasDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CLEAR_RECEIVED, OnClearReceived)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_EN_UPDATE(IDC_ADDRESS, OnUpdateAddress)
	ON_EN_UPDATE(IDC_DATA, OnUpdateData)
	ON_BN_CLICKED(IDC_CLEAR_SEND, OnClearSend)
	ON_EN_CHANGE(IDC_ADDRESS, OnChangeAddress)
	ON_EN_CHANGE(IDC_DATA, OnChangeData)
	ON_EN_MAXTEXT(IDC_RECEIVED, OnMaxtextReceived)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDallasDlg message handlers

#define MAX_DALLAS_MODULE 16
BOOL CDallasDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_strReceived.Empty();
	((CButton *)GetDlgItem(IDC_HEX))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_ASCII))->SetCheck(FALSE);

	((CButton *)GetDlgItem(IDC_RADIO_READ))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO_WRITE))->SetCheck(FALSE);

	((CButton *)GetDlgItem(IDC_MODULE_DE))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_MODULE_DS))->SetCheck(FALSE);

	int i;
	CString strTemp;
	for(i=0;i<MAX_DALLAS_MODULE;i++)
	{
		strTemp.Empty();
		strTemp.Format("%d",i+1);
		m_ctrlModule.AddString(strTemp);
	}
	m_ctrlModule.SetCurSel(0);

	m_strAddress.Empty();
	m_strData.Empty();


	DWORD style = WS_VISIBLE|WS_CHILD;
	if(!CommDallas.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM_DALLAS))
	{
		TRACE0("Failed to create OLE Communications Control\n");
	}
	DallasCommOpen();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDallasDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DestroyWindow();
}

void CDallasDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

int CDallasDlg::DoModal()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DoModal();
}

void CDallasDlg::OnClearReceived()
{
	// TODO: Add your control notification handler code here
	m_strReceived.Empty();
	UpdateData(FALSE);
}

void CDallasDlg::DallasCommOpen()
{
	if(CommDallas.GetPortOpen())		CommDallas.SetPortOpen(FALSE);

	CommDallas.SetCommPort(DallasCommSet.nPort);
	CommDallas.SetInBufferSize(1024);
	CommDallas.SetOutBufferSize(512);

	if(!CommDallas.GetPortOpen())	CommDallas.SetPortOpen(TRUE);
	else	AfxMessageBox("cannot open serial port");
	CommDallas.SetInputMode(1);
	CommDallas.SetSettings(DallasCommSet.strSettings);
	CommDallas.SetRThreshold(1);
	CommDallas.SetInputLen(0);
}

BEGIN_EVENTSINK_MAP(CDallasDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CDallasDlg)
	ON_EVENT(CDallasDlg, IDC_MSCOMM_DALLAS, 1 /* OnComm */, OnCommMscommDallas, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDallasDlg::OnCommMscommDallas()
{
	if(IsDlgButtonChecked(IDC_ASCII))
		DallasCommSet.bHexAscii = FALSE;
	else
		DallasCommSet.bHexAscii = TRUE;

	if(m_strReceived.GetLength() >= 4000)
		m_strReceived.Empty();


	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.
	CString strtemp;

	int nEvent;

    nEvent = CommDallas.GetCommEvent();

    switch(nEvent)
	{
	case 2:
		variant_inp = CommDallas.GetInput();   //读缓冲区
		safearray_inp = variant_inp;           //VARIANT型变量转换为ColeSafeArray型变量
		len=safearray_inp.GetOneDimSize(); //得到有效数据长度
		for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
		for(k=0;k<len;k++)             //将数组转换为Cstring型变量
		{
			BYTE bt=*(char*)(rxdata+k);      //字符型

			if(DallasCommSet.bHexAscii)
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

typedef  char BCD;
BCD DHexToBCD(char bcdTemp,BOOL highLow)
{
	BCD result;
	if( (bcdTemp>='0') && (bcdTemp <= '9') )
		result = bcdTemp-'0';
	if( (bcdTemp>='a') && (bcdTemp <= 'f') )
		result = bcdTemp- 'a' + 10;
	if( (bcdTemp>='A') && (bcdTemp <= 'F') )
		result = bcdTemp -'A' + 10;
	if(result > 0xf)	result = 0;
	if(highLow)		result <<= 4;
	return	result;
}



void CDallasDlg::OnSend()
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)		DallasCommSet.sendBytes[i] = 0x00;

	long lengthAddr,lengthData;
	BCD temp;
	lengthAddr = m_strAddress.GetLength();
	lengthData = m_strData.GetLength();

	if( (lengthAddr < 4) || (lengthData < 2) )
	{
		m_strAddress.Empty();
		m_strData.Empty();
		UpdateData(FALSE);
	}

	if(IsDlgButtonChecked(IDC_MODULE_DE))
		DallasCommSet.sendBytes[POS_IC_NAME] = m_ctrlModule.GetCurSel()+MODULE_DALLAS_DE_MIN;
	else
		DallasCommSet.sendBytes[POS_IC_NAME] = m_ctrlModule.GetCurSel()+MODULE_DALLAS_DS_MIN;

	if( (lengthAddr == 4) && (lengthData == 2) )
	{
		if(IsDlgButtonChecked(IDC_RADIO_READ))
			DallasCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_DALLAS_READ_BYTE;
		else
			DallasCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_DALLAS_WRITE_BYTE;

		for(i=0; i<lengthAddr; i++)
		{
			temp = DHexToBCD(m_strAddress[i], (i&0x01)^0x01);
			DallasCommSet.sendBytes[POS_IC_ADDR_1+(i>>1)] |= temp;
		}

		for(i=0; i<lengthData; i++)
		{
			temp = DHexToBCD(m_strData[i],(i&0x01)^0x01);
			DallasCommSet.sendBytes[POS_DATA_1+(i>>1)] |= temp;
		}
	}
	else
	{
		if(IsDlgButtonChecked(IDC_RADIO_READ))
			DallasCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_DALLAS_READ_ALL;
		else
			DallasCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_DALLAS_WRITE_ALL;
	}

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		DallasCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= DallasCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, DallasCommSet.sendBytes[i]);

    CommDallas.SetOutput(COleVariant(array)); // 发送数据
}



BOOL DCheckHexData(char charTemp)
/*
若参数charTemp为0~9,a~f,A~F则返回TRUE,否则返回FALSE
*/
{
	if( !( ((charTemp >= '0') && (charTemp <= '9')) ||
		   ((charTemp >= 'a') && (charTemp <= 'f')) ||
		   ((charTemp >= 'A') && (charTemp <= 'F')) ) )
	{
		return FALSE;
	}
	return TRUE;
}

void CDallasDlg::OnUpdateAddress()
{
	UpdateData(TRUE);
	m_ctrlAddress.Invalidate();
}

void CDallasDlg::OnUpdateData()
{
	UpdateData(TRUE);
	m_ctrlData.Invalidate();
}

void CDallasDlg::OnClearSend()
{
	m_strAddress.Empty();
	m_strData.Empty();
	UpdateData(FALSE);
}


void CDallasDlg::OnChangeAddress()
{
	UpdateData(TRUE);
	m_ctrlAddress.Invalidate();

	int i,k;
	k = m_strAddress.GetLength()-1;
	if( !((k>=0)&&(k<4)) )	return;

	for(i=0;i<=k;i++)
	if(!DCheckHexData(m_strAddress[i]))
	{
		m_strAddress.Empty();
		break;
	}
	UpdateData(FALSE);
	m_ctrlAddress.Invalidate();
}

void CDallasDlg::OnChangeData()
{
	UpdateData(TRUE);
	m_ctrlData.Invalidate();

	int i,k;
	k = m_strData.GetLength()-1;
	if( !((k>=0)&&(k<2)) )	return;

	for(i=0;i<=k;i++)
	if(!DCheckHexData(m_strData[i]))
	{
		m_strData.Empty();
		break;
	}
	UpdateData(FALSE);
	m_ctrlAddress.Invalidate();
}

void CDallasDlg::OnMaxtextReceived()
{
	// TODO: Add your control notification handler code here
	m_strReceived.Empty();
	UpdateData(FALSE);
}
