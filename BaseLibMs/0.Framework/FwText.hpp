/********************************************************************\
*																							*
*									Text String											*
*																							*
\********************************************************************/
#ifndef FW_TEXT_STR_HPP
#define FW_TEXT_STR_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"




	/********************************************************************\
	*																							*
	*										Include files									*
	*																							*
	\********************************************************************/
	#include	HDR_FW_RESULT
//	#include	HDR_FW_STRING
	#include	HDR_FW_BASE_TYPES
	#include	HDR_FW_ENUMS











	//template	<class NAME_CODE>
	//STRING	EnumName(NAME_CODE name_code,  NAME_CODE from, NAME_CODE to, const char* Names[])
	//{
	//	STRING	Name	= "";
	//	if(true == EnumChk(name_code, from, to)){
	//			Name = Names[name_code];
	//	}
	//	else{
	//			Name = ENUM_NAME_UNDEF;
	//	}
	//	return(Name);
	//}
	//#define	ENUM_NAME(ENUM, CODE)										\
	//		EnumName(CODE,(ENUM)0x00,ENUM##_COUNT,ENUM##_Names)	\
	//		/*ENUM_NAME*/

	//template	<class NAME_CODE>
	//NAME_CODE EnumCode(NAME_CODE from, NAME_CODE to, STRING Name, const char* Names[])
	//{
	//	NAME_CODE Code	= to;

	//	for(FW_INT i = from; i<= to ;i++){
	//		if(Name == Names[i]){
	//			Code	= (NAME_CODE)i;
	//			break;
	//		}
	//	}
	//	return(Code);
	//}

	//#define	ENUM_CODE(ENUM, NAME)											\
	//			EnumCode((ENUM)0x00, ENUM##_UNDEF, NAME, ENUM##_Names)	\
	//			/*ENUM_CODE*/





	/********************************************************************\
	*																							*
	*											Definitions									*
	*																							*
	\********************************************************************/
	#define		TAG_EMPTY				""

	#define		TAG_STR_END				"#"
	#define		TAG_TXT_END				"\n"
	#define		TAG_LINE_END			"\n\r"
	#define		TAG_FILE_SEP			" "
	#define		TAG_PRM_OPEN			"("
	#define		TAG_PRM_CLOSE			")"

	#define		TAG_SPACE				" "
	#define		TAG_POINTER				"->"
	#define		TAG_COMMENT				"//"

	#define		TAG_FRM_END				"."
	#define		TAG_SEG_END				":"
	#define		TAG_PAG_END				";"
	#define		TAG_ITM_END				","
	#define		TAG_LNK_END				">"


	#define	STR_TAG_FIELDS	\
		STR_TAG_FRM			\
		,STR_TAG_SEG		\
		,STR_TAG_PAG		\
		,STR_TAG_ITM		\
		,STR_TAG_LNK		\
		/*TAG_FIELDS*/

	#define	STR_TAG_NAMES	\
		TAG_FRM_END			\
		,TAG_SEG_END		\
		,TAG_PAG_END		\
		,TAG_ITM_END		\
		,TAG_LNK_END		\
		/*STR_TAG_NAMES*/
	ENUM_DEFINE(STR_TAG, STR_TAG_FIELDS);





	/********************************************************************\
	*																							*
	*											Class											*
	*																							*
	\********************************************************************/
	typedef struct _SRange 
	{
		FW_INT	from;
		FW_INT	to;
		FW_INT	length;
	}SRange;

	class  CMicString 
	{
		//	String Data containers.
		//private:	STRING	my_item;				//	Item in page - ends with ','.
		//private:	STRING	my_page;				//	Page in a segment - ends with ';'.
		//private:	STRING	my_segment;			//	Segment in formation - ends with ':'.
		//private:	STRING	my_formation;		//	Formation in a string - ends with '.'.
		//private:	STRING	my_description;	//	Description is a string containing a whole script.

		private:	FW_RESULT	Init(void);
		public:	FW_RESULT	Clear(void);
		public:				CMicString();
//		public:				CMicString(STRING description);
		public:	virtual	~CMicString();

		public:	bool					IsNum(STRING string);
		public:	static	STRING	GetNum(unsigned char num, bool Hex);
		public:	static	STRING	GetNum(FW_INT num, bool Hex);
		public:	static	STRING	GetNum(FW_LONG num, bool Hex);
		public:	static	FW_LONG	GetNum(STRING string);
		public:	static	FW_INT	GetNum(STRING	page, STRING sep, FW_INT at_index);
		public:	static	FW_INT	GetNum(STRING	page, FW_INT at_index);
		//public:	FW_INT				GetNum(FW_INT at_index);
		public:	static	STRING	GetArr(FW_CHAR* pArr, FW_LONG length, bool hex);

		//	Translate numeric to string.
		public:	static	bool		FindRight(STRING search_str, STRING sub_str);

		//	Translate numeric to string.
		public:	static	STRING	TokenRightGet(STRING search_str, STRING tkstart);
		public:	static	STRING	TokenRangeGet(STRING search_str, STRING tkstart, STRING tkend);
		public:	static	STRING	TokenRangeRmv(STRING search_str, STRING tkstart, STRING tkend);
		public:	static	STRING	TokenLeftGet(STRING search_str, STRING tkend);

		//	Text Containers.
		public:	static	FW_INT	GetTextCount(STRING str, STRING text);
		public:	static	FW_INT	GetTextIndex(STRING str, STRING text,FW_INT count);
		public:	static	STRING	GetTextItem(STRING page, STRING sep, FW_INT index);
		public:	static	STRING	GetTextItem(STRING page, FW_INT index);
		public:	static	STRING	TextRangeGet(STRING str, unsigned char tag_start, unsigned char tag_end, FW_INT index);
		public:	static	STRING	TextRangeRmv(STRING str, unsigned char tag_start, unsigned char tag_end, FW_INT index);

		//	Basic search and bordered string manipulations.
		public:	static	FW_INT	BorderFind(STRING description, STR_TAG tag, FW_INT from);
		public:	static	FW_INT	BorderFind(STRING description, STRING tag, FW_INT from);
		public:	static	SRange	RangeFind(STRING description, STR_TAG tag, FW_INT index);
		public:	static	STRING	RangeGet(STRING description, STR_TAG tag, FW_INT index);
		public:	static	STRING	RangeRemove(STRING& pDescription, STR_TAG tag, FW_INT index);


		//	Get string fro structural tag defined script.
		public:	static	STRING	GetLink(STRING str, FW_INT index);

		//public:	FW_RESULT	LetPage(STRING	page);
		//public:	STRING	GetPage(void);
		public:	static	FW_RESULT	AddItem(STRING& page, STRING item);
//		public:	STRING	GetItem(FW_INT index);
		public:	static	STRING	GetItem(STRING page, FW_INT index);

		//public:	FW_RESULT	LetSegment(STRING	segment);
		//public:	STRING	GetSegment(void);
		public:	static	FW_RESULT	AddPage(STRING& segment, STRING page);
		public:	static	STRING	GetPage(STRING	segment, FW_INT index);
//		public:	STRING	GetPage(STRING segment, FW_INT index);
		public:	static	STRING	PageRemove(STRING& pDescription, FW_INT index);

		public:	static STRING	GetSegment(STRING	formation, FW_INT index);
//		public:	STRING	GetSegment(STRING formation, FW_INT index);
//		public:	FW_RESULT	FormationLet(STRING	formation);
		public:	static	STRING	FormationAdd(STRING& description, STRING	formation);
		public:	static	STRING	FormationGet(STRING description, FW_INT index);
		public:	static	STRING	FormationRemove(STRING& pDescription, FW_INT index);

		public:	static	STRING	ParametersGet(STRING	description);
		public:	static	STRING	ParametersRemove(STRING& description);

		public:	static	STRING	TextGet(STRING description);
		public:	static	STRING	TextRemove(STRING& description);

		//public:	FW_RESULT	DescriptionLet(STRING description);
		//public:	STRING	DescriptionGet(void);
	};




	STRING	NumToStr(long long num, bool Hex);
	unsigned long	GetNum(STRING str_num);
//	unsigned long	GetNum(STRING str_num);
	STRING	GetTextRecord(STRING str, unsigned char tag, FW_INT index);

#endif	// FW_TET_STR_H

