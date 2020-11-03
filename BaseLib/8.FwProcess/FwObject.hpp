#ifndef	FW_OBJECT_HPP
#define	FW_OBJECT_HPP
	/********************************************************************\
	*																							*
	*									Include Files										*
	*																							*
	\********************************************************************/
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"




	/********************************************************************\
	*																							*
	*									Include Files										*
	*																							*
	\********************************************************************/
	#include	HDR_FW_BASE_TYPES
	#include	HDR_FW_STRING
	#include	HDR_FW_POINTERS
	#include	HDR_FW_LOG





	/********************************************************************\
	*																							*
	*										Definitions										*
	*																							*
	\********************************************************************/
	#define	LOG_PATH_SEP		"/"

	#define	FW_OBJ_NAME				name
	#define	FW_OBJ_PRMS_LIST		CFwLogConsol* pLog, STRING path, STRING name
	#define	FW_OBJ_PRMS_PASS		pLog, path, name
	#define	FW_OBJ_PRMS_NONE		PTR_NULL, STR_EMPTY, STR_EMPTY
	#define	FW_OBJ_PRMS(NAME)		my_pLog, my_path, NAME
	#define	FW_OBJ_PRMS_LOCAL								\
		PTR_DECLR_INIT(CFwLogConsol, my_pLog, pLog);	\
		STR_DECLR_INIT(my_path,path);						\
		STR_DECLR_INIT(my_name, name);					\
		/*FW_OBJ_PRMS_LOCAL*/





	/********************************************************************\
	*																							*
	*									Class													*
	*																							*
	\********************************************************************/
	class CFwObject
	{
		protected:			PTR_MEMBER(CFwLogConsol, my_pLog);
		protected:			STRING	my_path;
		protected:			STRING	my_name;
		public:				STRING	Name();

		public:				CFwObject();
		public:				CFwObject(FW_OBJ_PRMS_LIST);
		public:	virtual	~CFwObject();

		//	Log.
		protected:	FW_RESULT	LogWrite(FW_RESULT result, STRING msg);
		protected:	FW_RESULT	LogWrite(FW_RESULT result, STRING msg, FW_ULONG64 num);
		protected:	FW_RESULT	LogWrite(FW_RESULT res_log, STRING msg, FW_CHAR* buff, FW_ULONG size);
		public:		FW_RESULT	LogShow();
		public:		FW_RESULT	LogClear();
	};
#endif // !FW_CONFIG_HPP
