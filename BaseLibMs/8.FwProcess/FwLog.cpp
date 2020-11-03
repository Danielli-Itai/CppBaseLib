/********************************************************************\
*																							*
*										Log Filer										*
*																							*
\********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





/********************************************************************\
*																							*
*									Include Files										*
*																							*
\********************************************************************/
#include	HDR_FW_SINC
#include	HDR_FW_DATA_LIST
#include	HDR_FW_LOG






/********************************************************************\
*																							*
*									Definitions											*
*																							*
\********************************************************************/





/********************************************************************\
*																							*
*										Class												*
*																							*
\********************************************************************/
CFwLogConsol::CFwLogConsol()
	:	my_file(FILE_TYPE_LOG)
{
}

CFwLogConsol::~CFwLogConsol()
{
}




/********************************************************************\
*																							*
*									Implementation										*
*																							*
\********************************************************************/
FW_RESULT	CFwLogConsol::Clear()
{
	RES_RETURN(my_file.Clear());
}

FW_RESULT	CFwLogConsol::Show()
{
	RES_RETURN(my_file.Show());
}

FW_RESULT	CFwLogConsol::Write(STRING path, FW_RESULT result, STRING msg)
{
	STR_DECLR_INIT(log_line, path);
	STR_ADD(log_line, LOG_RECORD_SEP);

	STR_ADD(log_line, result ? STR_OK: STR_RES_ERR);
	STR_ADD(log_line, LOG_RECORD_SEP);

	STR_ADD(log_line, msg);
	STR_ADD(log_line, LOG_LINE_END);

	printf("%s\n", log_line.c_str());

	RES_RETURN(my_file.Write(log_line));
}


//#include HDR_MIC_TIME
//#include	HDR_FW_LOG
//#include	HDR_FW_XML_TYPES





///***********************************************************************\
//*																								*
//*											Include Files									*
//*																								*
//\***********************************************************************/
//	#define	LOG_FILE_NAME	"LogFile"
//
//
//
//
//
//	/***********************************************************************\
//	*																								*
//	*											Globals											*
//	*																								*
//	\***********************************************************************/
//	ENUM_NAMES_CREATE(LOG_TYPE,LOG_TYPE_NAMES);
//
//
//
//
//
//
//
//
//	STRING	CFwLog::Title(void)
//	{
//		return(my_LogFile.Title());
//	}
//	FW_RESULT	CFwLog::Title(STRING new_name)
//	{
//		RES_DECLR(result);
//
//		STR_SET(my_title, new_name);
//		STR_DECLR_INIT(title, my_title);
//
//	//	CTime t = CTime::GetCurrentTime();
//	//	STR_ADD(title, t.Format(" %d-%m-%Y %H.%M.%S"));
//
//		RES_CHECK(result,my_LogFile.NameLet(title));
//
//		RES_CHECK(result,STR_NOT_EMPTY(new_name));
//
//		RES_RETURN(result);
//	}
//
//
//	STRING	CFwLog::PathGet(void)
//	{
//		return(my_LogFile.PathGet());
//	}
//	FW_RESULT	CFwLog::PathLet(STRING new_path)
//	{
//		RES_DECLR(result);
//
//		RES_CHECK(result, my_LogFile.PathLet(new_path));
//		RES_CHECK(result, my_LogFile.TypeCode(FILE_TYPE_PROJECT_LOG));
//
//		RES_CHECK(result, my_LogFile.Open());
//	//	RES_CHECK(result, my_LogFile.Close());
//
//		RES_CHECK(result,STR_NOT_EMPTY(new_path));
//
//		RES_RETURN(result);
//	}
//
//
//
//
//
//
//
//
//
//
//	/***********************************************************************\
//	*																								*
//	*												Class											*
//	*																								*
//	\***********************************************************************/
//	#ifdef	LOG_FILE
//	#else
//		FW_RESULT	CFwLog::LogEnable(bool ToFile,	bool LogString, bool LogResult)
//		{
//			RES_DECLR(result);
//
//			my_StringsLog	=	LogString;	//	Set logging modes.
//			my_ResultsLog	=	LogResult;
//			my_LogToFile = ToFile;
//
//			RES_RETURN(result);
//		}
//	#endif
//
//	//	Construct a logger.
//	CFwLog::CFwLog()
//	{
//		RES_DECLR(result);
//
//		MUTX_INIT(LogLock);
//	
//		STR_INIT(my_title);
//	//	ENUM_INIT(LOG_TYPE, my_logType);
//
//		my_ListMax			=	MAX_LIST_SIZE_LOG_STRING;
//		my_ListPosition	=	NULL;
//
//		Title(LOG_FILE_NAME);
//		PathLet(MicFile::GetWorkingDirectory());
//
//	#ifdef	LOG_FILE
//	#else
//		RES_CHECK(result, LogEnable(true, true, false));
//	#endif
//
//		RES_ALERT(result);
//		return;
//	}
//
//
//	CFwLog::~CFwLog()
//	{
//		RES_DECLR(result);
//
//	//	RES_CHECK(result,my_LogFile.Clear());
//	//	RES_CHECK(result,my_DataFile.Clear());
//
//		RES_CHECK(result,ListClear());
//
//		RES_ALERT(result);
//	}
//
//
//
//
//	FW_RESULT CFwLog::FileAdd(STRING newline)
//	{
//		RES_DECLR(result);
//		MUTX_LOCK(LogLock);
//
//	#ifdef	LOG_FILE
//		if(STR_NOT_EMPTY(newline))
//	#else
//		if(my_LogToFile && STR_NOT_EMPTY(newline))
//	#endif
//		{															//	Data exists ?.
//			STR_DECLR(line);
//			line.Format("%s\n\r",newline);				//	Add the string to the file.
//			RES_CHECK(result, my_LogFile.StringAppend(line));
//	//		RES_CHECK(result, my_LogFile.StringAppend(newline));
//		}
//		if(my_LogFile.Size().val > FILE_MAX_SIZE){
//			RES_CHECK(result, Title(my_title));
//		}
//
//		MUTX_UNLOCK(LogLock);
//		RES_RETURN(result);
//	}
//
//
//
//
//
//	/***********************************************************************\
//	*																								*
//	*									A d d   t o   L o g									*
//	*																								*
//	\***********************************************************************/
//	FW_RESULT CFwLog::ListAdd(STRING newline)
//	{
//		RES_DECLR(result);
//	#ifdef	LOG_FILE
//		MUTX_LOCK(LogLock);
//	#endif
//	//	STR_DECLR_INIT(Line, newline);
//
//
//		RES_ALERT(ListString.GetCount() < my_ListMax);
//		if(ListString.GetCount() > my_ListMax){		//	Check if list is too long.
//			PTR_DECLR_INIT(STRING, pLine, ListString.RemoveHead());	
//			PTR_DESTROY(pLine);
//		}
//
//		PTR_DECLR_NEW(STRING, pLine);	
//		STR_SET(*pLine, newline);
//
//		FW_LIST_ADD_TAIL(ListString, pLine);							//	Add to tail.
//
//	#ifdef	LOG_FILE
//		MUTX_UNLOCK(LogLock);								//	Release.
//	#endif
//		RES_RETURN(result);
//	}
//
//
//	STRING	CFwLog::LineHeader(LOG_TYPE logType)
//	{
//	//	ENUM_SET(LOG_TYPE, my_logType, logType);
//		STR_DECLR_INIT(str, XML_NOD_BEGIN);
//		STR_ADD(str, ENUM_NAME(LOG_TYPE, logType));
//		STR_ADD(str, STR_SPACE);
//		STR_ADD(str, ENUM_NAME(XML_PROP, XML_PROP_TIME));
//		CTime t = CTime::GetCurrentTime();
//		STR_ADD(str, t.Format(DATE_TIME_FORMAT/*"%d/%m/%Y %H:%M:%S"*/) + XML_PROP_END);
//	
//		STR_RETURN(str) 
//	}
//	STRING	CFwLog::LineTrailer()
//	{
//		STR_DECLR_INIT(str, XML_NOD_FINISH);
//
//		STR_RETURN(str) 
//	}
//	FW_RESULT CFwLog::LineAdd(LOG_TYPE logType, STRING newline)
//	{
//		RES_DECLR(result);
//		STR_DECLR(logStr);
//
//		STR_ADD(logStr, LineHeader(logType));
//		STR_ADD(logStr, STR_SPACE);
//		STR_ADD(logStr, newline);
//		STR_ADD(logStr, STR_SPACE);
//		STR_ADD(logStr, LineTrailer());
//
//		RES_CHECK(result, ListAdd(logStr));
//	#ifdef	LOG_FILE
//	#else
//		if(LOG_DATA != logType){
//			RES_CHECK(result, FileAdd(logStr));	//	Add the string to the file.
//		}
//	#endif
//		RES_RETURN(result);
//	}
//
//
//
//	//*	Add a String to the Log list.
//
//	#ifdef	LOG_FILE
//		FW_RESULT CFwLog::AddProc(STRING path, STRING text)
//		{
//			STR_DECLR_INIT(new_line, XmlPropGet(XML_PROP_PATH, path));
//			STR_ADD(new_line, STR_SPACE);
//
//			STR_ADD(new_line, text);
//
//			RES_RETURN(LineAdd(LOG_PROC, new_line));
//		}
//	#else
//		FW_RESULT CFwLog::AddProc(STRING text)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			if(my_StringsLog)
//			{
//				RES_CHECK(result,LineAdd(LOG_PROC, text));
//			}
//			MUTX_UNLOCK(LogLock);								//	Release.
//			RES_RETURN(result);
//		}
//	#endif
//
//	//*	Add a String to the Log list.
//	#ifdef	LOG_FILE
//		FW_RESULT CFwLog::AddData(STRING path, STRING data)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			STR_DECLR_INIT(log_str, XmlPropGet(XML_PROP_PATH, path));
//			STR_ADD(log_str, STR_SPACE);
//
//			STR_ADD(log_str, data);
//
//			RES_CHECK(result,LineAdd(LOG_DATA, log_str));
//
//			MUTX_UNLOCK(LogLock);								//	Release.
//			RES_RETURN(result);
//		}
//	#else
//		FW_RESULT CFwLog::AddData(STRING data)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			if(my_StringsLog)
//			{
//				RES_CHECK(result,LineAdd(LOG_DATA, data));
//			}
//			MUTX_UNLOCK(LogLock);								//	Release.
//			RES_RETURN(result);
//		}
//	#endif
//	//*	Add a result message to the log.
//	#ifdef	LOG_FILE
//		STRING CFwLog::ResultStr(STRING name, bool ok)
//		{
//			STR_DECLR(newline);
//
//			STR_ADD(newline, name);
//			STR_ADD(newline, STR_SPACE);
//
//			if(ok){
//				STR_ADD(newline, XmlPropGet(PROP_RESULT, STR_OK));
//			}
//			else{
//				STR_ADD(newline, XmlPropGet(PROP_RESULT, STR_RES_ERR));
//			}
//
//			STR_RETURN(newline);
//		}
//
//		FW_RESULT CFwLog::AddResult(STRING path, STRING name, bool ok)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			STR_DECLR_INIT(resStr, XmlPropGet(XML_PROP_PATH, path));
//			STR_ADD(resStr, STR_SPACE);
//
//			STR_ADD(resStr, ResultStr(name, ok));
//			RES_CHECK(result,LineAdd(LOG_RES, resStr));
//
//			MUTX_UNLOCK(LogLock);
//			RES_RETURN(result);
//		}
//	#else
//		FW_RESULT CFwLog::AddResult(STRING name, bool ok)
//		{
//			RES_DECLR(result);
//			STR_DECLR(newline);
//
//			MUTX_LOCK(LogLock);
//
//			if(my_ResultsLog)
//			{
//				STR_ADD(newline, name);
//				STR_ADD(newline, STR_SPACE);
//
//				if(ok){
//					STR_ADD(newline, XmlPropGet(PROP_RESULT, STR_OK));
//				}
//				else{
//					STR_ADD(newline, XmlPropGet(PROP_RESULT, STR_RES_ERR));
//				}
//
//				RES_CHECK(result,LineAdd(LOG_RES, newline));
//			}
//
//			MUTX_UNLOCK(LogLock);
//			RES_RETURN(result);
//		}
//	#endif
//
//	#ifdef	LOG_FILE
//		FW_RESULT	CFwLog::AddException(STRING path, STRING StrNewstring)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			STR_DECLR_INIT(log_str, XmlPropGet(XML_PROP_PATH, path));
//			STR_ADD(log_str, STR_SPACE);
//
//			STR_ADD(log_str, StrNewstring);
//			RES_CHECK(result,LineAdd(LOG_EXP, log_str));
//
//			MUTX_UNLOCK(LogLock);
//			RES_RETURN(result);
//		}
//
//		FW_RESULT	CFwLog::AddScheduler(STRING path, STRING StrNewstring)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			STR_DECLR_INIT(log_str, XmlPropGet(XML_PROP_PATH, path));
//			STR_ADD(log_str, STR_SPACE);
//
//			STR_ADD(log_str, StrNewstring);
//			RES_CHECK(result,LineAdd(LOG_SCHD, log_str));
//
//			MUTX_UNLOCK(LogLock);
//			RES_RETURN(result);
//		}
//
//		FW_RESULT	CFwLog::AddMesurnment(STRING StrNewstring)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			RES_CHECK(result, LineAdd(LOG_MSUR, StrNewstring));
//
//			MUTX_UNLOCK(LogLock);
//			RES_RETURN(result);
//		}
//
//	#else
//		FW_RESULT	CFwLog::AddException(STRING StrNewstring)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			if(my_ResultsLog)	
//
//			{
//				RES_CHECK(result,LineAdd(LOG_EXP, StrNewstring));
//			}
//
//			MUTX_UNLOCK(LogLock);
//			RES_RETURN(result);
//		}
//
//		FW_RESULT	CFwLog::AddScheduler(STRING StrNewstring)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			RES_CHECK(result,LineAdd(LOG_SCHD, StrNewstring));
//
//			MUTX_UNLOCK(LogLock);
//			RES_RETURN(result);
//		}
//	#endif
//
//
//
//
//
//
//
//	STRING	CFwLog::DocHeader(LOG_TYPE logType, STRING header)
//	{
//	//	ENUM_SET(LOG_TYPE, my_logType, logType);
//		STR_DECLR_INIT(str, XML_NOD_BEGIN);
//		STR_ADD(str, ENUM_NAME(LOG_TYPE, logType));
//		STR_ADD(str, STR_SPACE);
//
//		STR_ADD(str, ENUM_NAME(XML_PROP, XML_PROP_TIME));
//		CTime t = CTime::GetCurrentTime();
//		STR_ADD(str, t.Format(DATE_TIME_FORMAT/*"%d/%m/%Y %H:%M:%S"*/) + XML_PROP_END);
//		STR_ADD(str, STR_SPACE);
//		STR_ADD(str, header);
//		STR_ADD(str, XML_NOD_END);
//
//		STR_RETURN(str) 
//	}
//	STRING	CFwLog::DocTrailer(LOG_TYPE logType)
//	{
//		STR_DECLR_INIT(str, XML_TAG_BEGIN);
//	//	STR_ADD(str, STR_SPACE);
//
//		STR_ADD(str, ENUM_NAME(LOG_TYPE, logType));
//	//	STR_ADD(str, STR_SPACE);
//
//		STR_ADD(str, XML_NOD_END);
//		STR_RETURN(str) 
//	}
//
//	#ifdef	LOG_FILE
//		STRING CFwLog::DocStr(LOG_TYPE logType, STRING header, STRING newline)
//		{
//
//			STR_DECLR_INIT(path, XmlPropGet(XML_PROP_PATH, header));
//			STR_DECLR_INIT(logStr, DocHeader(logType, path));
//			STR_ADD(logStr, STR_SPACE);
//
//			STR_ADD(logStr, newline);
//			STR_ADD(logStr, STR_SPACE);
//
//			STR_ADD(logStr, DocTrailer(logType));
//
//
//			STR_RETURN(logStr);
//		}
//	#else
//		FW_RESULT CFwLog::DocAdd(LOG_TYPE logType, STRING header, STRING newline)
//		{
//			RES_DECLR(result);
//			STR_DECLR(logStr);
//
//			STR_ADD(logStr, DocHeader(logType, header));
//			STR_ADD(logStr, STR_SPACE);
//
//			STR_ADD(logStr, newline);
//			STR_ADD(logStr, DocTrailer());
//
//			RES_CHECK(result, ListAdd(logStr));
//			if(LOG_DATA != logType){
//				RES_CHECK(result, FileAdd(logStr));	//	Add the string to the file.
//			}
//			RES_RETURN(result);
//		}
//	#endif
//
//	#ifdef	LOG_FILE
//		FW_RESULT	CFwLog::DocResult(STRING header, STRING name, bool ok)
//		{
//			RES_DECLR(result)
//
//			RES_CHECK(result, AddResult(header, name, ok));
//
//	//		STR_DECLR_INIT(resStr, ResultStr(name, ok));
//	//		STR_DECLR_INIT(docStr, DocStr(LOG_RES, header, resStr));
//	//		RES_CHECK(result, FileAdd(docStr));	//	Add the string to the file.
//
//			RES_RETURN(result);
//		}
//	
//		FW_RESULT	CFwLog::DocProc(STRING header, STRING text)
//		{
//			RES_DECLR(result)
//
//			RES_CHECK(result, AddProc(header, text)); 
//
//	//		STR_DECLR_INIT(docStr, DocStr(LOG_PROC, header, text));
//	//		RES_CHECK(result, FileAdd(docStr));	//	Add the string to the file.
//
//			RES_RETURN(result);
//		}
//
//		FW_RESULT	CFwLog::DocException(STRING header, STRING StrNewstring)
//		{
//			RES_DECLR(result)
//
//			RES_CHECK(result, AddException(header, StrNewstring)); 
//
//	//		STR_DECLR_INIT(docStr, DocStr(LOG_EXP, header, StrNewstring));
//	//		RES_CHECK(result, FileAdd(docStr));	//	Add the string to the file.
//
//			RES_RETURN(result);
//		}
//
//		FW_RESULT	CFwLog::DocScheduler(STRING header, STRING StrNewstring)
//		{
//			RES_DECLR(result);
//
//			RES_CHECK(result, AddScheduler(header, StrNewstring)); 
//
//	//		STR_DECLR_INIT(docStr, DocStr(LOG_SCHD, header, StrNewstring));
//	//		RES_CHECK(result, FileAdd(docStr));	//	Add the string to the file.
//
//			RES_RETURN(result);
//		}
//
//		FW_RESULT	CFwLog::DocMesurnment(STRING header, STRING StrNewstring)
//		{
//			RES_DECLR(result);
//
//			STR_DECLR_INIT(docStr, DocStr(LOG_MSUR, header, StrNewstring));
//
//	//		RES_CHECK(result, AddMesurnment(docStr));
//			RES_CHECK(result, ListAdd(docStr));
//
//			RES_CHECK(result, FileAdd(docStr));	//	Add the string to the file.
//
//			RES_RETURN(result);
//		}
//	#else
//		FW_RESULT	CFwLog::DocMesurnment(STRING header, STRING StrNewstring)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			RES_CHECK(result,DocAdd(LOG_MSUR, header, StrNewstring));
//
//			MUTX_UNLOCK(LogLock);
//			RES_RETURN(result);
//		}
//	#endif
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//		/***********************************************************************\
//		*																								*
//		*									L i s t   M e t h o d s								*
//		*																								*
//		\***********************************************************************/
//		bool CFwLog::ListIsEmpty(void)
//		{
//			bool	is_empty = false;
//			MUTX_LOCK(LogLock);
//
//			is_empty = (ListString.IsEmpty() == TRUE);
//
//			MUTX_UNLOCK(LogLock);							//	Release.
//			return(is_empty);
//		}
//
//		int CFwLog::ListGetCount(void)
//		{
//			int	count = 0x00;
//			MUTX_LOCK(LogLock);
//
//			count = ListString.GetCount();
//
//			MUTX_UNLOCK(LogLock);							//	Release.
//			return(count);
//		}
//
//
//		FW_RESULT	CFwLog::ListFindIndex(int	index)
//		{
//			RES_DECLR(result);
//			MUTX_LOCK(LogLock);
//
//			my_ListPosition = ListString.FindIndex(index);	//	Get the position of the string in the list.
//			RES_CHECK(result,PTR_NOT_NULL(my_ListPosition));
//
//			MUTX_UNLOCK(LogLock);							//	Release.
//			RES_RETURN(result);
//		}
//
//		STRING	CFwLog::ListGetNext(void)
//		{
//			STR_DECLR(str);
//
//			MUTX_LOCK(LogLock);
//
//			if(PTR_NOT_NULL( my_ListPosition)){
//				PTR_DECLR_INIT(STRING, pLine, ListString.GetNext(my_ListPosition));
//				STR_SET(str, *pLine);
//				PTR_DESTROY(pLine);
//			}
//			MUTX_UNLOCK(LogLock);							//	Release.
//
//			STR_RETURN(str);
//		}
//
//		STRING	CFwLog::ListPopHead(void)
//		{
//			STR_DECLR(str);
//
//			MUTX_LOCK(LogLock);
//
//			PTR_DECLR_INIT(CString, pStr, ListString.RemoveHead());
//			STR_SET(str, *pStr);
//			PTR_DESTROY(pStr);
//
//			MUTX_UNLOCK(LogLock);							//	Release.
//
//			STR_RETURN(str);
//		}
//
//
//
//
//	FW_RESULT CFwLog::ListClear(void)
//	{
//		RES_DECLR(result);
//		MUTX_LOCK(LogLock);
//
//	//	PTR_DECLR(STRING,pString);
//		while(!ListString.IsEmpty())					//	lis is not empty.
//		{
//			PTR_DECLR_INIT(STRING, pString, ListString.RemoveTail());
//			PTR_DESTROY(pString);
//	//		ListString.RemoveTail();
//		}
//		MUTX_UNLOCK(LogLock);							//	Release.
//		RES_RETURN(result);
//	}
//
//
//	//*	Store the Log list in to a file.
//	FW_RESULT CFwLog::ListToFile(STRING path,STRING name)
//	{
//		RES_DECLR(result);
//
//		int         ListCount			= ListString.GetCount();
//		POSITION    my_ListPosition	= ListString.GetHeadPosition();
//
//		RES_CHECK(result,my_LogFile.FullPathLet(path));		//  Let the CFile know the name of the file that's associated with the object.
//
//		STR_DECLR(str);
//		for (int i=1; i < ListGetCount(); i++)
//		{
//			STR_SET(str, ListGetNext());
//			STR_ADD(str, FILE_LOG_STRING_END);
//			RES_CHECK(result, FileAdd(str));
//		}
//
//		RES_RETURN(result);
//	}

