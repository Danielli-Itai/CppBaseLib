/***********************************************************************\
*																								*
*								P I P E   C O N N E C T I O N							*
*																								*
\***********************************************************************/
#ifndef MIC_PIPE_HPP
#define	MIC_PIPE_HPP
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"



	/***********************************************************************\
	*																								*
	*										Definitions											*
	*																								*
	\***********************************************************************/
	#define PIPE_TIMEOUT 5000
	#define BUFSIZE		4096

	#define	PIPE_NAME	"\\\\.\\pipe\\mynamedpipe"
	#define	PIPE_MSG		"Default message from client."




	/***********************************************************************\
	*																								*
	*										Interfaces											*
	*																								*
	\***********************************************************************/

	class SPipeInfo
	{
	};


	class CSreverIntrf
	{
		public:	virtual	bool	MsgSent(SPipeInfo* pPipeInfo) = 0x00;
		public:	virtual	bool	MsgReceived(SPipeInfo* pPipeInfo, char* pBuff, unsigned long size) = 0x00;
	};
#endif // !MIC_PIPE_HPP




