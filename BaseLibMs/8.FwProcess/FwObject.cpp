/********************************************************************\
*																							*
*								Object Configuration									*
*																							*
\********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





/********************************************************************\
*																							*
*									Include Files										*
*																							*
\********************************************************************/
#include	HDR_FW_DEBUGGING
#include	HDR_FW_TEXT_STR
#include	HDR_FW_OBJECT





/********************************************************************\
*																							*
*									Definitions											*
*																							*
\********************************************************************/
#define	LOG_PATH_SEP		"/"
#define	LOG_MESG_SEP		":"




/********************************************************************\
*																							*
*									Properties											*
*																							*
\********************************************************************/
STRING	CFwObject::Name()
{
	STR_RETURN(my_name);
}





/********************************************************************\
*																							*
*									Class													*
*																							*
\********************************************************************/
CFwObject::CFwObject()
:	my_pLog(PTR_NULL)
,	my_path(STR_EMPTY)
,	my_name(STR_EMPTY)
{
}

CFwObject::CFwObject(FW_OBJ_PRMS_LIST)
:	my_pLog(PTR_NULL)
,	my_path(STR_EMPTY)
,	my_name(STR_EMPTY)
{
	PTR_SET(my_pLog, pLog);

	if(STR_NOT_EMPTY(path)){
		STR_SET(my_path, path);
		STR_ADD(my_path, LOG_PATH_SEP);
	}
	STR_ADD(my_path, name);

	STR_SET(my_name, name);
}


CFwObject::~CFwObject()
{
	PTR_CLR(my_pLog);
}





/********************************************************************\
*																							*
*										Log												*
*																							*
\********************************************************************/
FW_RESULT	CFwObject::LogWrite(FW_RESULT res_log, STRING msg)
{
	RES_DECLR(result);
	if(PTR_NOT_NULL(my_pLog)){
		RES_CHECK(result, my_pLog->Write(my_path, res_log, msg));
	}
	RES_RETURN(result);
}

FW_RESULT	CFwObject::LogWrite(FW_RESULT res_log, STRING msg, FW_ULONG64 num)
{
	RES_DECLR_INIT(result, PTR_NOT_NULL(my_pLog));
	if(RES_TRUE(result))	
	{
		STR_ADD(msg, ":");
		STR_ADD(msg, NumToStr(num, true));
		RES_CHECK(result, LogWrite(result, msg));
	}
	RES_RETURN(result);
}

FW_RESULT	CFwObject::LogWrite(FW_RESULT res_log, STRING msg, FW_CHAR* buff, FW_ULONG size)
{
	RES_DECLR_INIT(result, PTR_NOT_NULL(my_pLog));
	if(RES_TRUE(result))	
	{
		STR_ADD(msg, ":");
		STR_ADD(msg, CMicString::GetArr(buff, size, true));
		RES_CHECK(result, LogWrite(result, msg));
	}
	RES_RETURN(result);
}

FW_RESULT	CFwObject::LogShow()
{
	RES_DECLR_INIT(result, PTR_NOT_NULL(my_pLog));
	if(RES_TRUE(result))	RES_CHECK(result, my_pLog->Show());
	RES_RETURN(result);
}
FW_RESULT	CFwObject::LogClear()
{
	RES_DECLR_INIT(result, PTR_NOT_NULL(my_pLog));
	if(RES_TRUE(result))	RES_CHECK(result, my_pLog->Clear());
	RES_RETURN(result);
}

