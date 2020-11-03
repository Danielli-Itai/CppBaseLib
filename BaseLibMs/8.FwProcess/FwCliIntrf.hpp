#ifndef REDIR_H
#define REDIR_H

	//#include "stdafx.h"
	#include	<windows.h>
	//#include	<winnt.h>
	#include	<string>
	#include	<cassert>

//	#define	TRACE(FORMAT, INFO)		printf(FORMAT,INFO)
	#define	ASSERT				assert
	#define	CLI_TIMEOUT		5000


	class CRedirector  
	{
		public:	CRedirector();
		public:	virtual ~CRedirector();


		protected:	HANDLE	m_hStdinWrite;		// write end of child's stdin pipe
		protected:	HANDLE	m_hStdoutRead;		// read end of child's stdout pipe
		protected:	HANDLE	m_hChildProcess;

		protected:	BOOL	LaunchChild(const char* pszCmdLine, HANDLE hStdOut, HANDLE hStdIn, HANDLE hStdErr);
		public:		BOOL	Open(const char* pszCmdLine);

		private:		HANDLE	m_hThread;			// thread to receive the output of the child process
		private:		HANDLE	m_hEvtStop;			// event to notify the redir thread to exit
		protected:	int	RedirectStdout();
		protected:	static DWORD WINAPI OutputThread(LPVOID lpvThreadParam);


			// overrides:
		private:		HANDLE	m_hEvtWaite;			// event to notify the redir thread to exit
		protected:	virtual void WriteStdOut(const char* pszOutput);
		protected:	virtual void WriteStdError(char* pszError);

		private:		std::string	my_replay;
		public:		BOOL	Printf(const char* pszFormat);
		public:		BOOL	Printf(const char* pMsg, std::string& replay,  int timeout);


		protected:	void	DestroyHandle(HANDLE& rhObject);
		public:		void	Close();
		public:		virtual void Exit(int timeout = 5000);
	};
#endif // !defined(AFX_REDIR_H__4FB57DC3_29A3_11D5_BB60_006097553C52__INCLUDED_)
