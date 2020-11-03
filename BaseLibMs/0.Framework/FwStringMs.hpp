#ifndef FW_STRING_MS_HPP
#define	FW_STRING_MS_HPP
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





	/***********************************************************************\
	*																								*
	*											Include Files									*
	*																								*
	\***********************************************************************/
	//#include	HDR_STDAFX







	/***********************************************************************\
	*																								*
	*										s t r i n g											*
	*																								*
	\***********************************************************************/
	#define	CHAR_ARR_REF(ARR)					char ARR[]
	#define	CHAR_ARR_PRM(ARR)					const char ARR[]





	/***********************************************************************\
	*																								*
	*										String Macros										*
	*																								*
	\***********************************************************************/
	#define	STR_EMPTY						""
	#define	STR_OK							"Ok"
	#define	STR_ERR							"Err"
	#define	STR_RES_ERR						"Error"
	#define	STR_RESULT						"Result"
	#define	STR_SPACE						" "
	#define	STR_EMPTY						""
	#define	STR_MINUS						"-"
	#define	STR_HEX							"0x"

	#define	STRING							CString
	#define	STR_PBUFF(STR)					((char*)((LPCSTR)STR))


	#define	STR_DECLR(STR)					STRING	STR = STR_EMPTY
	#define	STR_DECLR_REF(STR)			STRING&	STR
	#define	STR_DECLR_INIT(STR,INIT)	STRING	STR = INIT
	#define	STR_INIT(STR)					STR	= STR_EMPTY
	#define	STR_CLEAR(STR)					STR	= STR_EMPTY
	#define	STR_IS_EMPTY(STR)				(STR	== STR_EMPTY)
	#define	STR_NOT_EMPTY(STR)			(STR	!= STR_EMPTY)

	#define	STR_SET(STR,SET)				\
					STR	= SET;				\
					ASSERT(STR != _T(""));	\
					/*STR_SET*/

	#define	STR_RESET(STR,SET)			STR = SET;
	#define	STR_ADD(STR,ADD)				STR += ADD
	#define	STR_ADD_CHAR(STR,ADD)		STR += ADD
	#define	STR_CMP(STR,CMP)				(STR == CMP)
	#define	STR_CMP_NOT(STR,CMP)			!(STR == CMP)
	#define	STR_RETURN(STR)				return(STR);

	#define	STR_NOT_FOUND								-1
	#define	STR_FIND(STR, FIND)						\
		(STR_NOT_FOUND != STR.Find(FIND,0x00))		\
		/*STR_FIND*/
	#define	STR_FIND_INDEX(STR, FIND, INDEX)		\
				STR.Find(FIND, INDEX)					\
				/*STR_FIND*/

	#define	STR_RFIND(STR,FIND)						\
				STR.ReverseFind(FIND)					\
				/*STR_RFIND*/
	#define	STR_RFIND_INDEX(STR,FIND,INDEX)		\
				STR.rfind(FIND,INDEX)					\
				/*STR_RFIND_INDEX*/





	#define		STR_LEN_MAX						1000
	#define		STR_LEN(STR)						\
		STR.GetLength()								\
		/*STR_LEN*/

	#define	STR_UPPER(STR)																\
					std::transform(STR.begin(),STR.end(),STR.begin(), ::toupper)	\
					/*STR_UPPER*/

	#define	STR_FORMAT(STR, FORMAT, NUM)		\
					STR.Format(FORMAT,NUM)			\
					/*STR_FORMAT*/




	#define	STR_TO_HEX(STR, NUM)					\
			STR.Format("%x", NUM)					\
			/*STR_TO_HEX*/




	#define	STR_TO_DEC(STR, NUM)				\
				STR.Format("%d")					\
			/*STR_TO_DEC*/




	#define	STR_LEFT(STR, LEN)				\
				STR.Left(LEN)						\


	#define	STR_RIGHT(STR, LEN)				\
				STR.Right(LEN)						\


	#define	STR_SUBSTR(STR, INDX, LEN)		\
				STR.Mid(INDX, LEN)				\
				/*STR_SUBSTR*/
	#define	STR_DELETE(STR, INDX, LEN)		\
				STR.Delete(INDX, LEN)			\
				/*STR_DELETE*/
	#define	PSTR_DELETE(_PSTR, INDX, LEN)	\
				_PSTR->Delete(INDX, LEN)		\
				/*STR_LEN*/
	#define		STR_REMOVE(STR, _CHAR)		\
				STR.Remove(_CHAR)					\
				/*STR.erase(std::remove(STR.begin(), STR.end(), CHAR), STR.end())*/	\
				/*STR_LEN*/
#endif	/*!FW_STRING_MS_HPP*/