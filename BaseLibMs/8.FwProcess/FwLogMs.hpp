/***********************************************************************\
*																								*
*										L o g   H a n d l e r							*
*																								*
\***********************************************************************/
#ifndef MIC_LOG_H
#define MIC_LOG_H
#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"







	/***********************************************************************\
	*																								*
	*											Include Files									*
	*																								*
	\***********************************************************************/
	//#include HDR_STDAFX	//	"afxtempl.h"
	#include	HDR_FW_FILES
	#include	HDR_FW_THREAD
//	#include HDR_CONN_MESSG
//	#include HDR_CONN_SESSION





	/***********************************************************************\
	*																								*
	*										L o g g i n g										*
	*																								*
	\***********************************************************************/
	STRING	GetLinePath(STRING file, STRING func, int line);
	#define	FUNC_PATH_FULL		GetLinePath(__FILE__, __FUNCTION__, __LINE__)  
	
	#define	LOG_DECLR(VAR)					\
		CFwLog				VAR				\
		/*LOG_DECLR*/
	#define	LOG_STRING(VAR,STR)			\
		VAR.ListAdd(STR)					\
		/*LOG_STRING*/
	#define LOG_RESULT(STR,RES)			\
		LogResult(STR,RES)					\
		/*LOG_RESULT*/
	#define LOG_MESSAGE(PMSG)				\
		LogMessage(PMSG)						\
		/*LOG_MESSAGE*/
	#define	LOG_EVENT(PMSG)				\
		LogEvent(PMSG);						\
		/*LOG_EVENT*/









	/***********************************************************************\
	*																								*
	*											Definitions										*
	*																								*
	\***********************************************************************/
	#define		LOG_STORE_TO_FILE					0x021
	#define		LOG_STORE_TO_FILE_NAME			"Stor logger to File"


	#define		MAX_LIST_SIZE_LOG_STRING		5000

	//#define		LOG_SLEEP_INTERVAL				10

	/*Log command fields*/
	#define	LOG_TYPE_FIELDS	\
		LOG_RES						\
		,LOG_PROC					\
		,LOG_DATA					\
		,LOG_EXP						\
		,LOG_SCHD					\
		,LOG_MSUR					\
	/*Log command names*/
	#define LOG_TYPE_NAMES		\
		"LOG_RES"					\
		,"LOG_PROC"					\
		,"LOG_DATA"					\
		,"LOG_EXP"					\
		,"LOG_SCHD"					\
		,"LOG_MSUR"					\
	/*Log command enumerator*/
	ENUM_DEFINE(LOG_TYPE,LOG_TYPE_FIELDS);




	#define		STR_LOG_RETURN(RES)				\
		my_Log.AddString(FUNC_PATH_FULL,STR);	\
		return(STR);									\
		/*STR_LOG_RETURN*/





	/***********************************************************************\
	*																								*
	*											Class												*
	*																								*
	\***********************************************************************/

	class CFwLog
	{
		private:		STRING		my_title;
		public:		STRING		Title(void);
		private:		FW_RESULT		Title(STRING new_name);

		public:		STRING		PathGet(void);
		public:		FW_RESULT		PathLet(STRING new_path);

		public:						CFwLog();
		public:		virtual		~CFwLog();

		//	Log file.
		protected:	CFileHandler	my_LogFile;
		private:		FW_RESULT			ListToFile(STRING path, STRING name);

		//	Data file.
		protected:	CFileHandler	my_DataFile;
		protected:	FW_RESULT			FileAdd(STRING newline);

		protected:	MUTX_DECLR(LogLock);

	#ifdef	LOG_FILE
	#else
		private:		bool				my_StringsLog;
		private:		bool				my_ResultsLog;
		private:		bool				my_LogToFile;
		public:		FW_RESULT			LogEnable(bool ToFile,	bool LogString, bool LogResult);
	#endif

		//Log list.
	//	private:		LOG_TYPE			my_logType;
		private:		int				my_ListMax;
		private:		POSITION			my_ListPosition;
		private:		CList<STRING*, STRING*> ListString;
		public:		FW_RESULT			ListAdd(STRING newline);
		private:		STRING			LineHeader(LOG_TYPE logType);
		private:		STRING			LineTrailer();
		protected:	FW_RESULT			LineAdd(LOG_TYPE logType, STRING newline);
	#ifdef	LOG_FILE
		public:		FW_RESULT			AddProc(STRING path, STRING text);
		public:		FW_RESULT			AddData(STRING path, STRING data);
	#else
		public:		FW_RESULT			AddProc(STRING text);
		public:		FW_RESULT			AddData(STRING data);
	#endif

	#ifdef	LOG_FILE
		public:		STRING			ResultStr(STRING name, bool ok);
		public:		FW_RESULT			AddResult(STRING path, STRING name, bool ok);
		public:		FW_RESULT			AddException(STRING path, STRING StrNewstring);
		public:		FW_RESULT			AddScheduler(STRING path, STRING StrNewstring);
	#else
		public:		FW_RESULT			AddResult(STRING name, bool ok);
		public:		FW_RESULT			AddException(STRING StrNewstring);
		public:		FW_RESULT			AddScheduler(STRING StrNewstring);
	#endif

	#ifdef	LOG_FILE
		public:		FW_RESULT			AddMesurnment(STRING StrNewstring);
	#endif

		private:		STRING			DocHeader(LOG_TYPE logType, STRING header);
		private:		STRING			DocTrailer(LOG_TYPE logType);
	#ifdef	LOG_FILE
		protected:	STRING			DocStr(LOG_TYPE logType, STRING header, STRING newline);
		public:		FW_RESULT			DocProc(STRING header, STRING text);
		public:		FW_RESULT			DocResult(STRING header, STRING name, bool ok);
		public:		FW_RESULT			DocException(STRING header, STRING StrNewstring);
		public:		FW_RESULT			DocScheduler(STRING header, STRING StrNewstring);
	#else
		protected:	FW_RESULT			DocAdd(LOG_TYPE logType, STRING header, STRING newline);
	#endif
		public:		FW_RESULT			DocMesurnment(STRING header, STRING strNewString);


		//	List methods.
		public:		FW_RESULT			ListClear(void);
		public:		bool				ListIsEmpty(void);
		public:		int				ListGetCount(void);
		public:		FW_RESULT			ListFindIndex(int	index);
		public:		STRING			ListGetNext(void);
		public:		STRING			ListPopHead(void);
	};
#endif	//	MIC_LOG_H
