/********************************************************************\
*																							*
*							Command Line Interface									*
*																							*
\********************************************************************/
#include "../../../0.Tools/baselib_source/0.Config/Config.h"
#include "../../../0.Tools/baselib_source/0.Config/Includes.h"




/********************************************************************\
*																							*
*									Include Files										*
*																							*
\********************************************************************/
#include	HDR_FW_INTRF




/********************************************************************\
*																							*
*										Class												*
*																							*
\********************************************************************/

CRedirector::CRedirector() :
	m_hStdinWrite(NULL),
	m_hStdoutRead(NULL),
	m_hChildProcess(NULL),
	m_hThread(NULL),
	m_hEvtStop(NULL),
	m_hEvtWaite(NULL),
	my_replay("")
{
}

CRedirector::~CRedirector()
{
	Exit();
}






//////////////////////////////////////////////////////////////////////
// CRedirector implementation
//////////////////////////////////////////////////////////////////////
BOOL CRedirector::LaunchChild(const char* pszCmdLine, HANDLE hStdOut, HANDLE hStdIn, HANDLE hStdErr)
{
	ASSERT(m_hChildProcess == NULL);

	// Set up the start up info struct.
	STARTUPINFO si;
	::ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.hStdOutput = hStdOut;
	si.hStdInput = hStdIn;
	si.hStdError = hStdErr;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

	// Note that dwFlags must include STARTF_USESHOWWINDOW if we use the wShowWindow flags.
	// This also assumes that the CreateProcess() call will use CREATE_NEW_CONSOLE.
	PROCESS_INFORMATION pi;
	if (!::CreateProcess(NULL, (LPTSTR)pszCmdLine, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		return FALSE;

	m_hChildProcess = pi.hProcess;

	return TRUE;
}

BOOL CRedirector::Open(const char* pszCmdLine)
{
	BOOL bOK = FALSE;

	Exit();

	HANDLE hStdoutReadTmp	= NULL;		// parent stdout read handle
	HANDLE hStdinWriteTmp	= NULL;		// parent stdin write handle
	HANDLE hStdoutWrite		= NULL;		// child stdout write handle
	HANDLE hStdinRead			= NULL;		// child stdin read handle
	HANDLE hStderrWrite		= NULL;		// child stdout error handle

	// Set up the security attributes struct.
	SECURITY_ATTRIBUTES sa	=	{0x00};
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;


	__try
	{
		// Create a child stdout pipe.
		if (!::CreatePipe(&hStdoutReadTmp, &hStdoutWrite, &sa, 0))
			__leave;

		// Create a duplicate of the stdout write handle for the std error write handle.
		// This is necessary in case the child application closes one of its std output handles.
		if (!::DuplicateHandle( ::GetCurrentProcess(), hStdoutWrite, ::GetCurrentProcess(), &hStderrWrite,	0, TRUE, DUPLICATE_SAME_ACCESS))
			__leave;

		// Create a child stdin pipe.
		if (!::CreatePipe(&hStdinRead, &hStdinWriteTmp, &sa, 0))
			__leave;

		// Create new stdout read handle and the stdin write handle.
		// Set the inheritance properties to FALSE and make it uninheritable.
		// Otherwise, the child inherits the these handles; resulting in non-closeable handles to the pipes being created.
		if (!::DuplicateHandle(::GetCurrentProcess(), hStdoutReadTmp, ::GetCurrentProcess(), &m_hStdoutRead, 0, FALSE,	DUPLICATE_SAME_ACCESS))
			__leave;
		if (!::DuplicateHandle(::GetCurrentProcess(), hStdinWriteTmp, ::GetCurrentProcess(), &m_hStdinWrite, 0, FALSE, DUPLICATE_SAME_ACCESS))
			__leave;

		// Close inheritable copies of the handles we do not want to be inherited.
		DestroyHandle(hStdoutReadTmp);
		DestroyHandle(hStdinWriteTmp);

		// launch the child process
		if (!LaunchChild(pszCmdLine, hStdoutWrite, hStdinRead, hStderrWrite))
			__leave;

		// Child is launched.
		// Close the parents copy of those pipe handles that only the child should have open.
		// Make sure that no handles to the write end of the stdout pipe are maintained in this process or else the pipe will not close when the child process exits and ReadFile will hang.
		DestroyHandle(hStdoutWrite);
		DestroyHandle(hStdinRead);
		DestroyHandle(hStderrWrite);

		// Launch a thread to receive output from the child process.
		DWORD	dwThreadId = 0x00;
		m_hEvtStop	= ::CreateEvent(NULL, TRUE, FALSE, NULL);
		m_hThread	= ::CreateThread( NULL, 0, OutputThread, this, 0, &dwThreadId);
		if (!m_hThread)
			__leave;

		bOK = TRUE;
	}

	__finally
	{
		if (!bOK)
		{
			DWORD dwOsErr = ::GetLastError();
			char szMsg[40];
			::sprintf(szMsg, "Redirect console error: %x\r\n", dwOsErr);
			WriteStdError(szMsg);
			DestroyHandle(hStdoutReadTmp);
			DestroyHandle(hStdoutWrite);
			DestroyHandle(hStderrWrite);
			DestroyHandle(hStdinWriteTmp);
			DestroyHandle(hStdinRead);
			Exit();
			::SetLastError(dwOsErr);
		}
	}

	return bOK;
}




void CRedirector::WriteStdOut(const char* pszOutput)
{
	if(NULL != m_hEvtWaite)
	{
		my_replay = pszOutput;
		::SetEvent(m_hEvtWaite);
	}
}

void CRedirector::WriteStdError(char* pszError)
{
}

// redirect the child process's stdout:
// return: 1: no more data, 0: child terminated, -1: os error
int CRedirector::RedirectStdout()
{
	ASSERT(m_hStdoutRead != NULL);

	for (;;)
	{
		DWORD data_size = 0;
		if (!::PeekNamedPipe(m_hStdoutRead, NULL, 0, NULL, &data_size, NULL))			// error
			break;

		if (!data_size)					// not data available
			return 1;

		char szOutput[256];
		DWORD dwRead = 0;
		if (!::ReadFile(m_hStdoutRead, szOutput, min(255, data_size), &dwRead, NULL) || !dwRead)	// error, the child might ended
			break;

		szOutput[dwRead] = 0;
		WriteStdOut(szOutput);
	}

	DWORD dwError = ::GetLastError();
	if (dwError == ERROR_BROKEN_PIPE || dwError == ERROR_NO_DATA)		// pipe has been ended || pipe closing in progress
	{
		WriteStdOut("\r\n<TEST INFO>: Child process ended\r\n");
		return 0;	// child process ended
	}

	WriteStdError("Read stdout pipe error\r\n");
	return -1;		// os error
}


// thread to receive output of the child process
DWORD WINAPI CRedirector::OutputThread(LPVOID lpvThreadParam)
{
	HANDLE aHandles[2];
	int nRet;
	CRedirector* pRedir = (CRedirector*) lpvThreadParam;

	ASSERT(pRedir != NULL);
	aHandles[0] = pRedir->m_hChildProcess;
	aHandles[1] = pRedir->m_hEvtStop;

	for (;;)
	{
		// redirect stdout till there's no more data.
		nRet = pRedir->RedirectStdout();
		if (nRet <= 0)
			break;

		// check if the child process has terminated.
		DWORD dwRc = ::WaitForMultipleObjects(2, aHandles, FALSE, CLI_TIMEOUT/*pRedir->m_dwWaitTime*/);
		if (WAIT_OBJECT_0 == dwRc)		// the child process ended
		{
			nRet = pRedir->RedirectStdout();
			if (nRet > 0)
				nRet = 0;
			break;
		}
		if (WAIT_OBJECT_0+1 == dwRc)	// m_hEvtStop was signalled
		{
			nRet = 1;	// cancelled
			break;
		}
	}

	// close handles
	pRedir->Close();
	return nRet;
}




// write data to the child's stdin
BOOL CRedirector::Printf(const char* pszFormat)
{
	if (!m_hStdinWrite)
		return FALSE;

	std::string strInput = pszFormat;
	DWORD dwWritten;
	return ::WriteFile(m_hStdinWrite, strInput.c_str(), strInput.length(), &dwWritten, NULL);
}
BOOL CRedirector::Printf(const char* pMsg, std::string& replay,  int timeout)
{
	BOOL result = TRUE;
	my_replay = "";

	if (!m_hStdinWrite){
		result = FALSE;
	}
	else if(NULL == m_hEvtWaite)
	{
		std::string strInput = pMsg;
		DWORD dwWritten;
		result &= ::WriteFile(m_hStdinWrite, strInput.c_str(), strInput.length(), &dwWritten, NULL);

		m_hEvtWaite = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		if (::WaitForSingleObject(m_hEvtWaite, timeout) == WAIT_TIMEOUT){
			result = FALSE;
		}
		else{
			replay = my_replay;
		}
		DestroyHandle(m_hEvtWaite);
	}
	return(result);
}





void CRedirector::DestroyHandle(HANDLE& rhObject)
{
	if (rhObject != NULL)
	{
		::CloseHandle(rhObject);
		rhObject = NULL;
	}
}

void CRedirector::Close()
{
	DestroyHandle(m_hStdinWrite);
	DestroyHandle(m_hStdoutRead);

	if(m_hChildProcess){
		::TerminateProcess(m_hChildProcess, 0x00);
		DestroyHandle(m_hChildProcess);
	}
}

void CRedirector::Exit(int timeout)
{
	if (m_hThread != NULL)
	{
		// this function might be called from redir thread
		ASSERT(m_hEvtStop != NULL);
		::SetEvent(m_hEvtStop);
		if (::WaitForSingleObject(m_hThread, timeout) == WAIT_TIMEOUT)
		{
			WriteStdError("The redir thread is dead\r\n");
			::TerminateThread(m_hThread, -2);
		}
		DestroyHandle(m_hEvtStop);
		DestroyHandle(m_hThread);
	}

	Close();
}







