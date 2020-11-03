/***********************************************************************\
*																								*
*										D a t a   I t e m									*
*																								*
\***********************************************************************/
#ifndef DATA_ITEM_H
#define DATA_ITEM_H
#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





/***********************************************************************\
*																								*
*										Include Files										*
*																								*
\***********************************************************************/
#include	<math.h>
#include	HDR_FW_ENUMS
#include HDR_FW_BUFFER
#include HDR_FW_STRING





/***********************************************************************\
*																								*
*										Definitions											*
*																								*
\***********************************************************************/

#define	DATA_BUFF_SIZE					0xFF

//	Data formation.
#define	DATA_FIELD_FIELDS	\
	DATA_TITLE					\
	,DATA_SETTINGS				\
	,DATA_CONTNTS				\
	,DATA_BUFFER				\
	,DATA_FILESEP				\
	/*DATA_FIELDS_FIELDS*/
#define	DATA_FIELD_NAMES	\
	"DATA_TITLE"				\
	,"DATA_SETTINGS"			\
	,"DATA_CONTNTS"			\
	,"DATA_BUFFER"				\
	,"DATA_FILESEP"			\
	/*DATA_FIELD_NAMES*/
ENUM_DEFINE(DATA_FIELD,DATA_FIELD_FIELDS);

#define	FORM_INT_SIZE			0x02

//	Data formats.
#define DATA_FORMAT_FIELDS	\
	FORM_CHR						=	0x01	/*	param	,	byte			*/	\
	,FORM_INT					=	0x02	/*	data	, 	BinNum		*/	\
	,FORM_LONG					=	0x03	\
	,FORM_PTR_CMND				=	0x04	/*	data	, 	BinNum		*/	\
	,FORM_PTR_RMT				=	0x05	/*	data	, 	BinNum		*/	\
	,FORM_BYTE_ARR				=	0x06	/*	data	,	Byte array.	*/	\
	,FORM_ASCII_TXT			=	0x07	/*	data	,	Byte array.	*/	\
	,FORM_BCD_NUM				=	0x08	/*	data	,	Byte array.	*/	\
	,FORM_ASCII_DEC_NUM		=	0x09	/*	data	,	Byte array.	*/	\
	,FORM_RVASCII_DEC_NUM	=	0x0A	/*	data	,	Byte array.	*/	\
	,FORM_SIZED_ARR			=	0x0B	/*	data	,	Sized array	*/	\
	,FORM_SIZED_ASCII_TXT	=	0x0D	/*	data	,	Sized array	*/	\
	,FORM_PTR_TITLE			=	0x0E	/*	Title pointer			*/	\
	,FORM_PTR_CNTRL			=	0x0F	/*	Ui Control pointer	*/	\
	/*DATA_FORMAT_FIELDS*/
#define DATA_FORMAT_NAMES	\
	"FORM_CHR"					\
	,"FORM_INT"					\
	,"FORM_LONG"				\
	,"FORM_PTR_CMND"			\
	,"FORM_PTR_RMT"			\
	,"FORM_BYTE_ARR"			\
	,"FORM_ASCII_TXT"			\
	,"FORM_BCD_NUM"			\
	,"FORM_ASCII_DEC_NUM"	\
	,"FORM_RVASCII_DEC_NUM"	\
	,"FORM_SIZED_ARR"			\
	,"FORM_SIZED_ASCII_TXT"	\
	,"FORM_PTR_TITLE"			\
	,"FORM_PTR_CNTRL"			\
	/*DATA_FORMAT_NAMES*/
	ENUM_DEFINE(DATA_FORMAT,DATA_FORMAT_FIELDS);

//	Error names.
#define	DATA_ERROR_FIELDS	\
	DATA_ERR_MISSNG			\
	,DATA_ERR_OVERFLOW		\
	,DATA_ERR_CONTENTS		\
	,DATA_ERR_FORMAT			\
	,DATA_ERR_UNDEF			\
	,DATA_ERR_UNEXP			\
	/*DATA_ERROR_FIELDS	*/
#define	DATA_ERROR_NAMES	\
	"Missing Data"				/* There is no enogh data while a data is expected.	*/	\
	,"More data than buffer"/* There is more data than expected.						*/	\
	,"Contents"					/* Data contents does not match expected contents.		*/	\
	,"Unknown format"			/* Data type is unknown.										*/	\
	,"Undefined data"			/* Data received but not predefined.						*/	\
	,"Unexpected item"				/* Unexpected data item.								*/	\
	/*DATA_ERROR_NAMES*/
ENUM_DEFINE(DATA_ERROR,DATA_ERROR_FIELDS);









/***********************************************************************\
*																								*
*												Class											*
*																								*
\***********************************************************************/

class CMicData:	public CFwBuffer
{
	//	System methods.
	private:	FW_RESULT		Init(void);
	public:	FW_RESULT		Clear(void);

	public:					CMicData();
	public:	virtual		~CMicData();

	//	Data type - Buffer, Time, File...	
	private:	DATA_FORMAT		my_format;		//	Data format - Buffer, Time, File...
	public:	DATA_FORMAT		Format();
	public:	FW_RESULT			Format(DATA_FORMAT format);

	//	preset size.
	private:	int				my_size;		//	pre set size.
	public:	int				Size();
	public:	FW_RESULT			Size(DWORD new_size);

	//	Expected Contents.
	private:	STRING				my_cont_str;			//	contents string.
	private:	CFwBuffer			my_contents;			//	contains the expected data contents.
	public:	FW_RESULT				ContentsStr(STRING new_cont);
	public:	STRING				ContentsStr(void);
	public:	unsigned long		ContentsVal(void);
	public:	CFwBuffer*	Contents(void);
	private:	FW_RESULT				Contents(const CFwBuffer* pBuff);
	public:	FW_RESULT				ContentsSet(const unsigned char* p_data, unsigned int size);
	public:	FW_RESULT				Build(void);

	public:	FW_RESULT				ContentsIsEmpty(void)	{		return(my_contents.IsEmpty());	}

	//	Actual buffer.
	private:	long 				my_buff_num;
	public:	long				BuffNum(void);
	public:	STRING			BuffStr(void);
	public:	FW_RESULT			BuffClear(void);
	public:	unsigned int	BuffSet(const unsigned char data[],unsigned int size, unsigned int data_index);

	public:	FW_RESULT			DataGet(FW_UCHAR& val);
	public:	FW_RESULT			DataGet(UInt& num);
	public:	FW_RESULT			DataGet(ULong& num);

	//	File connection.
	private:	STRING			my_file_sep;
	public:	bool				FileEna(void);
	private:	FW_RESULT			FileSepCode(STRING sep);

	private:	STRING			my_file_cont;
	public:	STRING			FileTitle(bool is_first);
	public:	STRING			FileCont(bool is_first);


	//	validation compare Expected with Actual.
	private:	bool				my_error;
	public:	FW_RESULT			Error(void)				{	return(my_error);					}
	private:	STRING			my_errors;
	public:	STRING			Errors(void);
	public:	FW_RESULT			ErrorsClear(void);
	public:	FW_RESULT			IsVerifayd(void);
	private:	FW_RESULT			ErrorAdd(DATA_ERROR error);

	//	Description - Formation string.
	private:	STRING			my_description;			//	Contents format string.
	private:	int				Field(DATA_FIELD field);
	private:	STRING			FieldGet(DATA_FIELD field);
	public:	STRING			Description();
	public:	FW_RESULT			Description(STRING formation);
	public:	STRING			Description(bool hex,bool title,bool format,bool contents,bool buffer);

	//	Operators.
	public:	CMicData*		operator = (const CFwBuffer*	pBuff);
	public:	CMicData*		operator = (const CMicData*		pData);
	public:	bool				operator == (const CMicData*		pData);
};
#endif
