#ifndef FW_PROGRESS_HPP
#define	FW_PROGRESS_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"
	/***********************************************************************\
	*																								*
	*									Include Files											*
	*																								*
	\***********************************************************************/
	#include HDR_FW_BASE_TYPES
	#include	HDR_FW_RESULT
	#include	HDR_FW_POINTERS
	#include HDR_FW_STRING





	/***********************************************************************\
	*																								*
	*										Progress Callback									*
	*																								*
	\***********************************************************************/
	typedef	FW_RESULT (ProgressCb)(std::string message, int val, int max);

	FW_RESULT ProgressCbClr();
	FW_RESULT ProgressCbSet(ProgressCb pCb);
	FW_RESULT ProgressCbCall(STRING message, int val, int max);
#endif // !FW_LOG_HPP
