#ifndef _STRUCT_VAR__H_
#define _STRUCT_VAR__H_

#define SEND_DATA_LENGTH	16
struct CommStruct{
	BOOL bHexAscii;
	int nPort;
	CString strSettings;
	CString strReceive;
	unsigned char sendBytes[SEND_DATA_LENGTH];
	};

#define POS_IC_NAME		0
#define POS_IC_OPT_1	1
#define POS_IC_OPT_2	2
#define POS_IC_OPT_3	3
#define POS_IC_ADDR_1	4
#define POS_IC_ADDR_2	5
#define POS_IC_ADDR_3	6
#define POS_DATA_1		7
#define POS_DATA_2		8
#define POS_DATA_3		9
#define POS_DATA_4		10
#define POS_DATA_5		11
#define POS_DATA_6		12
#define POS_DATA_7		13
#define POS_DATA_8		14
#define POS_PARITY		15

#endif	//	end definition of _STRUCT_VAR__H_




