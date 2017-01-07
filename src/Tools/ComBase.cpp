// SerialCom.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ComBase.h"


// see ComBase.h for the class definition
CComBase::CComBase()
{
	m_hFile  = INVALID_HANDLE_VALUE;
}

CComBase::~CComBase()
{
	Close();
}

BOOL CComBase::Open(UINT uiPort)
{
	TCHAR szBuf[MAX_PATH];
	memset(szBuf,0,sizeof(szBuf));
	if(uiPort < 10)
	{
		wsprintf(szBuf,"COM%d",uiPort);
	}
	else
	{
		//" \\\\.\\COM10 ",           // 定义串口名
		wsprintf(szBuf,"\\\\.\\COM%d",uiPort);
	}
	return Open(szBuf);
}

BOOL CComBase::Close()
{
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		if(::CloseHandle(m_hFile))
		{
			m_hFile = INVALID_HANDLE_VALUE;
			return TRUE;
		}
		else
		{
			m_hFile = INVALID_HANDLE_VALUE;
			return FALSE;
		}
	}
	m_hFile = INVALID_HANDLE_VALUE;
	return TRUE;
}

/*DWORD CComBase::GetLastErrorCode()
{
	return ::GetLastError();
}*/

LONG CComBase::Write(LPCVOID lpBuf, DWORD dwLen)
{
	if (m_hFile == INVALID_HANDLE_VALUE || dwLen<=0)
	{
		return -1;
	}

	DWORD dwWritten = 0;

	if(WriteFile(m_hFile, lpBuf, dwLen, &dwWritten, NULL))
	{
		return dwWritten;
	}
	
	return -1;
}

/*
LONG CComBase::Read(LPVOID lpBuf, DWORD dwLen)
{
	if (m_hFile == INVALID_HANDLE_VALUE || lpBuf == NULL || dwLen<=0)
		return -1;
	DWORD dwReadLen=0;
	if(ReadFile(m_hFile, lpBuf, dwLen,&dwReadLen,NULL))
		return dwReadLen;
	else
		return -1;
}
//*/
LONG CComBase::Read(LPBYTE lpBuf, DWORD dwMaxLen)
{
	if (m_hFile == INVALID_HANDLE_VALUE || lpBuf == NULL || dwMaxLen<=0)
	{
		return -1;
	}

	DWORD dwReadLenCount = 0;
	DWORD dwReadLen = 0;
	while(1)
	{
		if(dwReadLenCount >= dwMaxLen)
		{
			break;
		}
		
		if(!ReadFile(m_hFile,
					lpBuf+dwReadLenCount, 
					dwMaxLen-dwReadLenCount,
					&dwReadLen,NULL))
		{
			return dwReadLenCount;
		}

		if(dwReadLen<=0) 
		{
			break;
		}

		dwReadLenCount += dwReadLen;
	}
	return dwReadLenCount;
}


LONG CComBase::RecvData2(LPBYTE lpBuf, DWORD dwMaxLen)
{
	if (m_hFile == INVALID_HANDLE_VALUE || lpBuf == NULL || dwMaxLen<=0)
	{
		return -1;
	}

	DWORD dwReadLenCount = 0;
	DWORD dwReadLen = 0;
	while(true)
	{
		if(dwReadLenCount >= dwMaxLen)
		{
			break;
		}
		
		if(!ReadFile(m_hFile,
					lpBuf+dwReadLenCount, 
					dwMaxLen-dwReadLenCount,
					&dwReadLen,NULL))
		{
			return dwReadLenCount;
		}

		if(dwReadLen<=0) 
		{
			if(dwReadLenCount<=0)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		dwReadLenCount += dwReadLen;
	}
	return dwReadLenCount;
}


LONG CComBase::RecvData(LPBYTE lpBuf, DWORD dwNeedLen)
{
	if (m_hFile == INVALID_HANDLE_VALUE || lpBuf == NULL || dwNeedLen<=0)
	{
		return -1;
	}

	DWORD dwReadLenCount = 0;
	DWORD dwReadLen = 0;
	while(1)
	{
		if(dwReadLenCount >= dwNeedLen) 
		{
			break;
		}
		
		if(ReadFile(m_hFile,lpBuf+dwReadLenCount, 
				dwNeedLen-dwReadLenCount,&dwReadLen,NULL))
		{
			if(dwReadLen>0)
			{
				dwReadLenCount += dwReadLen;
			}
			else
			{
				continue;//ReadFile No Data
			}
		}
		else
		{
			continue;//ReadFile Error
		}
	}

	return dwReadLenCount;
}

BOOL CComBase::Setup(EBaudrate eBaudrate)
{
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	if (!::GetCommState(m_hFile,&m_dcb))
	{
		return FALSE;
	}

	// Set the new data
	m_dcb.BaudRate = DWORD(eBaudrate);
	m_dcb.ByteSize = 8;
	m_dcb.Parity   = NOPARITY;
	m_dcb.StopBits = ONESTOPBIT;
	m_dcb.fDtrControl = DTR_CONTROL_DISABLE;
	m_dcb.fRtsControl = RTS_CONTROL_DISABLE;// set RTS bit high!
	//DTR_CONTROL_DISABLE
	//DTR_CONTROL_ENABLE
	//DTR_CONTROL_HANDSHAKE

	// Determine if parity is used
	m_dcb.fParity  = (m_dcb.Parity != NOPARITY);

	// Set the new DCB structure
	if (!::SetCommState(m_hFile,&m_dcb))
	{
		return FALSE;
	}	

	Reset();

	return TRUE;
}

BOOL CComBase::Open(LPCTSTR pPortName)
{	
	// Check if the port isn't already opened
	Close();

	m_hFile = ::CreateFile(pPortName,
						   GENERIC_READ|GENERIC_WRITE,0,
						   //GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,
						   NULL,
						   OPEN_EXISTING,
						   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						   //| FILE_FLAG_OVERLAPPED,
						   NULL);
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
#if(1)		
		//阻塞操作,设置延时
		m_CommTimeouts.ReadIntervalTimeout			=	100L;//两个字符的时间间隔
		m_CommTimeouts.ReadTotalTimeoutMultiplier	=	10L;
		m_CommTimeouts.ReadTotalTimeoutConstant		=	100L;
		m_CommTimeouts.WriteTotalTimeoutMultiplier	=	10L;
		m_CommTimeouts.WriteTotalTimeoutConstant	=	100L;
		
/*
		//非阻塞操作设置XXXXXXXXXXXX
		m_CommTimeouts.ReadIntervalTimeout          =   MAXDWORD;
		m_CommTimeouts.ReadTotalTimeoutMultiplier	=	0L;
		m_CommTimeouts.ReadTotalTimeoutConstant		=	0L;
		m_CommTimeouts.WriteTotalTimeoutMultiplier	=	0L;
		m_CommTimeouts.WriteTotalTimeoutConstant	=	100L;//*/
#else
		//非阻塞操作设置
		m_CommTimeouts.ReadIntervalTimeout = MAXDWORD;
		m_CommTimeouts.ReadTotalTimeoutMultiplier = 0;
		m_CommTimeouts.ReadTotalTimeoutConstant = MAXDWORD;
		m_CommTimeouts.WriteTotalTimeoutMultiplier = 0;
		m_CommTimeouts.WriteTotalTimeoutConstant = MAXDWORD;
#endif
		SetCommTimeouts(m_hFile, &m_CommTimeouts);
		
		return Setup();
	}
	return FALSE;
}

BOOL CComBase::Reset(void)
{
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	PurgeComm(m_hFile,PURGE_TXCLEAR);
	PurgeComm(m_hFile,PURGE_RXCLEAR);

	return TRUE;
}

BOOL CComBase::IsOpen(void)
{
	return (m_hFile != INVALID_HANDLE_VALUE);
}
