/***********************************************************************\
*																								*
*									D a t a   H a n d l e r								*
*																								*
\***********************************************************************/
#ifndef FW_DATALIST_HPP
#define FW_DATALIST_HPP
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"




	/***********************************************************************\
	*																								*
	*										Include Files										*
	*																								*
	\***********************************************************************/
	//#include <afxtempl.h>
	#include	<list>
	#include	<vector>
	#include HDR_FW_BUFFER
	#include HDR_FW_DATA





	/***********************************************************************\
	*																								*
	*										Definitions											*
	*																								*
	\***********************************************************************/
	//	Error names.
	#define	DATA_ERR_SEPARATOR		" "
	#define	DATA_ITEMS					0x30
	#define	POSITION						FW_UINT



	#define	FW_LIST_DECLR(TYPE,NAME)		std::list	<TYPE>	NAME
	#define	FW_LIST_ADD_TAIL(NAME, ADD)	NAME.AddTail(ADD)
	#define	FW_LIST_COUNT(NAME)				NAME.size()
	#define	FW_LIST_GET_AT(NAME, INDEX)	FW_LIST_ITR_DATA(std::next(NAME.begin(), INDEX))

	#define	FW_LIST_ITR_DATA(ITER)			(*ITER)
	#define	FW_LIST_LOOP(TYPE, ITER, NAME)															\
		for(std::list<TYPE>::iterator ITER=NAME.begin(); ITER!=NAME##.end(); ++##ITER)	\
		/*LIST_FOR_LOOP*/


	#define	FW_VECT_DECLR(TYPE,NAME)		std::vector<TYPE> NAME
	#define	FW_VECT_ADD_TAIL(NAME, ADD)	NAME.push_back(ADD)
	#define	FW_VECT_SIZE(NAME)				NAME.size()
	#define	FW_VECT_GET_AT(NAME,INDEX)		NAME[INDEX]

	#define	FW_VECT_ITR_DATA(ITER)			(*ITER)
	#define	FW_VECT_ITR_DELETE(NAME, ITER)	NAME.erase(ITER)
	#define	FW_VECT_LOOP(TYPE, ITER, NAME)															\
		for(std::vector<TYPE>::iterator ITER=NAME.begin(); ITER!=NAME##.end(); ++##ITER)	\
		/*LIST_FOR_LOOP*/




	/***********************************************************************\
	*																								*
	*											Class												*
	*																								*
	\***********************************************************************/
	class CMicDataList:	public CFwBuffer
	{
		protected:	FW_RESULT	Clear();
		public:					CMicDataList();
		public:		virtual	~CMicDataList();

		//	Errors.
		bool			my_error;
		STRING		my_errors;
		public:		bool			ErrorExist(void)		{	return(my_error);	}
		protected:	FW_RESULT	ErrorAdd(STRING error);
		public:		STRING		Errors(void);
		public:		FW_RESULT	ErrorsClear(void);

		//		private:		CList		<CMicData*,CMicData*>	my_data_items;
		private:		FW_LIST_DECLR(CMicData*, my_data_items);
		public:		FW_INT		Count();

		//	Methods.
		public:		FW_RESULT	AddItem(STRING	dscrp);
		public:		FW_RESULT	AddItem(CMicData*	pItem);
		public:		FW_RESULT	AddItem(STRING title, DATA_FORMAT format, FW_INT size, const char buffer[]);

		//	Contents.
		public:		FW_INT		ContentsLength(void);

		//	Buffer.
		public:	CFwBuffer*		BufferBuild(void);		//	Build the buffer according to the contents settings.
		public:	FW_RESULT			BufferSet(CFwBuffer* pBuffer  = NULL);	//	Set buffer as contents.
		public:	CFwBuffer*		BufferGet(void);			//	Return a buffer containing the data according to formation settings.

		//	Operators.
		public:	bool				DataChk(void);				//	Check if the buffer fits the contents settings.
		public:	CMicData*		operator[](FW_INT index);		//	Return a data item from the contents array.
		public:	CMicDataList*	operator = (CMicDataList*	pDataHndlr);
		public:	bool				operator == (CMicDataList*	pDataHndlr);
		public:	FW_RESULT		DescriptionLet(STRING description);
		public:	STRING			DescriptionGet(bool hex, bool title);
	};
#endif	// FW_DATALIST_HPP

