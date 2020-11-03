/***********************************************************************\
*																								*
*										D a t a   I t e m									*
*																								*
\***********************************************************************/
#ifndef FW_DATA_HPP
#define FW_DATA_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





/***********************************************************************\
*																								*
*										Include Files										*
*																								*
\***********************************************************************/
#include	<math.h>
#include HDR_FW_BUFFER
#include HDR_FW_TEXT_STR









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
	FORM_CHR						=	0x01	\
	,FORM_INT					=	0x02	\
	,FORM_LONG					=	0x03	\
	,FORM_BYTE_ARR				=	0x04	\
	,FORM_ASCII_TXT			=	0x05	\
	,FORM_BCD_NUM				=	0x06	\
	,FORM_ASCII_DEC_NUM		=	0x07	\
	,FORM_RVASCII_DEC_NUM	=	0x08	\
	,FORM_SIZED_ARR			=	0x09	\
	,FORM_SIZED_ASCII_TXT	=	0x0A	\
	/*DATA_FORMAT_FIELDS*/
#define DATA_FORMAT_NAMES	\
	"FORM_CHR"					\
	,"FORM_INT"					\
	,"FORM_LONG"				\
	,"FORM_BYTE_ARR"			\
	,"FORM_ASCII_TXT"			\
	,"FORM_BCD_NUM"			\
	,"FORM_ASCII_DEC_NUM"	\
	,"FORM_RVASCII_DEC_NUM"	\
	,"FORM_SIZED_ARR"			\
	,"FORM_SIZED_ASCII_TXT"	\
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

#ifdef	OLD_CODE
class CMicData:	public CFwBuffer
#else
class CMicData:	public CFwBuffer//, protected CMicString 
#endif
{
	//	System methods.
	private:	FW_RESULT		Init(void);
	public:	FW_RESULT		Clear(void);

	public:					CMicData();
	public:	virtual		~CMicData();

	//	Title describing the data meaneing.
	private:	int			Field(STRING page, DATA_FIELD field);
	private:	STRING		FieldGet(STRING page, DATA_FIELD field);

	//	Data type - Buffer, Time, File...	
	private:	DATA_FORMAT		my_format;		//	Data format - Buffer, Time, File...
	public:	DATA_FORMAT		Format();
	public:	FW_RESULT			Format(DATA_FORMAT format);

	//	preset size.
	private:	FW_INT			my_size;		//	pre set size.
	public:	FW_INT			Size();
	public:	FW_RESULT			Size(FW_INT new_size);

	//	Actual buffer.
	private:	long 				my_buff_num;
	public:	long				BuffNum(void);
	public:	STRING			BuffStr(void);
	public:	FW_RESULT			BuffClear(void);
	public:	unsigned int	BuffSet(const char data[],unsigned int size, unsigned int data_index);

	public:	FW_RESULT			DataGet(FW_UCHAR& num);
	public:	FW_RESULT			DataGet(UInt& num);
	public:	FW_RESULT			DataGet(ULong& num);

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
	public:	STRING			Description();
	public:	FW_RESULT			Description(STRING formation);


	//	Operators.
	public:	CMicData*		operator = (const CFwBuffer*	pBuff);
	public:	CMicData*		operator = (const CMicData*		pData);
	public:	bool				operator == (const CMicData*		pData);
};	
#endif // !FW_DATA_HPP
