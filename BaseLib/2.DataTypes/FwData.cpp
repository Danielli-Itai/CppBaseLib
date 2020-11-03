/********************************************************************\
*																							*
*									D a t a   I t e m									*
*		The data item holds both definition and actual value.				*
*		Expected data is stored in 'Contents', it holds the properties *
*			and the contents of the expected information						*
*		Actual data is stored in the parent class which holds the		*
*			actual information for the class user.								*
*																							*
\********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





/********************************************************************\
*																							*
*									Include files										*
*																							*
\********************************************************************/
#include	HDR_FW_POINTERS
#include HDR_FW_DATA
#include	HDR_FW_XML_TYPES





/********************************************************************\
*																							*
*											Globals										*
*																							*
\********************************************************************/
ENUM_NAMES_CREATE(DATA_FIELD,DATA_FIELD_NAMES);
ENUM_NAMES_CREATE(DATA_FORMAT,DATA_FORMAT_NAMES);
ENUM_NAMES_CREATE(DATA_ERROR,DATA_ERROR_NAMES);





/********************************************************************\
*																							*
*											Class											*
*																							*
\********************************************************************/

//	Clear the class and parent class.
FW_RESULT	CMicData::Init(void)
{
	RES_DECLR(result);

	ENUM_INIT(DATA_FORMAT,my_format);				//	Data type - Buffer, Time, File...
	my_size		=	0x00;									//	preset buffer size.

	my_buff_num	=	ULONG_MAX;					//	No contents.

	my_error		=	RES_ERR;
	STR_INIT(my_errors);

	STR_INIT(my_description);					//	Formation string.

	RES_RETURN(result);
}

FW_RESULT	CMicData::Clear(void)
{
	RES_DECLR(result);

	RES_CHECK(result,Init());
	CFwBuffer::BufferClear();

	RES_RETURN(result);
}
//	Call parent constructor and clear.
CMicData::CMicData()
{
	RES_ALERT(Init());
}

//	Clear before destruction.
CMicData::~CMicData()
{
	RES_ALERT(Clear());
}





/********************************************************************\
*																							*
*									B U F F E R											*
*																							*
\********************************************************************/
//	Data type - Buffer, Time, File...
DATA_FORMAT	CMicData::Format()
{	return(my_format);			}
FW_RESULT	CMicData::Format(DATA_FORMAT format)
{	RES_RETURN(ENUM_SET(DATA_FORMAT,my_format,format));	}

//	preset size and allocation for the contents buffer.
FW_INT	CMicData::Size()
{	return(my_size);			}
FW_RESULT	CMicData::Size(FW_INT new_size)
{
	my_size = new_size;
	RES_RETURN(my_size == new_size);
}		//	Set new size.

//-------------------------------------------------
//	Get unsigned long value received by the buffer.
//	Buffer formatted value.
long CMicData::BuffNum(void)
{
	RES_DECLR(result);

	int	power	= 0x00;
	long	value = 0x00;
	long	my_buff_num	=	0x00;

	for(int index=0x00; index<CFwBuffer::Length(); index++)
	{															//	Process the current replay bytes.
		value = CFwBuffer::operator [](index);		//	Get byte from data array.
		switch(my_format)
		{											//	calculate the replay value.
		case	ENUM_UNDEF(DATA_FORMAT):	//	Undefined array of bytes.
			RES_FAILE(result);				//	No contents.
			break;

		case	FORM_CHR:						//	Single byte.
			my_buff_num	=	value;			//	set value.
			RES_CHECK(result, index<1);	//	Only 1 byte is allowed.
			break;

		case	FORM_INT:					//	Binary number.
		case	FORM_LONG:
			if(index < sizeof(my_buff_num))
			{
				value <<= (index*0x08);		//	Shift back to place.
				my_buff_num += value;		//	Cast to unsigned long and shift to place.
			}
			break;
		case	FORM_BYTE_ARR:					//	Array of bytes.
			my_buff_num	=	ULONG_MAX;		//	No contents.
			break;
		case	FORM_ASCII_TXT:				//	ASCII codes.
			RES_FAILE(result);
			break;
		case	FORM_BCD_NUM:					//	BCD data.
			my_buff_num *= 10;
			my_buff_num += (value>>0x08) & 0x0F;	//	value of MSB nibble.
			my_buff_num *= 10;
			my_buff_num += value & 0x0F;	//	value of LSB nibble.
			break;
		case	FORM_ASCII_DEC_NUM:			//	ASCII decimal.
			my_buff_num *= 10;
			my_buff_num += value - '0';	//	value of ASCII decimal digit.
			break;
		case	FORM_RVASCII_DEC_NUM:		//	Reversed ASCII decimal.
			value -= '0';
			power = index;
			my_buff_num += (long)(value * pow(10.0,power));
			break;

		case	FORM_SIZED_ARR:
			break;

		case	FORM_SIZED_ASCII_TXT:
			RES_FAILE(result);
			break;

		default:									//	unknown definition of replay type.
			RES_FAILE(result);				//	replay type not acceptable.
			break;
		}	//	end switch type.
	}	//	end for.
	RETURN(my_buff_num);
}

//-------------------------------------------------
//	Get a string containing the formatted
//	information received by the buffer.
STRING	CMicData::BuffStr(void)
{
	//return(my_buff_str);
	RES_DECLR(result);

	STR_DECLR(my_buff_str);
	unsigned long	my_buff_num	=	ULONG_MAX;		//	No contents.


	for(int index=0x00; index<CFwBuffer::Length(); index++)
	{																//	Process the current replay bytes.
		unsigned char value = CFwBuffer::operator [](index);	//	Get byte from data array.

		switch(my_format)
		{												//	calculate the replay value.
		case	FORM_ASCII_TXT:				//	ASCII codes.
			if(value==0x00)	value =	' ';	//	Avoid string terminator error.
			STR_ADD_CHAR(my_buff_str,(unsigned char) value);
			break;
		case	FORM_ASCII_DEC_NUM:			//	ASCII decimal.
			if(value==0x00)	value =	' ';	//	Avoid string terminator error.
			STR_ADD_CHAR(my_buff_str, (unsigned char) value);
			break;
		case	FORM_RVASCII_DEC_NUM:		//	Reversed ASCII decimal.
			if(value==0x00)	value =	' ';	//	Avoid string terminator error.
			STR_ADD_CHAR(my_buff_str, (unsigned char) value);
			break;
		case	FORM_SIZED_ARR:
			break;

		case	FORM_SIZED_ASCII_TXT:
			if(index==0){
				my_buff_str = NumToStr((long)value,true);
				my_buff_str += TAG_LNK_END;
			}
			else{
				STR_ADD_CHAR(my_buff_str, (unsigned char) value);
			}
			break;
		}	//	end switch type.
	}	//	end for.

	switch(my_format)
	{												//	calculate the replay value.
	case	ENUM_UNDEF(DATA_FORMAT):	//	Undefined array of bytes.
		break;

	case	FORM_CHR:						//	Single byte.
		my_buff_str = CMicString::GetNum(BuffNum(),true);
		break;

	case	FORM_INT:						//	Binary number.
	case	FORM_LONG:
		my_buff_str = CMicString::GetNum(BuffNum(),true);
		break;

	case	FORM_BYTE_ARR:					//	Array of bytes.
		my_buff_str = CFwBuffer::BufferText(true);
		break;
	case	FORM_ASCII_TXT:				//	ASCII codes.
		break;
	case	FORM_BCD_NUM:					//	BCD data.
		my_buff_str = CMicString::GetNum(BuffNum(),true);
		break;
	case	FORM_ASCII_DEC_NUM:			//	ASCII decimal.
		my_buff_str = CMicString::GetNum(BuffNum(),true);
		break;
	case	FORM_RVASCII_DEC_NUM:		//	Reversed ASCII decimal.
		my_buff_str = CMicString::GetNum(BuffNum(),true);
		break;

	case	FORM_SIZED_ARR:
		my_buff_str = CFwBuffer::BufferText(true);
	case	FORM_SIZED_ASCII_TXT:
		break;

	default:									//	unknown definition of replay type.
		RES_FAILE(result);
		break;
	}
	STR_RETURN(my_buff_str);
}


//	Clear the buffer contents.
FW_RESULT	CMicData::BuffClear(void)
{
	RES_DECLR(result);

	CFwBuffer::BufferClear();
	my_buff_num	=	ULONG_MAX;								//	No contents.

	RES_RETURN(result);	//	Reset contents.
}


//	Set Actual data
// the buffer contents coming threw external source.
//	Return the pointer to where the data was read.
unsigned int	CMicData::BuffSet(const char new_data[],unsigned int size, unsigned int data_index)
{
 	RES_DECLR(result);

	int power		= 0x00;
	unsigned long	value = 0x00;
	my_buff_num	=	ULONG_MAX;		//	No contents.

	if(	(my_size > 0x00)	&&						//	My buffer is not expexted to be empty.
			((data_index + my_size) <= size)	)	//	buffer is not shorter than expected bytes.
	{
		if(Allocate(my_size))					//	Resize the buffer and Initialize its contents.
		{
			my_buff_num = 0x00;

			for(int index=0x00; index<CFwBuffer::Length(); index++)
			{												//	Process the current replay bytes.
				value = new_data[data_index];		//	Get byte from data array.
				CFwBuffer::BufferSet(new_data[data_index],index);	//	Store to buffer.

				data_index++;
			 	switch(my_format)
			 	{												//	calculate the replay value.
					case	ENUM_UNDEF(DATA_FORMAT):					//	Un defined array of bytes.
						my_buff_num	=	ULONG_MAX;		//	No contents.
						break;

					case	FORM_CHR:						//	Single byte.
						my_buff_num	=	value;			//	set value.
						RES_CHECK(result, index<1);	//	Only 1 byte is allowed.
						break;

					case	FORM_INT:					//	Binary number.
					case	FORM_LONG:
						if(index < sizeof(my_buff_num))
						{
							value <<= (index*0x08);		//	Shift back to place.
							my_buff_num += value;		//	Cast to unsigned long and shift to place.
						}
			 			break;
					case	FORM_BYTE_ARR:					//	Array of bytes.
						my_buff_num	=	ULONG_MAX;		//	No contents.
			 			break;
					case	FORM_ASCII_TXT:				//	ASCII codes.
						if(value==0x00)	value =	' ';	//	Avoid string terminator error.
						break;

					case	FORM_BCD_NUM:					//	BCD data.
			 			my_buff_num *= 10;
			 			my_buff_num += (value>>0x08) & 0x0F;	//	value of MSB nibble.
			 			my_buff_num *= 10;
			 			my_buff_num += value & 0x0F;	//	value of LSB nibble.
						break;

					case	FORM_ASCII_DEC_NUM:			//	ASCII decimal.
			 			my_buff_num *= 10;
			 			my_buff_num += value - '0';	//	value of ASCII decimal digit.
			 			break;

			 		case	FORM_RVASCII_DEC_NUM:		//	Reversed ASCII decimal.
			 			value -= '0';
			 			power = index;
			 			my_buff_num += (long)(value * pow(10.0,power));
						break;

					case	FORM_SIZED_ARR:
						break;

					case	FORM_SIZED_ASCII_TXT:
						break;

			 		default:									//	unknown definition of replay type.
			 			result = false;					//	replay type not exceptable.
			 			break;
			 	}	//	end switch type.
			}	//	end for.
		}
		else{
			RES_FAILE(result);
		}	//	end if allocate.
	}
	else								//	Buffer could not be saved.
	{
		data_index += my_size;	//	Return index of data end.
	}
	return(data_index);
}






FW_RESULT	CMicData::DataGet(FW_UCHAR& val)
{
	RES_DECLR_INIT(result, (FORM_CHR == my_format));
	val = (FW_UCHAR)BuffNum();
	RES_CHECK(result, (BuffNum() == val));
	RES_RETURN(result);
}

FW_RESULT	CMicData::DataGet(UInt& num)
{
	RES_DECLR_INIT(result, (FORM_INT == my_format));
	num.val = (FW_INT)BuffNum();
	RES_CHECK(result, (BuffNum() == num.val));
	RES_RETURN(result);
}

FW_RESULT	CMicData::DataGet(ULong& num)
{
	RES_DECLR_INIT(result, (FORM_LONG == my_format));
	num.val = (FW_ULONG)BuffNum();
	RES_CHECK(result, (BuffNum() == num.val));
	RES_RETURN(result);
}





/********************************************************************\
*																							*
*								V a l i d a t i o n									*
*																							*
\********************************************************************/

//	Clear errors description.
FW_RESULT		CMicData::ErrorsClear(void)
{
	RES_DECLR(result);

	my_error = false;
	STR_CLEAR(my_errors);

	RES_RETURN(result);
}


//	Errors description.
STRING	CMicData::Errors(void)
{
	STR_DECLR(errors);
	
	STR_SET(errors,"Errs:");
	STR_ADD(errors,Title());
	STR_ADD(errors,my_errors);

	STR_RETURN(errors);
}

//	Add error to report.
FW_RESULT		CMicData::ErrorAdd(DATA_ERROR error)
{
	RES_DECLR(result);

	my_error = true;

	STR_ADD(my_errors,TAG_TXT_END);
	STR_ADD(my_errors,ENUM_NAME(DATA_ERROR,error));

	RES_RETURN(result);
}

//	Verify the buffer contents.
bool	CMicData::IsVerifayd(void)
{
	int	index = 0x00;
	bool	verified = true;
	
	my_error = RES_ERR;
	STR_CLEAR(my_errors);

	
	if((CFwBuffer::IsEmpty())||(my_size > CFwBuffer::Length()))
	{															//	Buffer missing or too small.
		verified = false;
		ErrorAdd(DATA_ERR_MISSNG);
	}
	else	if(my_size < CFwBuffer::Length())	//	Buffer too large for settings.
	{
		verified = false;
		ErrorAdd(DATA_ERR_OVERFLOW);
	}
	
	switch(my_format)
	{
		case	ENUM_UNDEF(DATA_FORMAT):							//	Un defined array of bytes.
			verified = false;					//	Any replay accepted.
			ErrorAdd(DATA_ERR_UNDEF);
			break;

		case	FORM_CHR:							//	Single byte.
		case	FORM_INT:						//	Binary number.
		case	FORM_LONG:
		case	FORM_BYTE_ARR:						//	Array of bytes.
		case	FORM_ASCII_TXT:					//	ASCII codes.
		case	FORM_BCD_NUM:						//	BCD data.
		case	FORM_ASCII_DEC_NUM:				//	ASCII decimal.
		case	FORM_RVASCII_DEC_NUM:			//	Reversed ASCII decimal.
			for(index=0x00;index<CFwBuffer::Length();index++)	{
				my_buff_num = CFwBuffer::operator [](index);	//	Get next byte.
			}
			break;
		default:									//	replay type is not defined.
			verified = false;					//	Any replay accepted.
			ErrorAdd(DATA_ERR_UNDEF);
			break;
	}
	my_error = !verified;

	return(verified);
}






/********************************************************************\
*																							*
*							D E S C R I P T I O N 									*
*																							*
\********************************************************************/
int	CMicData::Field(STRING page, DATA_FIELD field)
{
	return(GetNum(CMicString::GetItem(page, field - 1)));
}
STRING	CMicData::FieldGet(STRING page, DATA_FIELD field)
{
	return(CMicString::GetItem(page, field - 1));
}


//	Set the data according to formation string.
FW_RESULT		CMicData::Description(STRING page)
{
	RES_DECLR(result);
	unsigned	int	num	=	0x00;
	
//	if(LetPage(page))
//	{
		RES_CHECK(result, Title(FieldGet(page, DATA_TITLE)));
	
		STR_DECLR_INIT(settings, FieldGet(page, DATA_SETTINGS));	//	Set data formation segment as active segment.
		{
			num = GetNum(CMicString::GetLink(settings,0));						//	Get the number from the data string.
			RES_CHECK(result,Format((DATA_FORMAT)num));			//	Set data type.
			num = GetNum(CMicString::GetLink(settings,1));						//	Get the number from the data string.			
			RES_CHECK(result,Size(num));								//	Set data size.
		}
//	}
//	else{
//		RES_FAILE(result);
//	}

	RES_RETURN(result);
}

//	Return the page Description.
//	Containing:	title, formation, expected data, contents.
STRING	CMicData::Description()
{
	bool		close = false;
	STR_DECLR(replay);

	STR_ADD(replay, XML_NOD_BEGIN);
	STR_ADD(replay, ENUM_NAME(XML_PROP, XML_PROP_DATA) + Title() + XML_PROP_END);
	STR_ADD(replay, ENUM_NAME(XML_PROP, XML_PROP_TYPE) + NumToStr(my_format, false) + XML_PROP_END);
	STR_ADD(replay, ENUM_NAME(XML_PROP, XML_PROP_CONT) + BuffStr() + XML_PROP_END);
	STR_ADD(replay, XML_NOD_FINISH);

	return(replay);
}





/********************************************************************\
*																							*
*								O P E R A T O R S										*
*																							*
\********************************************************************/

//	Assignment operator.
CMicData*	CMicData::operator = (const CMicData*	pData)
{
	RES_DECLR(result);

	CFwBuffer::operator =((CFwBuffer*)pData);

	if(pData != NULL)
	{
		my_format	= pData->my_format;
		my_size	= pData->my_size;

		my_buff_num	= pData->my_buff_num;
		
		my_error		= pData->my_error;
		my_errors	= pData->my_errors;

		RES_SUCCESS(result);
	}	
	else
	{
		RES_CHECK(result,Clear());	
	}

	RES_ALERT(result);

	RES_CHECK(result, this->operator==(pData));

	PTR_RETURN(result ? this : NULL);
}

//	Buffer Assignment operator.
CMicData*	CMicData::operator = (const CFwBuffer*	pBuff)
{
	RES_DECLR(result);
	RES_CHECK(result,CFwBuffer::operator =(pBuff));	//	Set parent.

	RES_CHECK(result,Format(FORM_BYTE_ARR));					//	Data type is array.

	if(NULL == pBuff)
	{
		RES_CHECK(result,Size(0x00));									//	Expected size.
	}
	return(this);
}

//	Comperisson operator.
bool	CMicData::operator == (const CMicData*	pData)
{
	bool	result =	false;

	if(pData != NULL)
	{
		result = (CFwBuffer::operator == ((CFwBuffer*)pData));	//	Set buffer.

		result =	result && (my_format		==	pData->my_format);							//
		result =	result && (my_size		==	pData->my_size);
	}
	return(result);
}
