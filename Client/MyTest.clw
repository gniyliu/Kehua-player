; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRelayDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyTest.h"
ODLFile=MyTest.odl

ClassCount=7
Class1=CMyTestApp
Class2=CMyTestDlg
Class3=CAboutDlg
Class4=CMyTestDlgAutoProxy

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG_DALLAS
Class5=CDallasDlg
Resource4=IDD_MYTEST_DIALOG
Class6=CEepromDlg
Resource5=IDD_DIALOG_EEPROM
Class7=CRelayDlg
Resource6=IDD_DIALOG_RELAY

[CLS:CMyTestApp]
Type=0
HeaderFile=MyTest.h
ImplementationFile=MyTest.cpp
Filter=N
LastObject=CMyTestApp

[CLS:CMyTestDlg]
Type=0
HeaderFile=MyTestDlg.h
ImplementationFile=MyTestDlg.cpp
Filter=D
LastObject=IDC_CHECK_PORT
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MyTestDlg.h
ImplementationFile=MyTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CMyTestDlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_MYTEST_DIALOG]
Type=1
Class=CMyTestDlg
ControlCount=15
Control1=IDC_SET_DALLAS,button,1208057856
Control2=IDC_SET_EEPROM,button,1208057856
Control3=IDC_SET_RELAY,button,1342276352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1073872896
Control6=IDC_STATIC,static,1073872896
Control7=IDC_STATIC,static,1073872896
Control8=IDC_STATIC,static,1073872896
Control9=IDC_PORT,combobox,1344339970
Control10=IDC_BAUD,combobox,1075904514
Control11=IDC_DATABITS,combobox,1075904514
Control12=IDC_STOPBITS,combobox,1075904514
Control13=IDC_PARITY,combobox,1075904514
Control14=IDC_CHECK_PORT,button,1342242819
Control15=IDC_BUTTON1,button,1073807360

[DLG:IDD_DIALOG_DALLAS]
Type=1
Class=CDallasDlg
ControlCount=21
Control1=IDC_RECEIVED,edit,1352736772
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_ASCII,button,1342308361
Control5=IDC_HEX,button,1342177289
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CLEAR_RECEIVED,button,1342275584
Control8=IDC_CLEAR_SEND,button,1342275584
Control9=IDC_SEND,button,1342275584
Control10=IDC_MSCOMM_DALLAS,{648A5600-2C6E-101B-82B6-000000000014},1073807360
Control11=IDC_RADIO_READ,button,1342308361
Control12=IDC_RADIO_WRITE,button,1342177289
Control13=IDC_MODULE,combobox,1344339970
Control14=IDC_ADDRESS,edit,1350631552
Control15=IDC_DATA,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_MODULE_DE,button,1342308361
Control20=IDC_MODULE_DS,button,1342177289
Control21=IDC_STATIC,static,1342308352

[CLS:CDallasDlg]
Type=0
HeaderFile=dallasdlg.h
ImplementationFile=dallasdlg.cpp
BaseClass=CDialog
LastObject=IDC_RECEIVED
Filter=D
VirtualFilter=dWC

[DLG:IDD_DIALOG_EEPROM]
Type=1
Class=CEepromDlg
ControlCount=19
Control1=IDC_MSCOMM_EEPROM,{648A5600-2C6E-101B-82B6-000000000014},1073807360
Control2=IDC_EDIT1,edit,1352736772
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_ASCII,button,1342308361
Control6=IDC_HEX,button,1342177289
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CLEAR_RECEIVED,button,1342275584
Control9=IDC_CLEAR_SEND,button,1342275584
Control10=IDC_SEND,button,1342275584
Control11=IDC_ADDRESS_TEXT,edit,1350631552
Control12=IDC_DATA_TEXT,edit,1350631552
Control13=IDC_EEPROM_READ,button,1342308361
Control14=IDC_EEPROM_WRITE,button,1342177289
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_BUTTON_READ_8574,button,1342242816
Control19=IDC_BUTTON_WRITE_8575,button,1342242816

[CLS:CEepromDlg]
Type=0
HeaderFile=EepromDlg.h
ImplementationFile=EepromDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_ADDRESS_TEXT

[DLG:IDD_DIALOG_RELAY]
Type=1
Class=CRelayDlg
ControlCount=28
Control1=IDC_EDIT1,edit,1084301316
Control2=IDC_ASCII,button,1073872905
Control3=IDC_HEX,button,1073741833
Control4=IDC_STATIC,static,1073872896
Control5=IDC_CLEAR_RECEIVED,button,1073840128
Control6=IDC_CLEAR_SEND,button,1208057856
Control7=IDC_SEND,button,1073840128
Control8=IDC_STATIC,static,1073872896
Control9=IDC_RELAY_ON,button,1073872905
Control10=IDC_RELAY_OFF,button,1073741833
Control11=IDC_BUTTON_READ_AD,button,1073840128
Control12=IDC_BUTTON1,button,1073807360
Control13=IDC_BUTTON2,button,1073807360
Control14=IDC_BUTTON3,button,1073807360
Control15=IDC_BUTTON4,button,1073807360
Control16=IDC_BUTTON5,button,1073807360
Control17=IDC_BUTTON6,button,1073807360
Control18=IDC_BUTTON7,button,1073807360
Control19=IDC_BUTTON8,button,1073807360
Control20=IDC_BUTTON9,button,1073807360
Control21=IDC_BUTTON10,button,1073807360
Control22=IDC_BUTTON11,button,1073807360
Control23=IDC_BUTTON12,button,1073807360
Control24=IDC_BUTTON13,button,1073807360
Control25=IDC_BUTTON14,button,1073807360
Control26=IDC_RELAY_SEL,combobox,1075904514
Control27=IDC_BUTTON15,button,1342242816
Control28=IDC_MSCOMM_RELAY,{648A5600-2C6E-101B-82B6-000000000014},1073807360

[CLS:CRelayDlg]
Type=0
HeaderFile=RelayDlg.h
ImplementationFile=RelayDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRelayDlg

