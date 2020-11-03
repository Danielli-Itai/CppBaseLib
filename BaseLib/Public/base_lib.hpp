#ifndef	BASE_LIB_HPP
#define	BASE_LIB_HPP
#ifdef	__cplusplus




//	_MSC_VER

	/***********************************************************************\
	*																								*
	*									Include Paths											*
	*																								*
	\***********************************************************************/
	#define	HDR_FW_STRING_CLI		"../../../0.Framework/BaseLib/0.Framework/FwStringCli.hpp"



	#if !(defined(_AFXDLL) || defined(_AFX) || defined(__cplusplus_cli))
		#ifndef USE_STL
			#define	USE_STL
		#endif
	#endif



	/***********************************************************************\
	*																								*
	*									Include Files											*
	*																								*
	\***********************************************************************/
	#ifdef USE_STL
		#include "../../../0.Framework/BaseLib/0.Config/Config.h"
		#include "../../../0.Framework/BaseLib/0.Config/Includes.h"
	#else
		#include "../../../0.Framework/BaseLib/0.Config/ConfigMs.h"
		#include "../../../0.Framework/BaseLib/0.Config/IncludesMs.h"	
	#endif


	#include	HDR_FW_BASE_TYPES
	#include	HDR_FW_ENUMS
	#include	HDR_FW_POINTERS
	#include	HDR_FW_RESULT
	#include	HDR_FW_STRING
	#include	HDR_FW_TEXT_STR


	#ifdef __cplusplus_cli
		#include	HDR_FW_STRING_CLI
	#endif // __cplusplus_cli

#endif	__cplusplus
#endif	//	BASE_LIB_HPP

