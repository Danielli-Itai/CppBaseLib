/********************************************************************\
*																							*
*								D a t a   H a n d l e r								*
*		Handles an array of data items which togather define a			*
*		block of information.														*
*			The class inherits from the Buffer handler						*
\********************************************************************/
#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"






/***********************************************************************\
*																								*
*										Include Files										*
*																								*
\***********************************************************************/
#include	HDR_FW_POINTERS
#include	HDR_FW_TEXT_STR
#include HDR_FW_DATA_LIST





/********************************************************************\
*																							*
*										Globals											*
*																							*
\********************************************************************/
#define	DATA_ITEM_UNEXP	"Unexpected"









/********************************************************************\
*																							*
*										S Y S T E M										*
*																							*
\********************************************************************/

//----------------------------------
//	Clear when loading.
CMicDataList::CMicDataList()
{
	RES_DECLR(result);
	PTR_DECLR(CMicData, pData);

	my_file_cnct	=	false;;
	STR_INIT(my_file_titl);
	STR_INIT(my_file_data);
	my_error		= false;

	STR_INIT(my_errors);
}

//	Clear before unloading.
CMicDataList::~CMicDataList()
{
	RES_DECLR(result);

	PTR_DECLR(CMicData,pData);
	for(int index = my_data_items.GetCount(); index >0x00; index--)
	{
		pData = my_data_items.RemoveHead();		//	Clear data item.

		if(PTR_NOT_NULL(pData)){
			RES_CHECK(result,pData->Clear());
			PTR_DESTROY(pData);
		}
		else{
			RES_FAILE(result);
		}
	}

	RES_CHECK(result,my_data_items.IsEmpty());
}










/********************************************************************\
*																							*
*									M E T H O D S										*
*																							*
\********************************************************************/

int	CMicDataList::Count()
{
	return(LIST_COUNT(my_data_items));		
}

FW_RESULT	CMicDataList::AddItem(CMicData*	pItem)
{
	RES_DECLR(result);
	PTR_DECLR(CMicData,pData);

	if(PTR_NOT_NULL(pItem))					//	Validate item pointer.
	{
		PTR_CREATE(CMicData,pData);		//	Create a copy of the item. 
		pData->operator = (pItem);			//	duplicate the object.
		
		FileChkConnect(pData);				//	Update file connection.
		RES_CHECK(result,PTR_NOT_NULL(FW_LIST_ADD_TAIL(my_data_items, pData)));	//	Add to list.
	}
	else{
		RES_FAILE(result);
	}
	RES_RETURN(result);
}

FW_RESULT	CMicDataList::AddItem(STRING	dscrp)
{
	RES_DECLR(result);
	PTR_DECLR_NEW(CMicData,pData);

	if(PTR_NOT_NULL(pData))						//	Validate item pointer.
	{
		if(true == pData->Description(dscrp))			//	Operate the new settings.
		{															//	if successful.
			FileChkConnect(pData);							//	Update file connection.
			FW_LIST_ADD_TAIL(my_data_items, pData);
		}
		else
		{
			RES_FAILE(result);
			PTR_DESTROY(pData);
		}
	}
	else{
		RES_FAILE(result);
	}

	RES_RETURN(result);
}

FW_RESULT	CMicDataList::AddItem(STRING title, DATA_FORMAT format, int size, const unsigned char buffer[])
{
	RES_DECLR(result);
	PTR_DECLR_NEW(CMicData,pData);

	if(PTR_NOT_NULL(pData))
	{
		RES_CHECK(result,pData->Title(title));
		RES_CHECK(result,pData->Format(format));
		RES_CHECK(result,pData->Size(size));
		
		if(buffer!=NULL)	{
			RES_CHECK(result,pData->BuffSet(buffer,size,0x00)!=0x00);
		}
		if(result == true)	{
			RES_CHECK(result,PTR_NOT_NULL(FW_LIST_ADD_TAIL(my_data_items, pData)));	//	Add to list.
		}
		else	{
			PTR_DESTROY(pData);
		}
	}
	else{
		RES_FAILE(result);
	}

	RES_RETURN(result);
}








/********************************************************************\
*																							*
*								V a l i d a t i o n									*
*																							*
\********************************************************************/

//	Return the errors list.
STRING	CMicDataList::Errors(void)
{
	return(my_errors);
}

//	Clear the errors list.
FW_RESULT		CMicDataList::ErrorsClear(void)
{
	RES_DECLR(result);

	my_error = false;
	STR_CLEAR(my_errors);
	RES_CHECK(result,STR_IS_EMPTY(my_errors));

	RES_RETURN(result);
}

//	Add error to the errors list.
FW_RESULT		CMicDataList::ErrorAdd(STRING error)
{
	RES_DECLR(result);

	my_error = true;
	STR_ADD(my_errors, error + DATA_ERR_SEPARATOR);
	
	RES_RETURN(result);
}

//	Check if the requests are received correctly.
bool		CMicDataList::DataChk(void)
{
	int	index = 0x00;
	RES_DECLR(result);												//	Any replay is accepted if no replay found wrong.

	RES_CHECK(result,ErrorsClear());
	for(int counter = 0x00; counter<my_data_items.GetCount(); counter++)	//	Check all replay definitions.
	{
		PTR_DECLR_INIT(CMicData,pItem,my_data_items.GetAt(my_data_items.FindIndex(counter)));

		if(pItem->Size()!=0x00)
		{
			RES_CHECK(result,pItem->ErrorsClear());
			if(true != pItem->IsVerifayd())	{
				RES_CHECK(result,ErrorAdd(pItem->Errors()));
			}
		}
	}
	RES_ALERT(result);
	return(!my_error);
}










/********************************************************************\
*																							*
*								C o n t e n t s										*
*					Contents is compound of data objects						*
*																							*
\********************************************************************/

//	Get the contents length
int	CMicDataList::ContentsLength(void)
{
	int	length = 0x00;

	for(int counter = 0x00; counter<my_data_items.GetCount(); counter++)	//	Check all replay definitions.
	{
		length += my_data_items.GetAt(my_data_items.FindIndex(counter))->Size();
	}

	return(length);
}










/***********************************************************************\
*																								*
*									B u f f e r												*
*	The actual data build when transmitting or received when receiving	*
*																								*
\***********************************************************************/


//--------------------------------------------------------------------
//	Builde the contents and place in a buffer	acording to formation settings.
//	Update the parent with the buffer contents.
CFwBuffer*	CMicDataList::BufferBuild(void)
{
	RES_DECLR(result);

	CFwBuffer::BufferClear();										//	Clear the buffer.
	for(int counter = 0x00; counter<my_data_items.GetCount(); counter++)	//	Check all replay definitions.
	{
		PTR_DECLR_INIT(CMicData, pItem, my_data_items.GetAt(my_data_items.FindIndex(counter)));

		if(pItem->Size() > 0x00)								//	No error is found and data is not empty.
		{
			RES_CHECK(result, pItem->Build());				//	check for error.
			if(pItem->Length()>0x00){							//	Buffer was build.
				RES_CHECK(result, CFwBuffer::BufferAdd(pItem));
			}
		}
	}
	RES_ALERT(result);
	return(this);
}

//	Set contents buffer as contents.
//	false is returned if the allocation problem occurse.
FW_RESULT	CMicDataList::BufferSet(CFwBuffer* pBuff)
{
	RES_DECLR(result)
	int	data_index	= 0x00;

	data_index = 0x00;
	for(int counter = 0x00; counter<my_data_items.GetCount(); counter++)
	{																						//	Check all replay definitions.
		PTR_DECLR_INIT(CMicData, pData, my_data_items.GetAt(my_data_items.FindIndex(counter)));	//	Get data item.
		RES_CHECK(result, pData->BuffClear());												//	Clear data buffer.

		if(pBuff->Length() > data_index)									//	End of message not reached.
		{																			//	re construct the buffer.
			if(pData->Size() == 0x00){										//	No definition of expected size.
				RES_CHECK(result, pData->Size(pBuff->Length()-data_index));	//	accept all remaining bytes
			}
//			RES_CHECK(result,(pData->Size()<=(pBuff->Length()-data_index)));
			if(pData->Size()<=(pBuff->Length()-data_index))	{		//	received buffer exceeds expected size.
				data_index = pData->BuffSet(pBuff->Buffer(),pBuff->Length(),data_index);// set buffer contents.
			}
			else{
				RES_FAILE(result);
			}
		}
	}

	if(pBuff->Length() > data_index){				//	Received information larger than pre defined.
		PTR_DECLR_NEW(CMicData,pData);				//	Create new data object;

		if(PTR_NOT_NULL(pData))
		{
			RES_CHECK(result,pData->Title(DATA_ITEM_UNEXP));	//	Unexpected data item.
			RES_CHECK(result,pData->Format(FORM_BYTE_ARR));		//	as expected array.

			RES_CHECK(result,pData->Size(pBuff->Length()-data_index));	//	accept all remaining bytes
			if(RES_TRUE(result))
			{
				data_index = pData->BuffSet(pBuff->Buffer(),pBuff->Length(),data_index);	// set buffer contents.
				RES_CHECK(result,AddItem(pData));														//	Add data item.
			}
			PTR_DESTROY(pData);
		}
	}
	RES_RETURN(result);
}

//--------------------------------------------------------------------
//	Build the contents and place in a buffer according to formation settings.
//	Update the parent with the buffer contents.
CFwBuffer*	CMicDataList::BufferGet(void)
{
	RES_DECLR(result);
	PTR_DECLR(CMicData,pItem);
	PTR_DECLR_NEW(CFwBuffer,pBuffer);					//	Create buffer.

	for(int index = 0x00; index < my_data_items.GetCount(); index++)
	{
		PTR_SET(pItem,my_data_items.GetAt(my_data_items.FindIndex(index)));

		if(RES_TRUE(result) && (pItem->Size() > 0x00))				//	No error is found and data is not empty.
		{
			RES_CHECK(result,pItem->Build());							//	check for error.
			RES_CHECK(result,pBuffer->BufferAdd(pItem->Buffer(),pItem->Length()));
		}
	}
	PTR_RETURN(pBuffer);
}


//	File connection.
bool	CMicDataList::FileIsConnect(void)
{
	return(my_file_cnct);
}
bool	CMicDataList::FileChkConnect(CMicData*	pData)
{
	my_file_cnct =	my_file_cnct || pData->FileEna();	//	Update file connection.
	return(my_file_cnct);
}

//	Get the file data titles string.
STRING	CMicDataList::FileTitleGet(void)
{
	RES_DECLR(result);
	PTR_DECLR(CMicData,pData);

	STR_DECLR(my_file_titl);														//	Clear titles string.
	for(int counter = 0x00; counter<my_data_items.GetCount(); counter++)
	{																						//	Check all replay definitions.
		PTR_SET(pData,my_data_items.GetAt(my_data_items.FindIndex(counter)));	//	Get data item.
		
		if(true == pData->FileEna())															//	If file connected.
		{
			STR_ADD(my_file_titl,pData->FileTitle(STR_IS_EMPTY(my_file_titl)));			//	Add the title.
		}
	}
	STR_RETURN(my_file_titl);															//	Return titles string.
}

//	Get the file data recorded string.
STRING	CMicDataList::FileDataGet(void)
{
	RES_DECLR(result);
	PTR_DECLR(CMicData,pData);

	STR_DECLR(my_file_data);														//	Clear contents.
	for(int counter = 0x00; counter<my_data_items.GetCount(); counter++)
	{																						//	Check all replay definitions.
		PTR_SET(pData,my_data_items.GetAt(my_data_items.FindIndex(counter)));	//	Get data item.
		if(true == pData->FileEna()){															//	If file connected.
			STR_ADD(my_file_data,pData->FileCont(STR_IS_EMPTY(my_file_data)));	//	Add the title.
		}
	}
	STR_RETURN(my_file_data);															//	Return titles string.
}





/***********************************************************************\
*																								*
*									Operators												*
*																								*
*																								*
\***********************************************************************/

//	Return a pointer to the data item index.
CMicData*	CMicDataList::operator[](int index)							//	Return a data item from the contents array.
{
	if((index>=0x00) &&(index<my_data_items.GetCount())) {
		return(my_data_items.GetAt(my_data_items.FindIndex(index)));
	}
	return(NULL);
}

CMicDataList*	CMicDataList::operator = (CMicDataList* pDataHndlr)
{
	RES_DECLR(result);

	//RES_CHECK(result, CMicString::Clear());
	CFwBuffer::operator = ((CFwBuffer*)pDataHndlr);

	if(PTR_NOT_NULL(pDataHndlr))
	{
		my_errors	=	pDataHndlr->Errors();
		my_error		=	pDataHndlr->ErrorExist();

		for(int index = 0x00; index < pDataHndlr->Count(); index++)
		{
			RES_CHECK(result,AddItem(pDataHndlr->operator[](index)));
		}
	}
	return(result ? this:NULL);
}


bool	CMicDataList::operator == (CMicDataList*	pDataHndlr)
{
	RES_DECLR(result);

	bool			equal	= false;
	if(PTR_NOT_NULL(pDataHndlr))
	{
		equal = CFwBuffer::operator == ((CFwBuffer*)pDataHndlr);

		equal	&=	(my_errors	== pDataHndlr->Errors());
		equal	&=	(my_error	== pDataHndlr->ErrorExist());
		equal	&=	(my_data_items.GetCount() == pDataHndlr->Count());	

		
		for(int index = 0x00; index < my_data_items.GetCount(); index++)
		{
			PTR_DECLR_INIT(CMicData, pItem, my_data_items.GetAt(my_data_items.FindIndex(index)));
			equal	&=	( pItem->operator==(pDataHndlr->operator[](index)));
		}
	}
	else
	{
		CFwBuffer::BufferClear();
	}

	RES_ALERT(result);
	return(equal);
}

//-------------------------------------------------
//	Set the description.
FW_RESULT	CMicDataList::DescriptionLet(STRING description)
{
	RES_DECLR(result);

//	CMicString	parser;
//	RES_CHECK(result,parser.DescriptionLet(description));

	RES_CHECK(result,Clear());											//	Clear current contents.

//	STR_DECLR(page_str);
	int	page_indx = 0x00;

	STR_DECLR_INIT(page_str, CMicString::GetPage(description, page_indx++));
	RES_CHECK(result,Title(page_str));	//	Title.

	do{
		STR_SET(page_str, CMicString::GetPage(description, page_indx++));	//	Data item page.
		if(STR_NOT_EMPTY(page_str)){							//	Item settings page exists.
			RES_CHECK(result, AddItem(page_str));	//	Add Item from string.
		}
	}while(STR_NOT_EMPTY(page_str));

	RES_RETURN(result);
}
//	Get the  description.
STRING	CMicDataList::DescriptionGet(bool hex)
{
	RES_DECLR(result);
	STR_DECLR(strData);
	STR_DECLR(description);

	STR_ADD(description, Title());
	STR_ADD(description, TAG_PAG_END);

	for(int counter = 0x00; counter<my_data_items.GetCount(); counter++)	//	Check all replay definitions.
	{
		PTR_DECLR_INIT(CMicData, pItem, my_data_items.GetAt(my_data_items.FindIndex(counter)));

		STR_SET(strData,pItem->Description(hex, true, true, true, true));
		STR_ADD(description, strData);
		if(counter < (my_data_items.GetCount()-0x01))	{	//	not the last replay definition(rep_count equals replay definitions + 1) .
			STR_ADD(description, TAG_PAG_END);					//	Add replay definition seperator.
		}
	}

	RES_ALERT(result);
	STR_RETURN(description);
}

//	Get the  description.
STRING	CMicDataList::DescriptionGet(bool hex, bool title)
{
	RES_DECLR(result);
	STR_DECLR(strData);
	STR_DECLR(description);

	if(true == title)
	{
		STR_ADD(description, Title());
		STR_ADD(description, TAG_PAG_END);
	}
	for(int counter = 0x00; counter<my_data_items.GetCount(); counter++)	//	Check all replay definitions.
	{
		PTR_DECLR_INIT(CMicData, pItem, my_data_items.GetAt(my_data_items.FindIndex(counter)));

		STR_SET(strData,pItem->Description());
		STR_ADD(description, strData);
		if(counter < (my_data_items.GetCount()-0x01))	{	//	not the last replay definition(rep_count equals replay definitions + 1) .
			STR_ADD(description, TAG_PAG_END);					//	Add replay definition seperator.
		}
	}

	RES_ALERT(result);
	STR_RETURN(description);
}


