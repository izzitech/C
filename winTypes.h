/* --------------------------------------------------------
||
||    	My own handworked replacement for crappy WinAPI
||
||
||				Author: Iván E. Sierra
||				Date: 2016-06-09
||
||
//----------------------------------------------------------*/

// Replacement for POINT
typedef struct Point
{
	long  x;
	long  y;
};

// Replacement for tagMSG / MSG 
typedef struct Message {
	void* handle;
	unsigned int value;
	void* param1;
	void* param2;
	unsigned long* time;
	struct Point point;
};

// Replacement for WNDCLASSW
typedef struct Window {
	unsigned int style;
	void* process;
	int cbClsExtra;
	int cbWndExtra;
	void* handle;
	void* icon;
	void* cursor;
	void* background;
	unsigned short* menuName;
	unsigned short* className;
};