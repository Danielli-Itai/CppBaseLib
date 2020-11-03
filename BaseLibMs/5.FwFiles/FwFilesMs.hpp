/***********************************************************************\
*																								*
*									F i l e   H a n d l e r								*
*																								*
\***********************************************************************/
#ifndef	FILE_HANDLER_H
#define	FILE_HANDLER_H
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





	/***********************************************************************\
	*																								*
	*										Include Files										*
	*																								*
	\***********************************************************************/
	#include <afxmt.h>
	#include	<Windows.h>
	#include	HDR_FW_BUFFER
	#include	HDR_FW_STRING
	#include	HDR_FW_ENUMS
	#include	HDR_FW_SINC





	/***********************************************************************\
	*																								*
	*										Definitions											*
	*																								*
	\***********************************************************************/
	#define	FILE_MAX_SIZE						FW_ULONG_MAX - FW_UINT_MAX

	#define	TIMER_PROC_INTRVL					200

	#define	FILE_BUFF_SIZE						0xFF
	#define	FILE_INTERVAL						10

	#define	FILE_HNDLR_NAME					_T("Handler")	//	Port handler Messages.

	#define	FILE_ALL_TAG						_T("*")
	#define	FILE_EXT_TAG						_T(".")
	#define	FILE_PATH_TAG						_T("\\")
	#define	FILE_LOG_STRING_END				_T(";\n")


	#define FILE_PORTHANDLER_FIELDS	\
		FILE_TYPE_PORT_LOG				\
		,FILE_TYPE_PORT_DAT				\
		,FILE_TYPE_PORT_MSG				\
		,FILE_TYPE_PORT_REP				\
		/*FILE_PORT_FIELDS*/
	#define FILE_PORTHANDLER_NAMES	\
		"phl"		/*Log*/					\
		,"phd"	/*Data*/					\
		,"phm"	/*Message*/				\
		,"phr"	/*Replay*/				\
		/*FILE_PORTHANDLER_NAMES*/

	#define FILE_PORTSERVER_FIELDS	\
		FILE_TYPE_SERVER_LOG				\
		,FILE_TYPE_SERVER_DAT			\
		/*FILE_PORT_FIELDS*/
	#define FILE_PORTSERVER_NAMES		\
		"pll"		/*Log*/					\
		,"pld"	/*Data*/					\
		/*FILE_PORTHANDLER_NAMES*/


	#define	FILE_PROJECT_FIELDS		\
		FILE_TYPE_PROJECT_LOG			\
		,FILE_TYPE_PROJECT_DAT			\
		,FILE_TYPE_PROJECT				\
		,FILE_TYPE_PROJECT_CNCTION		\
		/*FILE_PROJECT_FIELDS*/
	#define FILE_PROJECT_NAMES			\
		"Prl"		/*Log*/					\
		,"Prd"	/*Data*/					\
		,"Prj"	/*MicProject*/				\
		,"Prc"	/*Connection*/			\
		/*FILE_PROJECT_NAMES*/

	#define FILE_EXECUTION_FIELDS		\
		FILE_TYPE_EXECUTION_LOG			\
		,FILE_TYPE_EXECUTION_DAT		\
		,FILE_TYPE_EXECUTION				\
		,FILE_TYPE_EXECUTION_CNCTION	\
		/*FILE_EXECUTION_FIELDS*/
	#define	FILE_EXECUTION_NAMES		\
		"elg"		/*Log*/					\
		,"exd"	/*Data*/					\
		,"exc"	/*Execution*/			\
		,"ecn"	/*Connection*/			\
		/*FILE_EXECUTION_NAMES*/

	#define FILE_STATION_FIELDS		\
		FILE_TYPE_STATION_LOG			\
		,FILE_TYPE_STATION_DAT			\
		,FILE_TYPE_STATION_MEMORY		\
		,FILE_TYPE_STATION_EXCHNG		\
		,FILE_TYPE_STATION_CNCTION		\
		/*FILE_STATION_FIELDS*/
	#define FILE_STATION_NAMES			\
		"slg"		/*Log*/					\
		,"std"	/*Data*/					\
		,"out"	/*Memory*/				\
		,"uio"	/*Exchange/UI*/		\
		,"scn"	/*Connection*/			\
		/*FILE_STATION_NAMES*/


	#define FILE_PRCSSR_FIELDS		\
		FILE_TYPE_PRCSSR_LOG			\
		,FILE_TYPE_PRCSSR_DAT		\
		,FILE_TYPE_PRCSSR_SESSION	\
		,FILE_TYPE_PRCSSR_CNCTION	\
		,FILE_TYPE_PRCSSR_OPCODE	\
		/*FILE_PRCSSR_FIELDS*/
	#define FILE_PRCSSR_NAMES		\
		"plg"		/*Log*/				\
		,"dat"	/*Data*/				\
		,"ses"	/*Sessions*/		\
		,"pcn"	/*Connection*/		\
		,"opc"	/*Opcodes*/			\
		/*FILE_PRCSSR_NAMES*/

	#define	FILE_TYPE_FIELDS		\
		FILE_PORTHANDLER_FIELDS	\
		,FILE_PORTSERVER_FIELDS		\
		,FILE_PROJECT_FIELDS			\
		,FILE_EXECUTION_FIELDS		\
		,FILE_STATION_FIELDS			\
		,FILE_PRCSSR_FIELDS			\
		/*FILE_TYPE_FIELDS*/

	#define	FILE_TYPE_NAMES		\
		FILE_PORTHANDLER_NAMES		\
		,FILE_PORTSERVER_NAMES		\
		,FILE_PROJECT_NAMES			\
		,FILE_EXECUTION_NAMES		\
		,FILE_STATION_NAMES			\
		,FILE_PRCSSR_NAMES			\
		/*FILE_TYPE_FIELDS*/

	ENUM_DEFINE(FILE_TYPE, FILE_TYPE_FIELDS);





	/***********************************************************************\
	*																								*
	*											Class												*
	*																								*
	\***********************************************************************/

	#ifdef	OLD_CODE
		class CFileHandler:	public	CFwBuffer
	#else
		class CFileHandler:	public	CFwBuffer//, protected CMicString 
	#endif
	{
		//	Calss.
		public:		FW_RESULT		Init(void);
		private:		FW_RESULT		InitCounters(void);
		public:		FW_RESULT		Clear(void);
		public:						CFileHandler();
		public:						CFileHandler(STRING path, STRING name, FILE_TYPE type);
		public:		virtual		~CFileHandler();

		//	File name.
		private:		FILE_TYPE	my_Type;
		public:		FILE_TYPE	TypeCode(void);
		public:		FW_RESULT		TypeCode(FILE_TYPE type);

		private:		STRING		my_Ext;
		public:		FW_RESULT		ExtLet(STRING name);
		public:		STRING		ExtGet(void);
		public:		STRING		ExtCalc(STRING	full_path);

		private:		STRING		my_Name;
		public:		FW_RESULT		NameLet(STRING name);
		public:		STRING		NameGet(void);
		public:		STRING		NameCalc(STRING	full_path);

		private:		STRING		my_Path;
		public:		FW_RESULT		PathLet(STRING name);
		public:		STRING		PathGet(void);
		public:		STRING		PathCalc(STRING	full_path);

		public:		STRING		PathAndNameGet(void);
		public:		FW_RESULT		PathAndNameLet(STRING path);
		public:		STRING		PathAndNameCalc(STRING	full_path);

		public:		STRING		FullPathGet(void);
		public:		FW_RESULT		FullPathLet(STRING path);
		protected:	STRING		FullPathGet(FILE_TYPE type);


		//	File object.
		private:		HANDLE 		my_file;
		private:		DWORD 		my_file_size;			//	file size.


		//	Block operations.
		private:		int			block_size;
		private:		int			block_index;

		//	Standard operations.
		protected:	FW_RESULT		Open(FILE_TYPE type);
		public:		FW_RESULT		Open(void);
		public:		FW_RESULT		Open(STRING path, STRING name, FILE_TYPE type);

		public:		ULong			Size();
		private:		FW_RESULT		Append(const void* p_buffer, FW_UINT nCount);
		public:		FW_RESULT		Close(void);
		private:		FW_RESULT		Delete(void);

		//	String.
		private:		STRING		StringRead(void);
		private:		STRING		StringRemove(void);
		private:		FW_RESULT		StringWrite(STRING string);
		public:		FW_RESULT		StringAppend(STRING str);

		//	Buffer.
		private:		FW_RESULT			BuffLoad(void);
		private:		FW_RESULT			BuffSet(unsigned char buff[], int size, int index);
		private:		unsigned char	BuffChecksum(bool xor);
		private:		FW_RESULT			BuffAppend(const void* p_buffer, FW_UINT nCount);
		private:		FW_RESULT			BuffUnLoad();

		//	Navigation.
		public:	static FW_RESULT	Find(STRING path, FILE_TYPE type_code);
		public:	static STRING	Dialog(STRING path, FILE_TYPE type_code);

		//	Synchronization.
		private:	MUTX_DECLR(FileLock);
	
		public:		STRING		StringReadSinc(FILE_TYPE type);
		public:		STRING		StringReadSinc(void);
		public:		STRING		StringRemoveSinc(void);
		public:		FW_RESULT		StringWriteSinc(STRING str);
		public:		FW_RESULT		StringAppendSinc(STRING string);
	};










	/***********************************************************************\
	*																								*
	*									API functions											*
	*																								*
	\***********************************************************************/
	ENUM_NAMES_EXTERN(FILE_TYPE);

	namespace MicFile
	{
		STRING	FileExtNameGet(FILE_TYPE type);

		STRING	FilePathFullGet(STRING path, STRING name, FILE_TYPE code);

		STRING	WorkingName();
		void		WorkingName(STRING newName);
		STRING	WorkingDirectorySet();
		void		WorkingDirectorySet(STRING newDir);
		STRING	GetWorkingDirectory();
	}
#endif // FILE_HANDLER_H
