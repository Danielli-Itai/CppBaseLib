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
#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"






/********************************************************************\
*																							*
*									Include files										*
*																							*
\********************************************************************/
#include	HDR_FW_POINTERS
#include HDR_FW_DATA
#include	HDR_FW_TEXT_STR
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

	STR_INIT(my_cont_str);
	RES_CHECK(result,my_contents.Clear());	//	Clear the contents buffer.

	my_buff_num	=	FW_ULONG_MAX;					//	No contents.

	my_error		=	FALSE;
	STR_INIT(my_errors);

	STR_INIT(my_description);					//	Formation string.

	my_file_sep = TAG_FILE_SEP;

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
{
	return(my_format);
}
FW_RESULT	CMicData::Format(DATA_FORMAT format)
{
	RES_DECLR(result);

	RES_CHECK(result,ENUM_SET(DATA_FORMAT,my_format,format));

	RES_RETURN(result);
}

//	preset size and allocation for the contents buffer.
int	CMicData::Size()
{
	return(my_size);
}
FW_RESULT	CMicData::Size(DWORD new_size)
{
	RES_DECLR(result);

	my_size = new_size;
	RES_CHECK(result, my_size == new_size);

	RES_RETURN(result);
}		//	Set new size.

//-------------------------------------------------------
//	Contents string.
FW_RESULT	CMicData::ContentsStr(STRING new_cont)
{
	my_cont_str = new_cont;
	return(my_cont_str == new_cont);
}
//	data description according to the type.
STRING	CMicData::ContentsStr(void)
{
	return(my_cont_str);
}

unsigned long		CMicData::ContentsVal(void)
{
	return(CMicString::GetNum(my_cont_str));
}

//	Contents buffer.
CFwBuffer*	CMicData::Contents()
{
	return(&my_contents);		
}
FW_RESULT	CMicData::Contents(const CFwBuffer* pBuff)
{
	my_contents = pBuff;
	return(true);
}
//	Clears the buffer and sets the array as expected contents.
FW_RESULT	CMicData::ContentsSet(const unsigned char* p_data,unsigned int size)
{
	RES_DECLR(result);
	my_cont_str  = "";				//	No expected data.
	my_contents.BufferClear();		//	Clear expected buffer.


	if(p_data!=NULL)	{
		BuffClear();									//	Clear befor using the buffer.
		RES_CHECK(result, BuffSet(p_data, size, 0x00)<=size);
//		if(BuffSet(p_data, size, 0x00)<=size){	//	Sucsessfull translation.
//			my_cont_str = my_buff_str;				//	Keep expected contents description.
//		}
		my_contents.Buffer(p_data, size);			//	expected contents buffer.
		BuffClear();
	}
	RES_RETURN(result);
}

//	Build the contents buffer out of the contents string.
FW_RESULT	CMicData::Build(void)
{
	RES_DECLR(result);

	unsigned long	num = 0x00;								//	64 bit signed integer.
	unsigned char	byte = 0x00;
	int				index = 0x00;
	CMicString parer;
	my_contents.BufferClear();

	if((my_cont_str!="") && (my_size != 0x00))
	{
		RES_CHECK(result, my_contents.Allocate(my_size));
		
		switch(my_format)
		{
			case	FORM_CHR:
			case	FORM_PTR_CNTRL:
				num = CMicString::GetNum(my_cont_str,index - 0x01);
				if(num<0x00)	num = 0x00;
				byte = (unsigned char)(num & 0xFF);
				
				RES_CHECK(result, my_contents.Buffer(&byte,1));
				break;

			case	FORM_INT:						//	Binary number.
			case	FORM_PTR_CMND:				//	Command pointer.
			case	FORM_PTR_RMT:
				num = CMicString::GetNum(my_cont_str);
				for(index = 0x01; index <= my_size; index++){	//	
					if(num<0x00){
						num = 0x00;
					}
					byte = (unsigned char)((num>>((index-0x01)*0x08)) & 0xFF);
					if(index < sizeof num){
						RES_CHECK(result, my_contents.BufferSet(byte,(index-0x01)));
					}
					else{
						RES_CHECK(result, my_contents.BufferSet(0x00,(index-0x01)));
					}
				}
				break;

			case	FORM_BYTE_ARR:						//	Array of bytes.
				for(index = 0x00; index<my_size; index++)			//	fill the whole buffer.
				{
					num = CMicString::GetNum(parer.GetLink(my_cont_str, index));
					if(num < 0x00){										//	if out of range.
						num = 0x00;
					}
					byte = (unsigned char)num;							// convert to byte.
					RES_CHECK(result, my_contents.BufferSet(byte,index));	//	Add the byte to the contents buffer.
				}
			break;

			case	FORM_ASCII_TXT:					//	ASCII codes.
				for (index = 0; index <my_size; index++)
				{																//	Scan the string buffer.
					if(index < STR_LEN(my_cont_str)){
						byte = my_cont_str.GetAt(index);					//	Get byte.
					}
					else{
						byte = ' ';
					}
					RES_CHECK(result, my_contents.BufferSet(byte,index));	//	add to buffer.
				}
				break;

			case	FORM_BCD_NUM:						//	BCD data.
				for(index = 0x00; (index<my_size); index+=2)		//	Every 2 digitsstored in 1 byte.
				{
					num = CMicString::GetNum(CMicString::GetLink(my_cont_str,index));		//	Get first digit.
					if((num<0x00)||(num>0x09)){
						num = 0x00;											//	Check range.
					}
					byte = (unsigned char)((num & 0x0F) << 0x04);//	Set as MSB.

					num = CMicString::GetNum(CMicString::GetLink(my_cont_str,index+1));	//	Get second digit.
					if((num<0x00)||(num>0x09))	{
						num = 0x00;											//	Check range.
					}
					byte |= (unsigned char)(num & 0x0F);			//	Set as LSB.

					RES_CHECK(result, my_contents.BufferSet(byte,(my_size - index)));
				}
				break;


			case	FORM_ASCII_DEC_NUM:				//	ASCII decimal.
			case	FORM_RVASCII_DEC_NUM:			//	Reversed ASCII decimal.
				num = CMicString::GetNum(my_cont_str,0x00);	//	Get the number.
				if(num<0x00)	num = 0x00;			//	no minus values.
				for(index = 0x00; ((index<my_size)&&(index < sizeof num)); index++)
				{																	//	Scan the number bytes.
					byte = (unsigned char)((num>>index)&0xFF);		//	Get selected byte.
					RES_CHECK(result, my_contents.BufferSet(0x00,(my_size - index)));	//	Add byte to buffer.
				}
				break;
			default:									//	replay type is not defined.
				RES_FAILE(result);					//	Any replay accepted.
			break;
		}
	}
	RES_CHECK(result, BuffSet(my_contents.Buffer(),my_contents.Length(),0x00));// Store to built contents to buffer.
	
	RES_RETURN(result);
}





/********************************************************************\
*																							*
*									B U F F E R											*
*																							*
\********************************************************************/

//-------------------------------------------------
//	Get unsigned long value received by the buffer.
//	Buffer formatted value.
long CMicData::BuffNum(void)
{
	RES_DECLR(result);

	int power		= 0x00;
	long	value = 0x00;
	long	my_buff_num	=	0x00;

	for(int index=0x00; index<CFwBuffer::Length(); index++)
	{																//	Process the current replay bytes.
		value = CFwBuffer::operator [](index);		//	Get byte from data array.
		switch(my_format)
		{											//	calculate the replay value.
		case	ENUM_UNDEF(DATA_FORMAT):	//	Undefined array of bytes.
			RES_FAILE(result);				//	No contents.
			break;

		case	FORM_CHR:						//	Single byte.
		case	FORM_PTR_CNTRL:
			my_buff_num	=	value;			//	set value.
			RES_CHECK(result, index<1);	//	Only 1 byte is allowed.
			break;

		case	FORM_INT:					//	Binary number.
		case	FORM_LONG:
		case	FORM_PTR_CMND:
		case	FORM_PTR_RMT:
			if(index < sizeof(my_buff_num))
			{
				value <<= (index*0x08);		//	Shift back to place.
				my_buff_num += value;		//	Cast to unsigned long and shift to place.
			}
			break;
		case	FORM_BYTE_ARR:					//	Array of bytes.
			my_buff_num	=	FW_ULONG_MAX;		//	No contents.
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
	unsigned long	my_buff_num	=	FW_ULONG_MAX;		//	No contents.


	for(int index=0x00; index<CFwBuffer::Length(); index++)
	{																//	Process the current replay bytes.
		unsigned char value = CFwBuffer::operator [](index);	//	Get byte from data array.

		switch(my_format)
		{												//	calculate the replay value.
		case	FORM_ASCII_TXT:				//	ASCII codes.
			if(value==0x00)	value =	' ';	//	Avoid string terminator error.
			my_buff_str.AppendChar((unsigned char) value);
			break;
		case	FORM_ASCII_DEC_NUM:			//	ASCII decimal.
			if(value==0x00)	value =	' ';	//	Avoid string terminator error.
			my_buff_str.AppendChar((unsigned char) value);
			break;
		case	FORM_RVASCII_DEC_NUM:		//	Reversed ASCII decimal.
			if(value==0x00)	value =	' ';	//	Avoid string terminator error.
			my_buff_str.AppendChar((unsigned char) value);
			break;
		case	FORM_SIZED_ARR:
			break;

		case	FORM_SIZED_ASCII_TXT:
			if(index==0){
				my_buff_str = CMicString::GetNum((long)value, true);
				my_buff_str += TAG_LNK_END;
			}
			else{
				my_buff_str.AppendChar((unsigned char) value);
			}
			break;
		}	//	end switch type.
	}	//	end for.

	switch(my_format)
	{												//	calculate the replay value.
	case	ENUM_UNDEF(DATA_FORMAT):	//	Undefined array of bytes.
		break;

	case	FORM_CHR:						//	Single byte.
	case	FORM_PTR_CNTRL:
		my_buff_str = CMicString::GetNum(BuffNum(),true);
		break;

	case	FORM_INT:						//	Binary number.
	case	FORM_LONG:
	case	FORM_PTR_CMND:					//	Command pointer.
	case	FORM_PTR_RMT:
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
	my_buff_num	=	FW_ULONG_MAX;								//	No contents.

	RES_RETURN(result);	//	Reset contents.
}


//	Set Actual data
// the buffer contents coming threw external source.
//	Return the pointer to where the data was read.
unsigned int	CMicData::BuffSet(const unsigned char new_data[],unsigned int size, unsigned int data_index)
{
 	RES_DECLR(result);

	int power		= 0x00;
	unsigned long	value = 0x00;
	my_buff_num	=	FW_ULONG_MAX;		//	No contents.

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
						my_buff_num	=	FW_ULONG_MAX;		//	No contents.
						break;

					case	FORM_CHR:						//	Single byte.
					case	FORM_PTR_CNTRL:
						my_buff_num	=	value;			//	set value.
						RES_CHECK(result, index<1);	//	Only 1 byte is allowed.
						break;

					case	FORM_INT:					//	Binary number.
					case	FORM_LONG:
					case	FORM_PTR_CMND:
					case	FORM_PTR_RMT:
						if(index < sizeof(my_buff_num))
						{
							value <<= (index*0x08);		//	Shift back to place.
							my_buff_num += value;		//	Cast to unsigned long and shift to place.
						}
			 			break;
					case	FORM_BYTE_ARR:					//	Array of bytes.
						my_buff_num	=	FW_ULONG_MAX;		//	No contents.
			 			break;
					case	FORM_ASCII_TXT:				//	ASCII codes.
						if(value==0x00)	value =	' ';	//	Avoid string terminator error.
						my_cont_str.AppendChar((unsigned char) value);
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
						if(data_index==1){
							my_cont_str = CMicString::GetNum((long)value, true);
							my_cont_str += TAG_LNK_END;
						}
						else{
							my_cont_str.AppendChar((unsigned char) value);
						}
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

	 	switch(my_format)
	 	{												//	calculate the replay value.
			case	ENUM_UNDEF(DATA_FORMAT):	//	Undefined array of bytes.
					break;

			case	FORM_CHR:						//	Single byte.
			case	FORM_PTR_CNTRL:
				my_cont_str = CMicString::GetNum(my_buff_num,true);
				break;

			case	FORM_INT:						//	Binary number.
			case	FORM_PTR_CMND:					//	Command pointer.
			case	FORM_PTR_RMT:
				my_cont_str = CMicString::GetNum(my_buff_num,true);
	 			break;

			case	FORM_BYTE_ARR:					//	Array of bytes.
				my_cont_str = CFwBuffer::BufferText(true);
	 			break;
			case	FORM_ASCII_TXT:				//	ASCII codes.
				break;
			case	FORM_BCD_NUM:					//	BCD data.
				my_cont_str = CMicString::GetNum(my_buff_num,true);
				break;
			case	FORM_ASCII_DEC_NUM:			//	ASCII decimal.
				my_cont_str = CMicString::GetNum(my_buff_num,true);
	 			break;
	 		case	FORM_RVASCII_DEC_NUM:		//	Reversed ASCII decimal.
				my_cont_str = CMicString::GetNum(my_buff_num,true);
				break;

			case	FORM_SIZED_ARR:
				my_cont_str = CFwBuffer::BufferText(true);
			case	FORM_SIZED_ASCII_TXT:
				break;

			default:									//	unknown definition of replay type.
			 	my_cont_str = _T("");
				RES_FAILE(result);
			 	break;
		}
	}
	else								//	Buffer could not be saved.
	{
		data_index += my_size;	//	Return index of data end.
	}
	return(data_index);
}



//	File connection.
bool		CMicData::FileEna(void)
{
	return(my_file_sep != TAG_EMPTY);							
}
FW_RESULT		CMicData::	FileSepCode(STRING sep)
{
	RES_DECLR(result);

	my_file_sep = (char)CMicString::GetNum(sep);
	if(STR_CMP(my_file_sep,TAG_EMPTY)){
		STR_SET(my_file_sep, TAG_SPACE);
	}
	
	RES_RETURN(result);
}


STRING	CMicData::FileTitle(bool is_first)
{
	STR_DECLR(tmp_str);

	STR_SET(tmp_str,Title());

	if(is_first==false)
	{
		STR_ADD(tmp_str,my_file_sep);
	}
	
	STR_RETURN(tmp_str);
}

STRING	CMicData::FileCont(bool is_first)
{
	STR_DECLR(tmp_str);

	STR_SET(tmp_str, my_cont_str);
	
	if(is_first==false)
	{
		STR_ADD(tmp_str,my_file_sep);
	}
	
	STR_RETURN(tmp_str);
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
	num.val = (FW_UINT)BuffNum();
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
	
	my_error = FALSE;
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

		case	FORM_BYTE_ARR:						//	Array of bytes.
			for(index=0x00;index<CFwBuffer::Length();index++)	{
				my_buff_num = CFwBuffer::operator [](index);	//	Get next byte.
			}
			if(verified && (my_contents.IsEmpty()==false) && (my_size>0x00) && (CFwBuffer::Length()==my_size))
			{
				if((my_contents == (CFwBuffer*)this)==false) {	//	Contents missmatch.
					ErrorAdd(DATA_ERR_CONTENTS);
				}
			}
			break;

		case	FORM_CHR:							//	Single byte.
		case	FORM_PTR_CNTRL:
		case	FORM_PTR_CMND:					//	Command pointer.
		case	FORM_PTR_RMT:
		case	FORM_INT:						//	Binary number.
		case	FORM_LONG:
//		case	FORM_BYTE_ARR:						//	Array of bytes.
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
int	CMicData::Field(DATA_FIELD field)
{
	return(CMicString::GetNum(CMicString::GetItem(my_description, field - 1)));
}
STRING	CMicData::FieldGet(DATA_FIELD field)
{
	return(CMicString::GetItem(my_description, field - 1));
}


//	Set the data according to formation string.
FW_RESULT		CMicData::Description(STRING page)
{
	RES_DECLR(result);
	unsigned	int	num	=	0x00;
	
	STR_SET(my_description, page);
	RES_CHECK(result, Title(FieldGet(DATA_TITLE)));
	
	STR_DECLR_INIT(settings, FieldGet(DATA_SETTINGS));	//	Set data formation segment as active segment.
	{
		num = CMicString::GetNum(CMicString::GetLink(settings,0));						//	Get the number from the data string.
		RES_CHECK(result,Format((DATA_FORMAT)num));			//	Set data type.
		num = CMicString::GetNum(CMicString::GetLink(settings,1));						//	Get the number from the data string.			
		RES_CHECK(result,Size(num));								//	Set data size.
	}

	RES_CHECK(result,ContentsStr(FieldGet(DATA_CONTNTS)));	//	Set contents string.
	RES_CHECK(result,FileSepCode(FieldGet(DATA_FILESEP)));	//	Load file separation code.

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
	STR_ADD(replay, ENUM_NAME(XML_PROP, XML_PROP_TYPE) + CMicString::GetNum(my_format, false) + XML_PROP_END);
	STR_ADD(replay, ENUM_NAME(XML_PROP, XML_PROP_CONT) + BuffStr() + XML_PROP_END);
	STR_ADD(replay, XML_NOD_FINISH);

	return(replay);
}
//	Return the page Description.
//	Containing:	title, formation, expected data, contents.
STRING	CMicData::Description(bool hex,bool title, bool format,bool contents,bool buffer)
{
	bool		close = false;
	STR_DECLR(replay);

	if(title)
	{
		STR_SET(replay,Title());
		close = true;
	}

	if(format)
	{
		if(close){
			STR_ADD(replay,TAG_ITM_END);				//	Close previous session.
		}
		STR_ADD(replay, "t[" + CMicString::GetNum(my_format,hex) + "]" + TAG_LNK_END);	//	type.
		STR_ADD(replay, "s[" + CMicString::GetNum(my_size,hex)	+ "]");	//	Expected Size.
		close = true;
	}

	if(contents)
	{
		if(close){
			replay+= TAG_ITM_END;						//	Close previous session.
		}
		STR_ADD(replay,my_cont_str);					//	Expected contents.
		close = true;
	}

	if(buffer)
	{
		if(close){
			STR_ADD(replay, TAG_ITM_END);				//	Close previous session.
		}
		
		STR_ADD(replay,BufferText(hex));
		if(my_error){
			STR_ADD(replay,Errors());
		}
		close = true;
	}

	if(format)
	{
		if(close){
			STR_ADD(replay, TAG_ITM_END);				//	Close previous session.
		}
		STR_ADD(replay, "f[" + CMicString::GetNum(*my_file_sep.GetBuffer(), hex) + "]");
	}
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

		my_cont_str	= pData->my_cont_str;
		my_contents = &(pData->my_contents);

		my_buff_num	= pData->my_buff_num;
		
		my_file_sep	= pData->my_file_sep;
		my_file_cont= pData->my_file_cont;

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

