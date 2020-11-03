#ifndef DEBUGGING_H
#define	DEBUGGING_H
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





	/***********************************************************************\
	*																								*
	*											Include Files									*
	*																								*
	\***********************************************************************/
	#include	<assert.h>
	#include	HDR_FW_ENUMS





	/***********************************************************************\
	*																								*
	*											Definitions										*
	*																								*
	\***********************************************************************/
	#ifdef	__cplusplus
		#ifdef ASSERT
			#undef	ASSERT
		#endif // ASSERT
		#define	ASSERT							assert
	#endif





	/***********************************************************************\
	*																								*
	*										D e b u g g i n g									*
	*																								*
	\***********************************************************************/
	/*	Debug level defines the application sensitivity to errors
	*	The higher the level the more sensitive the application becomes
	*/
	#define	DEBUG_FIELDS	\
			DEBUG_DOA			\
		,	DEBUG_SANITY		\
		,	DEBUG_FULL			\
		,	DEBUG_ALPHA			\
		,	DEBUG_BETA			\
		,	DEBUG_RELEASE		\
		/*DEBUG_FIELDS*/

	#define	DEBUG_NAMES		\
			"DEBUG_DOA"			\
		,	"DEBUG_SANITY"		\
		,	"DEBUG_FULL"		\
		,	"DEBUG_ALPHA"		\
		,	"DEBUG_BETA"		\
		,	"DEBUG_RELEASE"	\
		/*DEBUG_NAMES*/
	/*	Debugging enumerator.*/
	ENUM_DEFINE(DEBUG_LEVEL, DEBUG_FIELDS);

	bool	DebugChk(DEBUG_LEVEL state);

	#define DEBUG_ALERT(LEVEL,RES)			\
			if(false == RES){						\
					RES_ALERT(DebugChk(LEVEL));\
			}											\
			/*DEBUG_ALERT*/

	#define DEBUG_RETURN(LEVEL,RES)			\
			if(DebugChk(LEVEL)){					\
					RES_ALERT(RES);				\
			}											\
			RETURN(RES);							\
			/*DEBUG_RETURN*/

#endif // !DEBUGGING_H