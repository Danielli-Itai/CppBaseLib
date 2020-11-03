/********************************************************************\
*																							*
*									Text String											*
*																							*
\********************************************************************/
#ifndef FW_TEXT_STR_MS_HPP
#define FW_TEXT_STR_MS_HPP
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





	/********************************************************************\
	*																							*
	*										Include files									*
	*																							*
	\********************************************************************/
	#include	HDR_FW_STRING
	#include	HDR_FW_ENUMS


















































	/********************************************************************\
	*																							*
	*											Definitions									*
	*																							*
	\********************************************************************/
	#define		TAG_EMPTY		_T("")

	#define		TAG_STR_END		_T("#")
	#define		TAG_TXT_END		_T("\n")
	#define		TAG_TEXT_LINE_END	_T("\n\r")
	#define		TAG_FILE_SEP	_T(" ")
	#define		TAG_PRM_OPEN	_T("(")
	#define		TAG_PRM_CLOSE	_T(")")

	#define		TAG_SPACE		_T(" ")
	#define		TAG_POINTER		_T("->")
	#define		TAG_COMMENT		_T("//")

	#define		TAG_FRM_END		_T(".")
	#define		TAG_SEG_END		_T(":")
	#define		TAG_PAG_END		_T(";")
	#define		TAG_ITM_END		_T(",")
	#define		TAG_LNK_END		_T(">")


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

	class AFX_CLASS_EXPORT CMicString 
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

#endif	// FW_TEXT_STR_MS_HPP
