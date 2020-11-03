/***********************************************************************\
*																								*
*									P I P E   S E R V E R								*
*																								*
\***********************************************************************/
#ifndef	PIPE_SERVER_WIN_HPP
#define	PIPE_SERVER_WIN_HPP
	#include "../../../0.Framework/BaseLib/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLib/0.Config/IncludesMs.h"




	/***********************************************************************\
	*																								*
	*										Include Files										*
	*																								*
	\***********************************************************************/
	#include <windows.h> 
	#include <stdio.h>
	#include	HDR_FW_PIPE_WIN




	/***********************************************************************\
	*																								*
	*											Class												*
	*																								*
	\***********************************************************************/
	class SPipeIntrf: public SPipeInfo
	{ 
		public:	OVERLAPPED	oOverlap; 
		public:	HANDLE		hPipeInst;

		public:	unsigned long	WriteSize;
		public:	unsigned long	ReadSize;
		public:	char*				ReadBuff;

		public:	CSreverIntrf*	pServer;
	};




	class CPipeServer:	CSreverIntrf
	{
		protected:	HANDLE		hPipe;
		protected:	OVERLAPPED	oConnect; 
 
		protected:	char*			my_pName;
		protected:	bool			my_result;

		public:		virtual	bool	Init(char* name);
		public:		virtual	bool	RunNext();
		public:		virtual	bool	ReadBuffer(SPipeIntrf* lpPipeInst);
		public:		virtual	bool	WritdBuffer(SPipeIntrf* lpPipeInst, char WriteBuffer[BUFSIZE], unsigned long WriteSize);
		public:		virtual	bool	MsgSent(SPipeInfo* pPipeInfo);
		public:		virtual	bool	MsgReceived(SPipeInfo* pPipeInfo, char* pBuff, unsigned long size);
	};
#endif // !PIPE_SERVER_WIN_HPP
