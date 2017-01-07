#ifndef _SERIALCOM_H_
#define _SERIALCOM_H_

#define MAX_COMMBUF	1024

class CComBase {
public:
	typedef enum
	{
		EBaudUnknown = -1,			// Unknown
		EBaud110     = CBR_110,		// 110 bits/sec
		EBaud300     = CBR_300,		// 300 bits/sec
		EBaud600     = CBR_600,		// 600 bits/sec
		EBaud1200    = CBR_1200,	// 1200 bits/sec
		EBaud2400    = CBR_2400,	// 2400 bits/sec
		EBaud4800    = CBR_4800,	// 4800 bits/sec
		EBaud9600    = CBR_9600,	// 9600 bits/sec
		EBaud14400   = CBR_14400,	// 14400 bits/sec
		EBaud19200   = CBR_19200,	// 19200 bits/sec 
		EBaud38400   = CBR_38400,	// 38400 bits/sec
		EBaud56000   = CBR_56000,	// 56000 bits/sec
		EBaud57600   = CBR_57600,	// 57600 bits/sec
		EBaud115200  = CBR_115200,	// 115200 bits/sec
		EBaud128000  = CBR_128000,	// 128000 bits/sec
		EBaud256000  = CBR_256000,	// 256000 bits/sec
	}EBaudrate;

	BOOL Setup(EBaudrate eBaudrate = EBaud115200);
	//BOOL Setup(EBaudrate eBaudrate = EBaud9600);
	LONG Write(LPCVOID lpBuf,DWORD dwLen);
	LONG Read(LPBYTE lpBuf, DWORD dwMaxLen);		//一次性接收数据
	LONG RecvData2(LPBYTE lpBuf, DWORD dwMaxLen);	//一次性接收数据,收到数据就返回
	LONG RecvData(LPBYTE lpBuf, DWORD dwNeedLen);	//收到所需长度才返回
	//DWORD GetLastErrorCode();
	BOOL Open(UINT uiPort);	
	virtual BOOL Close();
	virtual  ~CComBase();
	CComBase(void);
	BOOL Reset(void);
	BOOL IsOpen(void);
	// TODO: add your methods here.
protected:
	BOOL	Open(LPCTSTR pPortName);
	HANDLE	m_hFile;
	DCB		m_dcb;
	COMMTIMEOUTS		m_CommTimeouts;//延时结构	
};


#endif //_SERIALCOM_H_