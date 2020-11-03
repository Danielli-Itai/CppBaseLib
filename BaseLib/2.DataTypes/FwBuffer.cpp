/***********************************************************************\
*																								*
*								B u f f e r   H a n d l e r							*
*																								*
*		The buffer handler is a base class for manipulating a block			*
*		of memory treated as an array.												*
\***********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





/***********************************************************************\
*																								*
*										Include files										*
*																								*
\***********************************************************************/
#include	HDR_FW_TEXT_STR
#include	HDR_FW_BUFFER
#include	HDR_FW_POINTERS





/********************************************************************\
*																							*
*				 C o n s t r u c t i o n / D e s t r u c t i o n			*
*																							*
\********************************************************************/
//	Constructor.
CFwBuffer::CFwBuffer()
{
	RES_DECLR(result);

	STR_INIT(my_title);	//	No title.

	PTR_INIT(my_pBuffer);				//	set buffer pointer as null
	my_length	=	0x00;

	my_bottom		=	UNKNOWN;	//	Unknown maximal length.
	my_pointer		=	UNKNOWN;	//	Unknown pointer.
	my_block_size	=	UNKNOWN;	//	Unknown size.

	RES_ALERT(result);
	return;
}

//	Destructor.
CFwBuffer::~CFwBuffer()
{
	RES_DECLR(result);

	BufferClear();

	RES_ALERT(result);
	return;
}










/***********************************************************************\
*																								*
*									P r o p e r t i e s									*
*																								*
\***********************************************************************/
//	Buffer title.
FW_RESULT	CFwBuffer::Title(STRING new_title)
{
	RES_DECLR(result);

	my_title = new_title;
	RES_CHECK(result,STR_NOT_EMPTY(my_title ));

	RES_RETURN(result);
}
STRING	CFwBuffer::Title(void)
{
	STR_RETURN(my_title);
}

//	Buffer user.
FW_RESULT	CFwBuffer::User(FW_INT user)
{
	my_user	=	user;
	RES_RETURN(my_user >= 0x00);
}
FW_INT	CFwBuffer::User(void)
{
	return(my_user);
}
STRING	CFwBuffer::UserGet(bool Hex)
{
	STR_DECLR(tmp);

	STR_SET(tmp, "usr[");						//	prefix.
	STR_ADD(tmp, NumToStr(my_user,Hex));	//	contents.
	STR_ADD(tmp, "]");									//	closure.

	STR_RETURN(tmp);
}

//	Buffer size methods.
FW_INT	CFwBuffer::Bottom(void)
{
	return(my_bottom);
}
FW_RESULT	CFwBuffer::Bottom(FW_INT	leng)
{
	my_bottom = leng;
	RES_RETURN(my_bottom >= my_length);
}
STRING	CFwBuffer::BottomGet(bool Hex)
{
	STR_DECLR(tmp);
	
	STR_SET(tmp,"lmx[");						//	prefix.
	STR_ADD(tmp, NumToStr(my_bottom,Hex));	//	contents.
	STR_ADD(tmp,"]");							//	closure.

	STR_RETURN(tmp);
}

//	Buffer block.
FW_RESULT	CFwBuffer::BlockSize(int block_size)
{
	RES_DECLR(result);

	my_block_size	=	block_size;
	RES_CHECK(result,(my_block_size > 0) /*&& (my_block_size <= my_length)*/);

	RES_RETURN(result);
}
int	CFwBuffer::BlockSize(void)
{
	return(my_block_size);
}

STRING	CFwBuffer::BlockSizeGet(bool Hex)
{
	STR_DECLR(tmp);
	
	STR_SET(tmp,"blk[");								//	prefix.
	STR_ADD(tmp, NumToStr(my_block_size,Hex));	//	contents.
	STR_ADD(tmp,"]");									//	closure.
	
	STR_RETURN(tmp);
}


//----------------------------------------------
//	set the buffer length.
FW_RESULT	CFwBuffer::Length(FW_INT length)
{
	my_length = length;
	RES_RETURN(my_length < my_bottom);
}
//	Get the buffer length.
FW_INT	CFwBuffer::Length(void)
{		return(my_length);			}

//	Get the length description.
STRING	CFwBuffer::LengthGet(bool Hex)
{
	STR_DECLR(tmp);
	
	STR_SET(tmp,"ln[");						//	prefix.
	STR_ADD(tmp, NumToStr(my_length, Hex));	//	contents.
	STR_ADD(tmp,"]");							//	closure.

	STR_RETURN(tmp);
}

//	Buffer is completed.
FW_RESULT	CFwBuffer::Pointer(FW_INT pointer)
{
	RES_DECLR(result);

	my_pointer	=	pointer;
	RES_CHECK(result,my_pointer <= my_length);

	RES_RETURN(result);
}
int	CFwBuffer::Pointer(void)
{
	return(my_pointer);
}
STRING	CFwBuffer::PointerGet(bool	Hex)
{
	STR_DECLR(tmp);

	STR_SET(tmp,"ptr[");						//	prefix.
	STR_ADD(tmp, NumToStr(my_pointer,Hex));//	contents.
	STR_ADD(tmp,"]");							//	closure.
	
	STR_RETURN(tmp);
}


bool	CFwBuffer::Complete(void)	//	Buffer is completed.
{
	return(my_pointer	>= my_length);
}

FW_RESULT	CFwBuffer::Properties(STRING text_str)
{
	RES_DECLR(result);

	CMicString parser;
//	RES_CHECK(result, parser.LetPage(text_str));						//	Set data page.

	RES_CHECK(result, Title(parser.GetItem(text_str, 0)));
	RES_CHECK(result,	User(parser.GetNum(text_str, 1)));
	RES_CHECK(result, BlockSize(parser.GetNum(text_str, 2)));
	RES_CHECK(result, Bottom(parser.GetNum(text_str, 3)));
	RES_CHECK(result, Pointer(parser.GetNum(text_str, 4)));

	RES_RETURN(result);
}


	//	Get Identification string
//	"title,ad[...],op[...]"
STRING	CFwBuffer::Properties(bool hex)
{
	STR_DECLR(tmp);
	
	STR_ADD(tmp,Title());
	STR_ADD(tmp,TAG_ITM_END);

	STR_ADD(tmp,UserGet(hex));
	STR_ADD(tmp,TAG_ITM_END);

	STR_ADD(tmp,BlockSizeGet(hex));
	STR_ADD(tmp,TAG_ITM_END);

	STR_ADD(tmp,BottomGet(hex));
	STR_ADD(tmp,TAG_ITM_END);

	STR_ADD(tmp,PointerGet(hex));

	STR_RETURN(tmp);
}








/***********************************************************************\
*																								*
*								B u f f e r   a c c e s s								*
*																								*
\***********************************************************************/
//---------------------------------------------------------
//	Get a pointer to the buffer contents.
const char*	CFwBuffer::Buffer(void)
{
	return(my_pBuffer);
}
//	Return a byte at index.
char	CFwBuffer::Buffer(int	index)
{
	RES_DECLR(result);
	int	byte = -1;
	
	if(index<my_length)	//	Check in range.
	{
		byte = (*(my_pBuffer+index));			//	Set buffer contents.
	}
	else{
		if(0x00 < my_length){					//	If buffer is not empty.
			RES_FAILE(result);
		}
	}
	RES_ALERT(result);							//	validate in range.
	return(byte);									//	return contents.
}

//------------------------------------------------------'
//	Clear the old contents. and Allocate new buffer space.
FW_RESULT	CFwBuffer::Allocate(int leng)
{
	RES_DECLR(result);

	//	Check buffer is empty.
	RES_ALERT((my_pBuffer==NULL)&&(my_length==0x00));

	my_length = leng;									//	update new length.	
	if(my_length > 0x00)								//	not empty length.
	{														//	Resize the buffer.
		my_pBuffer = new char[my_length];				//	Allocate new buffer size.
		RES_CHECK(result, 0x00 != memset(my_pBuffer,0x00,my_length));	//	Initialize the buffer contents.
		RES_CHECK(result, (my_pBuffer!=NULL));
	}

	RES_RETURN(result);
}

//------------------------------------------------------'
//	Set Buffer size and contents.
FW_RESULT	CFwBuffer::Buffer(const char* pArr,int leng)
{
	RES_DECLR(result);

	RES_CHECK(result,Allocate(leng));							//	Allocate memory space.
	if(my_length>0x00){															//	Not empty space.
		RES_CHECK(result, NULL!=memcpy(my_pBuffer,pArr,my_length));	//	copy the new contents.
	}
	RES_RETURN(result);
}

//------------------------------------------------------------
//	Add auto buffer.
//	add a new memory block at the end of the current block
FW_RESULT	CFwBuffer::BufferAdd(const char* new_buffer,int new_length)
{
	RES_DECLR(result);
	if(PTR_NOT_NULL(new_buffer) && (new_length>0x00))		//	Not an empty operator.
	{
		char*	last_buffer = new char [my_length];
		int				last_length	= my_length;
		memcpy(last_buffer, my_pBuffer, last_length);

		my_length  = 0x00;
		PTR_DESTROY(my_pBuffer);
		RES_CHECK(result, Allocate(last_length + new_length));	//	Allocate new buffer.
		if(RES_TRUE(result))													//	Allocation successful.
		{
			RES_CHECK(result, NULL != memcpy(my_pBuffer, last_buffer ,last_length));	//	copy previous buffer contents.
			RES_CHECK(result, NULL != memcpy((my_pBuffer+last_length), new_buffer,new_length));	//	add the new buffer contents.
		}
		PTR_DESTROY_ARR(last_buffer);										//	clear the previous buffer.
	}
	RES_CHECK(result,((my_pBuffer==NULL)&&(my_length==0x00))||((my_pBuffer!=NULL)&&(my_length!=0x00)));
	RES_RETURN(result);
}

//	Add buffer to the current buffer.
FW_RESULT	CFwBuffer::BufferAdd(CFwBuffer* pBuffer)
{
	RES_DECLR(result);

	int	length	= 0x00;
	if(PTR_NOT_NULL(pBuffer))
	{
		if(PTR_NOT_NULL(pBuffer->Buffer()) && (0x00<pBuffer->Length()))
		{
			RES_CHECK(result,BufferAdd(pBuffer->Buffer(), pBuffer->Length()));
		}
	}
	RES_RETURN(result);
}

FW_RESULT	CFwBuffer::BufferSet(const char new_byte,int new_index)
{
	RES_DECLR(result);

	if(my_length>new_index)
	{
		(*(my_pBuffer+new_index)) = new_byte;
	}
	else{
		RES_FAILE(result);
	}
	RES_RETURN(result);
}

FW_RESULT	CFwBuffer::BufferSet(const char* new_buffer,int new_length, int strt_frm)
{
	RES_DECLR(result);
	
	if(my_length>(new_length+strt_frm))
	{
		RES_CHECK(result,(NULL!=memcpy(my_pBuffer, (new_buffer+strt_frm), new_length)));
	}

	RES_RETURN(result);
}


//-----------------------------------------------------------------------------'
//	Set buffer.
FW_RESULT	CFwBuffer::Buffer(void* pArr,int leng)
{
	RES_DECLR(result);

	RES_CHECK(result,Buffer((char*)pArr, leng));

	RES_RETURN(result);
}

	//	String conversion.
	FW_RESULT	CFwBuffer::BufferLet(STRING	text_str)
	{
		RES_RETURN(Buffer(STR_PBUFF(text_str), STR_LEN(text_str)));
	}

	//	Return a string containing the buffer contents.
	STRING	CFwBuffer::BufferGet()
	{
		STRING	strReturn('x', my_length);;						//	Temporary buffer.

		for (int counter = 0;counter<my_length;counter++){
			strReturn[counter] = my_pBuffer[counter];				//	Set buffer to string. 
		}

		RES_ALERT(my_length == STR_LEN(strReturn));

		STR_RETURN(strReturn);											//	Return the string object containing the buffer.
	}



FW_RESULT CFwBuffer::BufferClear(void)
{
	my_bottom		=	UNKNOWN;	//	Unknown maximal length.
	my_pointer		=	UNKNOWN;	//	Unknown pointer.
	my_block_size	=	UNKNOWN;	//	Unknown size.

	if(PTR_NOT_NULL(my_pBuffer)){
		PTR_DESTROY(my_pBuffer);
	}
	my_length	=	0x00;
	RES_RETURN(RES_OK);
}











//-----------------------------------------------
//	Return the first byte in buffer.
char	CFwBuffer::Head(void)
{
	char	head = (char)0xFF;	//	default when not defined.

	if(PTR_NOT_NULL(my_pBuffer)){
		head = (*my_pBuffer);
	}
	return(head);
}

//	Remove bytes from head.
FW_RESULT	CFwBuffer::HeadRemove(int size)
{
	RES_DECLR(result);

	RES_CHECK(result,((my_pBuffer==NULL)&&(my_length==0x00))||((my_pBuffer!=NULL)&&(my_length!=0x00)));
	if(my_length>size)						//	Buffer greater than removed.
	{												//	Preserve remaining data.
		char*	last_buffer = new char[my_length];
		int				last_length	= my_length;
		memcpy(last_buffer, my_pBuffer, last_length);

		my_length  = 0x00;
		PTR_DESTROY(my_pBuffer);
		Allocate(last_length - size);		//	Allocate smaller buffer.
		if(my_pBuffer != NULL)
		{
			RES_CHECK(result, NULL!=memcpy(my_pBuffer, (last_buffer+size), my_length));	//	Copy the rest of the old buffer to the new buffer.
			PTR_DESTROY_ARR(last_buffer);	//	delete t he Old buffer.
		}
		PTR_DESTROY_ARR(last_buffer);	//	delete t he Old buffer.
	}
	else	{										//	Do not remove more than buffer size.
		BufferClear();
	}

	RES_CHECK(result,((my_pBuffer==NULL)&&(my_length==0x00))||((my_pBuffer!=NULL)&&(my_length!=0x00)));
	RES_RETURN(result);
}

//	Return the first byte and remove it from buffer.
char	CFwBuffer::HeadGet()
{
	RES_DECLR(result);
	char	head = 0;

	if(false == IsEmpty()){
		head  = (*my_pBuffer);						//	Save the first byte to be returned.
		HeadRemove(1);
	}
	else{
		RES_FAILE(result);
	}

	RES_ALERT(result);
	return(head);
}


//	Return the last byte in buffer.
char	CFwBuffer::End(void)
{
	RES_DECLR(result);
	char	end = (char)0xFF;	//	default when not defined.

	if(my_length>0x00)	{
		end = (*(my_pBuffer + my_length - 1));
	}
	else{
		RES_FAILE(result);
	}

	RES_ALERT(result);
	return(end);
}






/********************************************************************\
*																							*
*							S t r i n g    c o n v e r s i o n					*
*																							*
\********************************************************************/

//---------------------------------------------------------------
//	Get a string containing formatted description of the message.
//	each item iseparated by ',' - 0x01, 0x02, ....
STRING CFwBuffer::BufferText(bool	Hex)
{
	STR_DECLR(description);
	STR_DECLR(tmp);

	for(FW_INT count=0; count<my_length; count++)
	{
		STR_INIT(tmp);
		if(Hex){
			STR_TO_HEX(tmp, *(my_pBuffer+sizeof(char)*count));
			if(count < my_length-1)	STR_ADD(tmp, ">");
			description += "0x" + tmp;
		}
		else{
			STR_TO_DEC(tmp, *(my_pBuffer+sizeof(char)*count));
			if(count < my_length-1)	STR_ADD(tmp, ",");
			STR_ADD(description, tmp);
		} 
	}
	return(description);
}

	//	Set buffer according to description.
	//	the description is an array of numbers separated by	'.' ':' ';' ',' '>' ' '
FW_RESULT	CFwBuffer::BufferText(STRING	array)
{
	RES_DECLR(result);

	char	Val = 0x00;
	int	num_count = -0x01;
	int	index = 0x00, index1=0x00, lst_index = 0x00, tmp = 0x00;
	bool	continu = true, Hex = false;

	BufferClear();
	STR_DECLR_INIT(description,array);

	while(continu)
	{
		//	Get the index of the next separator.
		index = STR_FIND_INDEX(description, TAG_TXT_END, lst_index);		//	search space separator marker.
		
		if(index == -1)													//	not found.
			index = STR_FIND_INDEX(description, TAG_LNK_END, lst_index);//	search array separator marker.
		if(index == -1)													//	not found.
			index = STR_FIND_INDEX(description, TAG_ITM_END, lst_index);//	search array separator marker.
		if(index == -1)													//	not found.
			index = STR_FIND_INDEX(description, TAG_PAG_END, lst_index);//	search array separator marker.
		if(index == -1)													//	not found.
			index = STR_FIND_INDEX(description, TAG_SEG_END, lst_index);//	search segment separator marker.
		if(index == -1)													//	not found.
			index = STR_FIND_INDEX(description, TAG_FRM_END, lst_index);//	search end of data marker.
		if(index == -0x01)												//	End of current number not found
		{
			index = STR_LEN(description);
			continu = false;												//	set as last number.
		}

		Val = 0x00;														//	new number value.
		if(index > lst_index)
		{										//	new number is found.
			num_count ++;												//	Increase numbers counter.
			
			Hex = false;
			
			if(	(STR_FIND_INDEX(description, "0x", lst_index) > -0x01)&&	//	Start searching from last index.
					((int)STR_FIND_INDEX(description, "0x", lst_index) < index))		//	if found chk it is before the end of this number.
				Hex = true;													//	Hex number is found.
			
			if(	(STR_FIND_INDEX(description, "[", lst_index) > -0x01)&&		//	Start searching from last index.
					((int)STR_FIND_INDEX(description, "[", lst_index) < index))		//	if found chk it is before the end of this number.
				lst_index = STR_FIND_INDEX(description, "[", lst_index);		//	Number closure is found.
			
			while( lst_index < index)
			{														//	run threw new number digits.
				tmp = description[lst_index];				//	get digit.
				lst_index++;									//	move to next byte.
			
				if(Hex)
				{
					if((tmp>='0') && (tmp<='9') ){		//	legal digit is found.
						tmp -= '0';								//	Convert from ASCII to digit.
						Val *= 0x10;
						Val += tmp;								//	increase value.
					}
					if((tmp>='A') && (tmp<='F')){
						tmp = tmp - 'A' + 10;
						Val *= 0x10;
						Val += tmp;								//	increase value.
					}
					if((tmp>='a') && (tmp<='f')){
						tmp = tmp - 'a' + 10;
						Val *= 0x10;
						Val += tmp;								//	increase value.
					}
				}
				else{
					if( (tmp>='0') && (tmp<='9') ){		//	legal digit is found.
						tmp -= '0';
						Val *= 10;
						Val += tmp;								//	increase value.
					}
				}
			}
			if((Val>=0x00) && (Val<=255)){
				RES_CHECK(result,BufferAdd(&((char)Val),1));
			}
		}

		lst_index++;
	}

	RES_RETURN(result);
}









/********************************************************************\
*																							*
*									O p e r a t o r s									*
*																							*
\********************************************************************/

//------------------------------------------------------------------
//	Assign a buffer to current object.
//	If NULL is assigned the object is cleared and the NULL is returned.
CFwBuffer*	CFwBuffer::operator = (const CFwBuffer* pBuff)
{
	RES_DECLR(result);

	BufferClear();

	if(PTR_NOT_NULL(pBuff))
	{
		my_title			=	pBuff->my_title;		
		my_block_size	=	pBuff->my_block_size;
		my_pointer		=	pBuff->my_pointer;
		my_bottom		=	pBuff->my_bottom;
		
		if (0x00 != pBuff->my_length){	//	Not empty space.
			RES_CHECK(result, Buffer(pBuff->my_pBuffer, pBuff->my_length));
		}
	}

	RES_ALERT(result);
	return(this);										//	Return this pointer.
}
//	Add the contents of a buffer to current buffer.
CFwBuffer*	CFwBuffer::operator += (const CFwBuffer* pBuff)
{
	RES_DECLR(result);
	PTR_DECLR(CFwBuffer,pThis);									//	return pointer to this.

	RES_CHECK(result,BufferAdd(pBuff->my_pBuffer,pBuff->my_length));
	if(RES_TRUE(result))	{
		pThis = this;														//	return NULL.
	}

	RES_ALERT(result);
	PTR_RETURN(pThis);
}

// compare this buffer contents with another buffer contents.
bool CFwBuffer::operator ==(const CFwBuffer* pBuff)
{
	bool	compare = false;

	if(PTR_NOT_NULL(pBuff))
	{
		compare = (my_length == pBuff->my_length);								//	Check length
		if(compare && (my_length>0x00))												//	Matching length and not empty.
		{
			compare &= (memcmp(my_pBuffer,pBuff->my_pBuffer,my_length) == 0);	//	Check contents.
		}
	}
	else{
		compare = true;
	}
	return(compare);
}

//-------------------------------------------------
//	Return a byte at position index from buffer.
char&	CFwBuffer::operator[](int Index)
{
	RES_ALERT(Index < my_length);										//	Valid index is received ?
	return(*(my_pBuffer+Index));										//	return the byte from memory.
}

//-------------------------------------------------
//	Set the buffer according to the description.
FW_RESULT	CFwBuffer::DescriptionLet(STRING description)
{
	RES_DECLR(result);


	RES_CHECK(result,Title(CMicString::GetSegment(description, 0x00)));//	Buffer Title.
	STR_DECLR_INIT(segment, CMicString::GetSegment(description, 0x01));
	if(STR_NOT_EMPTY(segment))
	{
		RES_CHECK(result,Properties(CMicString::GetPage(segment, 0x00)));		//	Buffer properties.
		RES_CHECK(result,BufferLet(CMicString::GetPage(segment, 0x01)));		//	Buffer contents.
	}
	else{
		RES_FAILE(result);
	}

	RES_RETURN(result);
}
//	Get the buffer description.
STRING	CFwBuffer::DescriptionGet(bool hex)
{
	STR_DECLR(description);

	STR_SET(description, Title());				//	Title.
	STR_ADD(description, TAG_SEG_END);		//	:
	STR_ADD(description, Properties(hex));	//	Properties.
	STR_ADD(description, TAG_PAG_END);		//	;
	STR_ADD(description,	BufferText(hex));	//	Buffer.

	STR_RETURN(description);
}









/********************************************************************\
*																							*
*								L i s t   m e t h o d s								*
*																							*
\********************************************************************/

//-------------------------------------
//	Check if the message bffer is empty
bool	CFwBuffer::IsEmpty(void)
{	return(my_length == 0);		}

//	search a byte in the buffer.
int	CFwBuffer::Serach(char byte)
{
	for(int index=0x00;index<my_length;index++)
	{											//	iterate threw the buffer length.
		if((*my_pBuffer)==byte)			//	check contents.
		{
			return(index);					//	return if found.
		}
	}
	return(-0x01);							//	not found.
}

