/***********************************************************************\
*																								*
*									P I P E   C L I E N T								*
*																								*
\***********************************************************************/
#ifndef PIPE_CLIENT_WIN_HPP
#define	PIPE_CLIENT_WIN_HPP
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"




	/***********************************************************************\
	*																								*
	*										Include Files										*
	*																								*
	\***********************************************************************/
	#include <windows.h> 
	#include	HDR_FW_PIPE




	/***********************************************************************\
	*																								*
	*											Class												*
	*																								*
	\***********************************************************************/
	class CPipeClient
	{
		HANDLE hPipe; 
		unsigned long dwMode;

		public:	CPipeClient();
		public: virtual	~CPipeClient();

		public:	bool	Connect(char* lpszPipename);
		public:	bool	Write(unsigned long cbToWrite, char* lpvMessage, unsigned long& cbWritten);
		public:	bool	Read(unsigned long  cbSize, char chBuf[BUFSIZE], unsigned long&  cbRead);
		public:	bool	Close();
	};
#endif // !PIPE_CLIENT_WIN_HPP
