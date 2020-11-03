#ifndef FW_FILES_HPP
#define	FW_FILES_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





	/********************************************************************\
	*																							*
	*									Include files										*
	*																							*
	\********************************************************************/
	#include <iostream>
	#include <fstream>
//	#include	HDR_FW_STRING
	#include	HDR_FW_ENUMS
	#include	HDR_FW_SINC





	/********************************************************************\
	*																							*
	*									Definitions											*
	*																							*
	\********************************************************************/
	#define	PATH_SEP				"/"

	#define	FILE_HNDLR							CFwFile
	#define	FILE_READ(FILE,PATH,CONT)		FILE.Read(PATH, CONT)
	#define	FILE_WRITE(FILE,PATH)			FILE.Write(PATH)
	#define	FILE_DELETE(NAME)		(std::remove(NAME.c_str()) == 0x00)

	#define	FILE_TYPE_FIELDS	\
		FILE_TYPE_LOG				\
		/*FILE_TYPE_FIELDS*/
	ENUM_DEFINE(FILE_TYPE, FILE_TYPE_FIELDS);





	/********************************************************************\
	*																							*
	*										Class												*
	*																							*
	\********************************************************************/
	class CFwFile
	{
		private:		STRING		my_path;
		private:		SINC_LOCK_DECLR(my_lock);

		private:						CFwFile(STRING path, FILE_TYPE type);
		public:						CFwFile(FILE_TYPE type);
		public:		virtual		~CFwFile();

		public:		FW_RESULT		Clear();
		public:		FW_RESULT		Show();
		public:		FW_RESULT		Read(STRING path, STRING& content);
		public:		FW_RESULT		Write(STRING content);
	};





	/********************************************************************\
	*																							*
	*									Public Functions									*
	*																							*
	\********************************************************************/
	STRING	FwDirectoryCurrent();
#endif // !FW_FILES_HPP




