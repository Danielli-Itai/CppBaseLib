#ifndef FW_ENUMS_HPP
#define	FW_ENUMS_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





	#include	HDR_FW_BASE_TYPES
	#include	HDR_FW_STRING
	#include	HDR_FW_RESULT



	/********************************************************************\
	*																							*
	*                           E n u m e r a t o r                      *
	*																							*
	\********************************************************************/
	#ifdef  __cplusplus_cli
		#define	ENUM_DEFINE(ENUM,FIELDS)		\
		public enum class ENUM:int					\
		{													\
					FIELDS									\
			,	ENUM##_UNDEF							\
			,	ENUM##_COUNT = ENUM##_UNDEF		\
		};													\
		/*ENUM_DEFINE*/

		#define	ENUM_DEFINE_EXT(ENUM, FIELDS, EXTNDS)	\
		public enum class ENUM:int					\
		{													\
					EXTNDS									\
			,	FIELDS									\
			,	ENUM##_UNDEF							\
			,	ENUM##_COUNT = ENUM##_UNDEF		\
		};													\
		/*ENUM_DEFINE_EXT*/


		#define ENUM_DECLR(ENUM,VAR)				\
		ENUM VAR = ENUM::ENUM##_UNDEF				\
		/*ENUM_DCLR*/

		#define ENUM_INIT(ENUM,VAR)				\
		VAR = ENUM::ENUM##_UNDEF					\
		/*ENUM_INIT*/

		#define ENUM_DECLR_INIT(ENUM,VAR,INIT)	\
		ENUM VAR = ENUM::INIT						\
		/*ENUM_DECLR_INIT*/

		#define ENUM_NAME_INIT(ENUM,VAR)			\
		VAR = ENUM_NAME_UNDEF						\
		/*ENUM_INIT*/
	#endif	/*__cplusplus*/
#endif	// !FW_ENUMS_HPP

