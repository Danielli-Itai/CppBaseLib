#ifndef FW_ENUMS_HPP
#define	FW_ENUMS_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"




	/********************************************************************\
	*																							*
	*                           E n u m e r a t o r                      *
	*																							*
	\********************************************************************/
	#include	HDR_FW_BASE_TYPES
	#include	HDR_FW_STRING
	#include	HDR_FW_RESULT





	/********************************************************************\
	*																							*
	*                           E n u m e r a t o r                      *
	*																							*
	\********************************************************************/
	#define	ENUM_UNDEF(ENUM)							\
						ENUM##_UNDEF						\
						/*ENUM_UNDEF*/
	#define	ENUM_DEFINED(ENUM, VAL)					\
						(ENUM_UNDEF(ENUM) != VAL)		\
						/*ENUM_UNDEF*/
	#define	ENUM_UNDEFINED(ENUM, VAL)				\
						(ENUM_UNDEF(ENUM) == VAL)		\
						/*ENUM_UNDEF*/

	#define	ENUM_INITIAL(ENUM, VAL)					\
						(ENUM_UNDEF(ENUM) == VAL)		\
						/*ENUM_INITIAL*/
	#define	ENUM_INITIAL_NOT(ENUM, VAL)			\
						(ENUM_UNDEF(ENUM) != VAL)		\
						/*ENUM_INITIAL_NOT*/

	#define	ENUM_NAME_UNDEF	"Unknown"


	#define ENUM_DECLR(ENUM,VAR)						\
					ENUM VAR = ENUM##_UNDEF				\
					/*ENUM_DCLR*/
	#define ENUM_INIT(ENUM,VAR)						\
					VAR = ENUM##_UNDEF					\
					/*ENUM_INIT*/
	#define ENUM_DECLR_INIT(ENUM,VAR,INIT)			\
					ENUM VAR = INIT						\
					/*ENUM_DECLR_INIT*/
	#define ENUM_NAME_INIT(ENUM,VAR)					\
					VAR = ENUM_NAME_UNDEF				\
					/*ENUM_INIT*/


	#define	ENUM_CMP(ENUM, VAR)					\
				(ENUM == VAR)							\
				/*ENUM_COMP*/
	#define	ENUM_CMP_NOT(ENUM, VAR)				\
				(ENUM != VAR)							\
				/*ENUM_CMP_NOT*/
	#define	ENUM_CLR(ENUM, VAR)					\
				VAR = ENUM_UNDEF(ENUM)				\
				/*ENUM_CLR*/
	#define	ENUM_CLR_CHK(ENUM, VAR)				\
				(ENUM_UNDEF(ENUM) == VAR)			\
				/*ENUM_CLR_CHK*/

	#define	ENUM_DEFINE(ENUM,FIELDS)			\
			typedef enum _##ENUM						\
			{		FIELDS								\
				,	ENUM##_UNDEF						\
				,	ENUM##_COUNT = ENUM##_UNDEF	\
			}ENUM											\
			/*ENUM_DEFINE*/
	
	#define	ENUM_DEFINE_EXT(ENUM, FIELDS, EXTNDS)	\
			typedef enum _##ENUM								\
			{														\
					EXTNDS										\
				,	FIELDS										\
				,	ENUM##_UNDEF								\
				,	ENUM##_COUNT = ENUM##_UNDEF			\
			}ENUM													\
			/*ENUM_DEFINE_EXT*/


	/********************************************************************\
	*																							*
	*                           E n u m e r a t o r                      *
	*																							*
	\********************************************************************/
	#ifdef __cplusplus
		template	<class ENUM_CODE>
		bool	EnumChk(ENUM_CODE enum_code,ENUM_CODE from,ENUM_CODE to)
		{
			RETURN((from <= enum_code) && (enum_code<= to));
		}
		#define	ENUM_CHK(ENUM,CODE)						\
					EnumChk(CODE,(ENUM)0x00,ENUM##_COUNT)	\
		/*ENUM_CHK*/

		template	<class ENUM_CODE>
		bool		EnumSet(ENUM_CODE& var, ENUM_CODE code,ENUM_CODE from, ENUM_CODE to, ENUM_CODE undef)
		{
			bool result = true;

			if(EnumChk(code,from,to)){
					var = code;
			}
			else{
					var = undef;
					result = false;
			}
			return(result);
		}
		#define ENUM_SET(ENUM, VAR, CODE)			\
				EnumSet(VAR, (ENUM)CODE, (ENUM)0x00,ENUM##_COUNT,ENUM##_UNDEF)	\
					/*ENUM_SET*/


	#define	ENUM_NAMES_CREATE(ENUM,NAMES)						\
			const char*	ENUM##_Names[ENUM##_COUNT + 1] =		\
			{		NAMES													\
				,	ENUM_NAME_UNDEF									\
			}																\
			/*ENUM_NAMES_CREATE*/

		#define	ENUM_NAMES(ENUM)										\
					const char*	ENUM##_Names[]							\
					/*ENUM_NAMES*/

		#define	ENUM_NAMES_CREATE_EXT(ENUM,NAMES,EXTND)		\
					const char*	ENUM##_Names[ENUM##_COUNT + 1] =	\
					{	 NAMES, EXTND, ENUM_NAME_UNDEF	}				\
					/*ENUM_NAMES_CREATE_EXT*/

		#define	ENUM_NAMES_EXTERN(ENUM)										\
					extern	const char*	ENUM##_Names[ENUM##_COUNT + 1]	\
					/*ENUM_NAMES_EXTERN*/

		template	<class NAME_CODE>
		STRING	EnumName(NAME_CODE name_code,  NAME_CODE from, NAME_CODE to, const char* Names[])
		{
			STRING	Name	= "";

			if(true == EnumChk(name_code, from, to)){
				Name = Names[name_code];
			}
			else{
				Name = ENUM_NAME_UNDEF;
			}
			return(Name);
		}
		#define	ENUM_NAME(ENUM, CODE)									\
			EnumName(CODE,(ENUM)0x00,ENUM##_COUNT,ENUM##_Names)	\
			/*ENUM_NAME*/
		template	<class NAME_CODE>
		NAME_CODE EnumCode(NAME_CODE from, NAME_CODE to, STRING Name, const char* Names[])
		{
			NAME_CODE Code	= from;

			for(int i = from; i<=to ;i++){
				if(Name == Names[i])
				{
					Code	= (NAME_CODE)i;
					break;
				}
			}
			return(Code);
		}
		#define	ENUM_CODE(ENUM, NAME)	\
			EnumCode((ENUM)0x00, ENUM##_COUNT, NAME, ENUM##_Names)	\
			/*ENUM_NAME*/


		#define	ENUM_TABLE_CREATE(CLS,ENUM,UNDEF,FIELDS)					\
			static const	CLS ENUM##_Values[ENUM##_COUNT+1] =				\
					{	FIELDS, UNDEF	}													\
					/*ENUM_TABLE_CREATE*/
		#define	ENUM_TABLE_CREATE_EXT(CLS,ENUM,UNDEF,EXTND,FIELDS)		\
					const	CLS	ENUM##_Values[ENUM##_COUNT+1] =				\
					{	EXTND, FIELDS, UNDEF	}											\
					/*ENUM_NAMES_CREATE*/

		#define	ENUM_TABLE_EXTERN(CLS,ENUM)									\
					extern	const CLS	ENUM##_Values[ENUM##_COUNT+1];		\
					/*ENUM_TABLE_EXTERN*/

		template	<class VAL_CLS, class VAL_CODE >
		VAL_CLS	EnumVal(VAL_CODE name_code,  VAL_CODE from, VAL_CODE to, const VAL_CLS* Values)
		{
			VAL_CLS	val;

			if(true == EnumChk(name_code, from, to)){
					val = Values[name_code];
			}
			else{
					val = Values[from];
			}
			return(val);
		}
		#define	ENUM_VAL(ENUM, CODE)											\
					EnumVal(CODE,(ENUM)0x00,ENUM##_COUNT,ENUM##_Values)	\
					/*ENUM_VAL*/


		#define ENUM_FLAG_SET(FLAGS,ENUM)								\
					FLAGS.all |= (0x01 << (ENUM - 1))					\
					/*ENUM_FLAG_SET*/
		#define ENUM_FLAG_CLR(FLAGS,ENUM)								\
					FLAGS.all &= ~(0x01 << (ENUM - 1))					\
					/*ENUM_FLAG_CLR*/
		#define ENUM_FLAG_CHK(FLAGS,ENUM)								\
					((FLAGS.all & (0x01 << (ENUM - 1))) != 0x00)	\
					/*ENUM_FLAG_CHK*/

		#define	ENUM_FOR_LOOP(ENUM, VAR)							\
					for(	ENUM VAR = ENUM##_UNDEF;					\
						VAR < ENUM##_COUNT;								\
						VAR = (ENUM)(VAR + 1)							\
					)															\
					/*ENUM_LOOP*/

		typedef void (*ENUM_CB_TYPE)(void);
		#define	ENUM_CB_VECT(NAME, ENUM)	NAME##ENUM##_CB_ARR
		#define	ENUM_CB_FUNC(NAME)			void NAME(void)

		#define	ENUM_CB_VECT_CREATE(NAME, ENUM)								\
					ENUM_CB_TYPE ENUM_CB_VECT(NAME, ENUM)[ENUM##_COUNT] =	\
					{ NULL	};																\
					/*ENUM_CB_VECT*/

		#define	ENUM_CB_VECT_EXTERN(ENUM)										\
					extern	ENUM_CB_TYPE ENUM_CB_VECT(ENUM)[ENUM##_COUNT]	\
					/*ENUM_NAMES_EXTERN*/
	#endif	/*__cplusplus*/
#endif	// !FW_ENUMS_HPP

