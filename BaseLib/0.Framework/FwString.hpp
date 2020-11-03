#ifndef FW_STRING_HPP
#define	FW_STRING_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





	/***********************************************************************\
	*																								*
	*											Include Files									*
	*																								*
	\***********************************************************************/
	#include <string.h>
	#include	<sstream>
	#include <algorithm>





	/***********************************************************************\
	*																								*
	*										s t r i n g											*
	*																								*
	\***********************************************************************/
	#define	CHAR_ARR_REF(ARR)					char ARR[]
	#define	CHAR_ARR_PRM(ARR)					const char ARR[]





	/***********************************************************************\
	*																								*
	*									String Macros											*
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

	#define	STRING							std::string
	#define	STR_PBUFF(STR)					STR.c_str()
	//#define	LPCTSTR							const char*

	#define	STR_DECLR(STR)					STRING	STR = STR_EMPTY
	#define	STR_DECLR_REF(STR)			STRING&	STR
	#define	STR_DECLR_INIT(STR,INIT)   STRING	STR = INIT
	#define	STR_INIT(STR)					STR	= STR_EMPTY
	#define	STR_CLEAR(STR)					STR	= STR_EMPTY
	#define	STR_IS_EMPTY(STR)				(STR == STR_EMPTY)
	#define	STR_NOT_EMPTY(STR)         (STR != STR_EMPTY)

	#define	STR_SET(STR,SET)					\
					STR	= SET;					\
					assert(STR != STR_EMPTY);	\
					/*STR_SET*/

	#define	STR_RESET(STR,SET)			STR = SET;
	#define	STR_ADD(STR,ADD)				STR.append(STRING(ADD))
	#define	STR_ADD_CHAR(STR,ADD)		STR.append(1, ADD)
	#define	STR_CMP(STR,CMP)				(STR.compare(CMP) == 0x00)
	#define	STR_CMP_NOT(STR,CMP)			!(STR == CMP)
	#define	STR_RETURN(STR)				return(STR);

	#define	STR_NOT_FOUND							std::string::npos
	#define	STR_FIND(STR, FIND)							\
				(STR_NOT_FOUND != STR.find(FIND,0x00))	\
				/*STR_FIND*/
	#define	STR_FIND_INDEX(STR, FIND, INDEX)			\
				STR.find(FIND, INDEX)						\
				/*STR_FIND*/

	#define	STR_RFIND(STR,FIND)						\
				STR.rfind(FIND,0x00)						\
				/*STR_RFIND*/
	#define	STR_RFIND_INDEX(STR,FIND,INDEX)		\
				STR.rfind(FIND,INDEX)					\
				/*STR_FIND*/
	#define	STR_FIND_RIGHT(STR,FIND)																		\
				(0x00 == STR.find(FIND.c_str(), STR_LEN(STR) - STR_LEN(FIND), STR_LEN(FIND)))	\
				/*STR_RFIND_INDEX*/


	#define	STR_LEN_MAX									128
	#define	STR_LEN(STR)								\
				STR.length()								\
				/*STR_LEN*/

	#define	STR_UPPER(STR)																\
					std::transform(STR.begin(),STR.end(),STR.begin(), ::toupper)	\
					/*STR_UPPER*/

	#define	STR_FORMAT(STR, FORMAT, NUM){				\
				char	buff[STR_LEN_MAX];					\
				(0x00 != sprintf(buff, FORMAT, NUM));	\
				STR = buff;										\
			}														\
			/*STR_FORMAT*/

	#define	STR_TO_HEX(STR, NUM){						\
				std::ostringstream strm;					\
				strm << STR_HEX << std::hex << NUM;		\
				STR = strm.str();								\
			}														\
			/*STR_TO_HEX*/

	#define	STR_TO_DEC(STR, NUM){				\
				std::ostringstream strm;			\
				strm << std::dec << NUM;			\
				STR = strm.str();						\
			}												\
			/*STR_TO_HEX*/

	#define	STR_LEFT(STR, LEN)					\
			STR.substr(0, LEN)						\
				/*STR_LEN*/

	#define	STR_RIGHT(STR, LEN)					\
			STR.substr(STR_LEN(STR)-LEN, LEN)	\
			/*STR_LEN*/

	#define	STR_SUBSTR(STR, INDX, LEN)			\
				STR.substr(INDX, LEN)				\
				/*STR_SUBSTR*/
	#define	STR_DELETE(STR, INDX, LEN)			\
				STR.erase(INDX, LEN)					\
				/*STR_DELETE*/
	#define	PSTR_DELETE(PSTR, INDX, LEN)		\
				PSTR->erase(INDX, LEN)				\
				/*STR_LEN*/
	#define		STR_REMOVE(STR, CHAR)					\
				std::remove(STR.begin(), STR.end(), CHAR)	\
				/*STR.erase(std::remove(STR.begin(), STR.end(), CHAR), STR.end())*/	\
				/*STR_LEN*/


	#define STR_LST_DCLR(LIST)						\
				std::vector<string> LIST			\
				/*OP_REP_DCLR*/

	#define STR_LST_SIZE(LIST)						\
				LIST.size()								\
				/*OP_REP_DCLR*/

	#define STR_LST_GET(RES, LIST, INDX, STR) \
			if(INDX < LIST.size())					\
			{ STR = LIST[INDX];   }					\
			else    RES_FAILE(RES);					\
			/*OP_PRMS_GET*/

	#define STR_LST_PUSH(LIST, STR)	LIST.push_back(STR);

	#define STR_LST_NEXT(LIST, STR)				\
				STR_SET(STR, LIST.back());			\
				LIST.pop_back()						\
				/*STR_LST_NEXT*/

		//#include		<string.h>
		//#define		STRING							char
		//#define		STR_SIZE_MAX					1024
		//#define		STR_DECLR(STR)					STRING	STR[STR_SIZE_MAX] = {0x00}


		//#define		STR_DECLR_INIT(STR,INIT)   STRING	STR[STR_SIZE_MAX]  = INIT
		//#define		STR_SET(STR,SET)				StrSet(STR, SET)

#endif // !FW_STRING_HPP
