#ifndef FW_RESULT_HPP
#define	FW_RESULT_HPP
	#include	<assert.h>
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





	/***********************************************************************\
	*																								*
	*											Alert												*
	*																								*
	\***********************************************************************/
	#ifdef	__cplusplus
		#ifdef ASSERT
			#undef	ASSERT
		#endif // ASSERT
		#define	ASSERT							assert
	#endif





	/********************************************************************\
	*																							*
	*                           Result Macros										*
	*																							*
	\********************************************************************/

	#define		RETURN(OBJ)							return(OBJ)

	#ifdef	__cplusplus
		#define		FW_RESULT							bool
		#define		RES_OK							true
		#define		RES_ERR							false
	#else
		#define		FW_RESULT							int
		#define		RES_OK							0x01
		#define		RES_ERR							0x00
	#endif


	#define RES_STR(RES)										\
			(true == RES?  STR_OK:STR_ERR)				\
			/*RES_DECLR*/


	#define		RES_DECLR(RES)					FW_RESULT	RES = RES_OK;
	#define		RES_INIT(RES)								RES = RES_OK;
	#define		RES_DECLR_INIT(RES,INIT)	FW_RESULT	RES = (INIT)
	#define		RES_FAILE(RES)								RES = RES_ERR;
	#define		RES_SUCCESS(RES)							RES = RES_OK;
	//#define		RES_CHECK(RES,CHCK)					RES = CHCK && (RES)
	#define		RES_CHECK(RES,CHCK)						(RES = (CHCK) && (RES));	\
																	/*ASSERT(RES)					\*/
				/*RES_CHECK*/
	#define		RES_SET(RES,SET)							RES =	(RES_OK == SET)
	#define		RES_TRUE(RES)								RES_OK == (RES)
	#define		RES_FALSE(RES)								RES_OK != (RES)
	#define		RES_ALERT(RES)								assert(RES)

	#define		RES_RETURN(RES)							\
			/*RES_ALERT(RES_TRUE(RES));*/					\
			return(RES);										\
			/*end of RES_RETURN*/

	#define	RES_LOG_RETURN(RES)							\
			RES_ALERT(LogResult(FUNC_PATH_FULL,RES));	\
			return(RES);										\
			/*RES_LOG_RETURN*/
	#define		BREAK_RES_FAILE(RES)						\
			if (true != (RES)){								\
					break;										\
			}														\
		/*BREAK_RES_FAILE*/
#endif	//!FW_RESULT_HPP