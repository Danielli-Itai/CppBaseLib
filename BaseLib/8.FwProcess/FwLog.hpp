/***********************************************************************\
*																								*
*										L o g   H a n d l e r							*
*																								*
\***********************************************************************/
#ifndef FW_LOG_HPP
#define FW_LOG_HPP
	#include	"../../../0.Framework/BaseLib/0.Config/Config.h"
	#include	"../../../0.Framework/BaseLib/0.Config/Includes.h"





	/********************************************************************\
	*																							*
	*									Include Files										*
	*																							*
	\********************************************************************/
	#include	HDR_FW_STRING
	#include	HDR_FW_FILES





	/********************************************************************\
	*																							*
	*									Definitions											*
	*																							*
	\********************************************************************/
	#define	LOG_PROP_SEP		":"
	#define	LOG_RECORD_SEP		","
	#define	LOG_LINE_END		"\n"





	/********************************************************************\
	*																							*
	*									Class													*
	*																							*
	\********************************************************************/
	class CFwLogConsol
	{
		private:		CFwFile		my_file;
		public:						CFwLogConsol();
		public:		virtual		~CFwLogConsol();

		public:		FW_RESULT		Clear();
		public:		FW_RESULT		Show();
		public:		FW_RESULT		Write(STRING path, FW_RESULT result, STRING msg);
	};





	/***********************************************************************\
	*																								*
	*											Include Files									*
	*																								*
	\***********************************************************************/
	#include	HDR_FW_FILES
	#include	HDR_FW_SINC
	#include	HDR_FW_DATA_LIST
//	#include	HDR_MIC_THREAD
//	#include HDR_CONN_MESSG
//	#include HDR_CONN_SESSION





	/***********************************************************************\
	*																								*
	*											Definitions										*
	*																								*
	\***********************************************************************/
	#define		LOG_STORE_TO_FILE					0x021
	#define		LOG_STORE_TO_FILE_NAME			"Stor logger to File"

	#define		MAX_LIST_SIZE_LOG_STRING		5000

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
		protected:	FILE_HNDLR	my_LogFile;
		private:		FW_RESULT		ListToFile(STRING path, STRING name);

		//	Data file.
		protected:	FW_RESULT		FileAdd(STRING newline);

		protected:	MUTEX_DECLR(LogLock);

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
		private:		FW_LIST_DECLR(STRING*, ListString);
		protected:	FW_RESULT			ListAdd(STRING newline);
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
