#ifndef _OPERATE_CONST__H_
#define _OPERATE_CONST__H_

/*	����������	*/
#define MODULE_DALLAS_DE_MIN	0x01
#define MODULE_DALLAS_DE_MAX	0x10
#define MODULE_DALLAS_DE_1		0x01
#define MODULE_DALLAS_DE_2		0x02
#define MODULE_DALLAS_DE_3		0x03
#define MODULE_DALLAS_DE_4		0x04
#define MODULE_DALLAS_DE_5		0x05
#define MODULE_DALLAS_DE_6		0x06
#define MODULE_DALLAS_DE_7		0x07
#define MODULE_DALLAS_DE_8		0x08
#define MODULE_DALLAS_DE_9		0x09
#define MODULE_DALLAS_DE_10		0x0a
#define MODULE_DALLAS_DE_11		0x0b
#define MODULE_DALLAS_DE_12		0x0c
#define MODULE_DALLAS_DE_13		0x0d
#define MODULE_DALLAS_DE_14		0x0e
#define MODULE_DALLAS_DE_15		0x0f
#define MODULE_DALLAS_DE_16		0x10

#define MODULE_DALLAS_DS_MIN	0x31
#define MODULE_DALLAS_DS_MAX	0x40
#define MODULE_DALLAS_DS_1		0x31
#define MODULE_DALLAS_DS_2		0x32
#define MODULE_DALLAS_DS_3		0x33
#define MODULE_DALLAS_DS_4		0x34
#define MODULE_DALLAS_DS_5		0x35
#define MODULE_DALLAS_DS_6		0x36
#define MODULE_DALLAS_DS_7		0x37
#define MODULE_DALLAS_DS_8		0x38
#define MODULE_DALLAS_DS_9		0x39
#define MODULE_DALLAS_DS_10		0x3a        
#define MODULE_DALLAS_DS_11		0x3b        
#define MODULE_DALLAS_DS_12		0x3c        
#define MODULE_DALLAS_DS_13		0x3d        
#define MODULE_DALLAS_DS_14		0x3e        
#define MODULE_DALLAS_DS_15		0x3f        
#define MODULE_DALLAS_DS_16		0x40

#define MODULE_24LC32			0x51
#define MODULE_8574A			0x52
#define MODULE_AD1110			0x53

#define MODULE_RELAY_MIN		0x71
#define MODULE_RELAY_MAX		0x7b
#define MODULE_RELAY_1			0x71
#define MODULE_RELAY_2			0x72
#define MODULE_RELAY_3			0x73
#define MODULE_RELAY_4			0x74
#define MODULE_RELAY_5			0x75
#define MODULE_RELAY_6			0x76
#define MODULE_RELAY_7			0x77
#define MODULE_RELAY_8			0x78
#define MODULE_RELAY_9			0x79
#define MODULE_RELAY_10			0x7a
#define MODULE_RELAY_11			0x7b

/*	Dallas�����Ĳ���������	*/
#define OPERATE_DALLAS_READ_BYTE	0x01
#define OPERATE_DALLAS_WRITE_BYTE	0x02
#define OPERATE_DALLAS_READ_ALL		0x03
#define OPERATE_DALLAS_WRITE_ALL	0x04


/*	24lc32�����Ĳ���������	*/
#define OPERATE_24LC32_READ_BYTE	0x01
#define OPERATE_24LC32_WRITE_BYTE	0x02
#define OPERATE_24LC32_READ_ALL		0x03
#define OPERATE_24LC32_WRITE_ALL	0x04

/*	8574A�����Ĳ���������	*/
#define OPERATE_8574A_READ_BYTE		0x01
#define OPERATE_8574A_WRITE_BYTE	0x02
#define OPERATE_8574A_READ_ALL		0x03
#define OPERATE_8574A_WRITE_ALL		0x04

/*	Relay(�̵���)�����Ĳ���������	*/
#define OPERATE_RELAY_ON		0x01
#define OPERATE_RELAY_OFF		0x02


#endif /*	end definition _OPERATE_CONST__H_	*/