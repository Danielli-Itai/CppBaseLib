#ifndef FW_RESULT_MS_HPP
#define	FW_RESULT_MS_HPP
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"






















	/***********************************************************************\
	*																								*
	*										Result Macros										*
	*																								*
	\***********************************************************************/









	#define		RES_OK							true
	#define		RES_ERR							false

	#define		RETURN(OBJ)								return(OBJ)
	#define		FW_RESULT									bool
	#define		RES_DECLR(RES)					bool	RES = true;
	#define		RES_INIT(RES)							RES = true;
	#define		RES_DECLR_INIT(RES,INIT)	bool	RES = (INIT)
	#define		RES_FAILE(RES)							RES = false;
	#define		RES_SUCCESS(RES)						RES = true;
	//#define		RES_CHECK(RES,CHCK)					RES = CHCK && (RES)
	#define		RES_CHECK(RES,CHCK)					(RES = CHCK && (RES))/*ASSERT(RES = CHCK && (RES))*/
	#define		RES_SET(RES,SET)						RES =	(TRUE == SET)
	#define		RES_TRUE(RES)							true == (RES)
	#define		RES_FALSE(RES)							true != (RES)
	#define		RES_ALERT(RES)							ASSERT(RES)
	#define		RES_RETURN(RES)	\
		/*ASSERT(RES_TRUE(RES));*/		\
		return(RES);					\
		/*end of RES_RETURN*/
	#define	RES_LOG_RETURN(RES)							\
		RES_ALERT(LogResult(FUNC_PATH_FULL,RES));		\
		return(RES);											\
		/*RES_LOG_RETURN*/
	#define		BREAK_RES_FAILE(RES)	\
	{											\
		if (true != (RES)){				\
			break;							\
		}										\
	}											\
	/*BREAK_RES_FAILE*/
#endif // !FW_RESULT_MS_HPP