#ifndef FW_DEBUGGING_MS_HPP
#define	FW_DEBUGGING_MS_HPP
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





	/***********************************************************************\
	*																								*
	*											Include Files									*
	*																								*
	\***********************************************************************/
	//#include	HDR_STDAFX
	#include	HDR_FW_ENUMS





	/***********************************************************************\
	*																								*
	*											Debugging										*
	*																								*
	\***********************************************************************/
	/*	Debug level defines the application sensitivity to errors
	*	The higher the level the more sensitive the application becomes
	*/
	#define	DEBUG_FIELDS	\
		DEBUG_DOA				\
		,DEBUG_SANITY			\
		,DEBUG_FULL				\
		,DEBUG_ALPHA			\
		,DEBUG_BETA				\
		,DEBUG_RELEASE			\
		/*DEBUG_FIELDS*/

	#define	DEBUG_NAMES		\
		"DEBUG_DOA"				\
		,"DEBUG_SANITY"		\
		,"DEBUG_FULL"			\
		,"DEBUG_ALPHA"			\
		,"DEBUG_BETA"			\
		,"DEBUG_RELEASE"		\
		/*DEBUG_NAMES*/
	/*	Debugging enumerator.*/
	ENUM_DEFINE(DEBUG_LEVEL, DEBUG_FIELDS);
	
	bool	DebugChk(DEBUG_LEVEL state);
	#define DEBUG_ALERT(LEVEL,RES)		\
		if(false == RES){						\
			RES_ALERT(DebugChk(LEVEL));	\
		}											\
		/*DEBUG_ALERT*/

	#define DEBUG_RETURN(LEVEL,RES)		\
		if(DebugChk(LEVEL)){		\
			RES_ALERT(RES);		\
		}								\
		RETURN(RES);				\
		/*DEBUG_RETURN*/




#endif // !FW_DEBUGGING_MS_HPP
