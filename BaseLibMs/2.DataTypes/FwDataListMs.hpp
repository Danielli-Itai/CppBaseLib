/***********************************************************************\
*																								*
*									D a t a   H a n d l e r								*
*																								*
\***********************************************************************/
#ifndef AFX_DATA_HANDLER_H
#define AFX_DATA_HANDLER_H
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"






	/***********************************************************************\
	*																								*
	*										Include Files										*
	*																								*
	\***********************************************************************/
	#include <afxtempl.h>
	#include HDR_FW_BUFFER
	#include HDR_FW_DATA





	/***********************************************************************\
	*																								*
	*										Definitions											*
	*																								*
	\***********************************************************************/
	//	Error names.
	#define	DATA_ERR_SEPARATOR					" "
	#define	DATA_ITEMS	0x30

	#define	FW_LIST_DECLR(TYPE, NAME)	CList	<TYPE, TYPE> NAME

	#define	LIST_COUNT(NAME)				NAME.GetCount()
	#define	FW_LIST_ADD_TAIL(NAME, ADD)	NAME.AddTail(ADD)




/***********************************************************************\
*																								*
*											Class												*
*																								*
\***********************************************************************/
#ifdef	OLD_CODE
	class CMicDataList:	public CFwBuffer
#else
	class CMicDataList:	public CFwBuffer//, protected CMicString 
#endif
{
	public:	CMicDataList();
	public:	virtual ~CMicDataList();

	//	Errors.
	bool			my_error;
	STRING		my_errors;
	public:		bool		ErrorExist(void)		{	return(my_error);	}
	protected:	FW_RESULT	ErrorAdd(STRING error);
	public:		STRING	Errors(void);
	public:		FW_RESULT	ErrorsClear(void);

	private:		//CList		<CMicData*,CMicData*>	my_data_items;
	private:		FW_LIST_DECLR(CMicData*, my_data_items);
	public:		int		Count();

	//	Methods.
	public:		FW_RESULT	AddItem(STRING	dscrp);
	public:		FW_RESULT	AddItem(CMicData*	pItem);
	public:		FW_RESULT	AddItem(STRING title, DATA_FORMAT format, int size, const unsigned char buffer[]);

	//	Contents.
	public:		int		ContentsLength(void);

	//	Buffer.
	public:	CFwBuffer*	BufferBuild(void);		//	Build the buffer according to the contents settings.
	public:	FW_RESULT		BufferSet(CFwBuffer* pBuffer  = NULL);	//	Set buffer as contents.
	public:	CFwBuffer*	BufferGet(void);			//	Return a buffer containing the data according to formation settings.

	//	File connection.
	private:	bool			my_file_cnct;
	public:	FW_RESULT		FileIsConnect(void);
	private:	FW_RESULT		FileChkConnect(CMicData*	pData);


	private:	STRING		my_file_titl;
	private:	STRING		my_file_data;
	public:	STRING		FileTitleGet(void);
	public:	STRING		FileDataGet(void);

	//	Operators.
	public:	bool				DataChk(void);				//	Check if the buffer fits the contents settings.
	public:	CMicData*		operator[](int index);		//	Return a data item from the contents array.
	public:	CMicDataList*	operator = (CMicDataList*	pDataHndlr);
	public:	bool				operator == (CMicDataList*	pDataHndlr);

	public:	FW_RESULT			DescriptionLet(STRING description);
	public:	STRING			DescriptionGet(bool hex);
	public:	STRING			DescriptionGet(bool hex, bool title);
};
#endif	// AFX_DATA_HANDLER_H

