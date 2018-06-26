#ifndef _CONST_STRING__H_
#define _CONST_STRING__H_

#define MAX_STR_PORT		10
const char *ssPort[MAX_STR_PORT] = {"Com1","Com2","Com3","Com4","Com5","Com6","Com7","Com8","Com9","Com10"};
#define MAX_STR_BAUD		10
const char *ssBaud[MAX_STR_BAUD] = {"300","600","1200","2400","9600","14400","19200","38400","57600","115200"};
#define MAX_STR_DATA_BITS	5
const char *ssDataBits[MAX_STR_DATA_BITS] = {"4","5","6","7","8"};
#define MAX_STR_STOP_BITS	2
const char *ssStopBits[MAX_STR_STOP_BITS] = {"1","2"};
#define MAX_STR_PARITY		5
const char *ssParity[MAX_STR_PARITY] = {"NONE","EVEN","ODD","MASK","SPACE"};

#endif		//	end definition of _CONST_STRING__H


