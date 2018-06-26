// EepromDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyTest.h"
#include "EepromDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEepromDlg dialog


CEepromDlg::CEepromDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEepromDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEepromDlg)
	m_strReceived = _T("");
	m_strAddress = _T("");
	m_strData = _T("");
	//}}AFX_DATA_INIT
}


void CEepromDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEepromDlg)
	DDX_Control(pDX, IDC_DATA_TEXT, m_ctrlData);
	DDX_Control(pDX, IDC_ADDRESS_TEXT, m_ctrlAddress);
	DDX_Control(pDX, IDC_EDIT1, m_nReceived);
	DDX_Text(pDX, IDC_EDIT1, m_strReceived);
	DDV_MaxChars(pDX, m_strReceived, 5000);
	DDX_Text(pDX, IDC_ADDRESS_TEXT, m_strAddress);
	DDV_MaxChars(pDX, m_strAddress, 4);
	DDX_Text(pDX, IDC_DATA_TEXT, m_strData);
	DDV_MaxChars(pDX, m_strData, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEepromDlg, CDialog)
	//{{AFX_MSG_MAP(CEepromDlg)
	ON_BN_CLICKED(IDC_CLEAR_RECEIVED, OnClearReceived)
	ON_BN_CLICKED(IDC_CLEAR_SEND, OnClearSend)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_EN_CHANGE(IDC_ADDRESS_TEXT, OnChangeAddressText)
	ON_EN_CHANGE(IDC_DATA_TEXT, OnChangeDataText)
	ON_BN_CLICKED(IDC_BUTTON_READ_8574, OnButtonRead8574)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_8575, OnButtonWrite8575)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEepromDlg message handlers

BOOL CEepromDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_strReceived.Empty();
	((CButton *)GetDlgItem(IDC_HEX))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_ASCII))->SetCheck(FALSE);

	((CButton *)GetDlgItem(IDC_EEPROM_READ))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_EEPROM_WRITE))->SetCheck(FALSE);

	DWORD style = WS_VISIBLE|WS_CHILD;
	if(!CommEeprom.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM_EEPROM))
	{
		TRACE0("Failed to create OLE Communications Control\n");
	}
	EepromCommOpen();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CEepromDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CEepromDlg)
	ON_EVENT(CEepromDlg, IDC_MSCOMM_EEPROM, 1 /* OnComm */, OnCommMscommEeprom, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CEepromDlg::OnCommMscommEeprom() 
{
	if(IsDlgButtonChecked(IDC_ASCII))
		EepromCommSet.bHexAscii = FALSE;
	else
		EepromCommSet.bHexAscii = TRUE;

	if(m_strReceived.GetLength() >= 4000)
		m_strReceived.Empty();

	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.
	CString strtemp;

	int nEvent;
  
    nEvent = CommEeprom.GetCommEvent();

    switch(nEvent)
	{
	case 2:
		variant_inp = CommEeprom.GetInput();   //读缓冲区
		safearray_inp = variant_inp;           //VARIANT型变量转换为ColeSafeArray型变量
		len=safearray_inp.GetOneDimSize(); //得到有效数据长度
		for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
		for(k=0;k<len;k++)             //将数组转换为Cstring型变量
		{
			BYTE bt=*(char*)(rxdata+k);      //字符型
						
			if(EepromCommSet.bHexAscii)
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

void CEepromDlg::EepromCommOpen()
{
	if(CommEeprom.GetPortOpen())		CommEeprom.SetPortOpen(FALSE);

	CommEeprom.SetCommPort(EepromCommSet.nPort);
	CommEeprom.SetInBufferSize(1024);
	CommEeprom.SetOutBufferSize(512);

	if(!CommEeprom.GetPortOpen())	CommEeprom.SetPortOpen(TRUE);
	else	AfxMessageBox("cannot open serial port");
	CommEeprom.SetInputMode(1);
	CommEeprom.SetSettings(EepromCommSet.strSettings);
	CommEeprom.SetRThreshold(1);
	CommEeprom.SetInputLen(0);
}

void CEepromDlg::OnClearReceived() 
{
	m_strReceived.Empty();
	UpdateData(FALSE);
	m_nReceived.Invalidate();
}

void CEepromDlg::OnClearSend() 
{
	m_strAddress.Empty();
	m_strData.Empty();
	UpdateData(FALSE);
	m_nReceived.Invalidate();
}

typedef  char BCD;
BCD HexToBCD(char bcdTemp,BOOL highLow)
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
void CEepromDlg::OnSend() 
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)	
		EepromCommSet.sendBytes[i] = 0x00;

	EepromCommSet.sendBytes[POS_IC_NAME] = MODULE_24LC32;

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

	if( (lengthAddr == 4) && (lengthData == 2) )
	{
		if(IsDlgButtonChecked(IDC_EEPROM_READ))
			EepromCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_24LC32_READ_BYTE;
		else
			EepromCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_24LC32_WRITE_BYTE;

		for(i=0; i<lengthAddr; i++)
		{
			temp = HexToBCD(m_strAddress[i],(i&0x01)^0x01);
			EepromCommSet.sendBytes[POS_IC_ADDR_1+(i>>1)] |= temp;
		}

		for(i=0; i<lengthData; i++)
		{
			temp = HexToBCD(m_strData[i],(i&0x01)^0x01);
			EepromCommSet.sendBytes[POS_DATA_1+(i>>1)] |= temp;
		}
	}
	else
	{
		if(IsDlgButtonChecked(IDC_EEPROM_READ))
			EepromCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_24LC32_READ_ALL;
		else
			EepromCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_24LC32_WRITE_ALL;

		m_strAddress.Empty();
		m_strData.Empty();
		UpdateData(FALSE);
	}

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		EepromCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= EepromCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, EepromCommSet.sendBytes[i]);

    CommEeprom.SetOutput(COleVariant(array)); // 发送数据
}

BOOL CheckHexData(char charTemp)
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
void CEepromDlg::OnChangeAddressText() 
{
	UpdateData(TRUE);
	m_ctrlAddress.Invalidate();

	int i,k;
	k = m_strAddress.GetLength()-1;
	if( !((k>=0)&&(k<4)) )	return;

	for(i=0;i<=k;i++)
	if(!CheckHexData(m_strAddress[i]))
	{
		m_strAddress.Empty();
		break;
	}
	UpdateData(FALSE);
	m_ctrlAddress.Invalidate();
}

void CEepromDlg::OnChangeDataText() 
{
	UpdateData(TRUE);
	m_ctrlData.Invalidate();

	int i,k;
	k = m_strData.GetLength()-1;
	if( !((k>=0)&&(k<2)) )	return;

	for(i=0;i<=k;i++)
	if(!CheckHexData(m_strData[i]))
	{
		m_strData.Empty();
		break;
	}
	UpdateData(FALSE);
	m_ctrlAddress.Invalidate();
}

void CEepromDlg::OnButtonRead8574() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)	
		EepromCommSet.sendBytes[i] = 0x00;

	EepromCommSet.sendBytes[POS_IC_NAME] = MODULE_8574A;

	EepromCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_8574A_READ_BYTE;

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		EepromCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= EepromCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, EepromCommSet.sendBytes[i]);

    CommEeprom.SetOutput(COleVariant(array)); // 发送数据
}

void CEepromDlg::OnButtonWrite8575() 
{
	int i;
	for(i=0;i<SEND_DATA_LENGTH;i++)	
		EepromCommSet.sendBytes[i] = 0x00;

	EepromCommSet.sendBytes[POS_IC_NAME] = MODULE_8574A;

	EepromCommSet.sendBytes[POS_IC_OPT_1] = OPERATE_8574A_WRITE_BYTE;

	long lengthData;
	BCD temp;
	lengthData = m_strData.GetLength();

	if(lengthData<2)	
		EepromCommSet.sendBytes[POS_DATA_1] = 0x00;
	else
	{
		for(i=0; i<lengthData; i++)
		{
			temp = HexToBCD(m_strData[i],(i&0x01)^0x01);
			EepromCommSet.sendBytes[POS_DATA_1+(i>>1)] |= temp;
		}
	}

	for(i=0; i<(SEND_DATA_LENGTH-1); i++)
		EepromCommSet.sendBytes[SEND_DATA_LENGTH-1] ^= EepromCommSet.sendBytes[i];

    CByteArray array;
    array.RemoveAll();
    array.SetSize(SEND_DATA_LENGTH);

    for(i=0;i<SEND_DATA_LENGTH;i++)
	    array.SetAt(i, EepromCommSet.sendBytes[i]);

    CommEeprom.SetOutput(COleVariant(array)); // 发送数据
}
