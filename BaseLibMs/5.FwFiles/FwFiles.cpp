/********************************************************************\
*																							*
*									Files Handler										*
*																							*
\********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





/********************************************************************\
*																							*
*									Include Files										*
*																							*
\********************************************************************/
#include	<stdio.h>
#include	<iostream>
#include <conio.h>
#include	HDR_FW_FILES
#include	HDR_FW_POINTERS
#include	HDR_FW_CONSOL





/********************************************************************\
*																							*
*									Local Definitions									*
*																							*
\********************************************************************/
#define	FILE_EXT_SEP		"."
#define	FILE_PATH_SEP		"\\"

#define	FILE_TYPE_NAMES	\
	"LogFile"
	/*FILE_TYPE_NAMES*/
#define	FILE_EXT_NAMES		\
	"log"							\
	/*FILE_TYPE_FIELDS*/




/********************************************************************\
*																							*
*									Containers											*
*																							*
\********************************************************************/
ENUM_NAMES_CREATE(FILE_TYPE, FILE_TYPE_NAMES);
ENUM_TABLE_CREATE(STRING,FILE_TYPE,STR_EMPTY,FILE_EXT_NAMES);




/********************************************************************\
*																							*
*									Local Functions									*
*																							*
\********************************************************************/
static STRING	FilePath(STRING path, FILE_TYPE type)
{
	STR_DECLR_INIT(path_full, path);
	STR_ADD(path_full, FILE_PATH_SEP);

	STR_ADD(path_full, ENUM_NAME(FILE_TYPE, type));
	STR_ADD(path_full, FILE_EXT_SEP);

	STR_ADD(path_full, ENUM_VAL(FILE_TYPE, type));

	STR_RETURN(path_full);
}





/********************************************************************\
*																							*
*									Definitions											*
*																							*
\********************************************************************/
#ifdef _MSC_VER
	#include <direct.h>
	#define GET_CURR_WORK_DIR	_getcwd
#else
	#include <unistd.h>
	#define GET_CURR_WORK_DIR	getcwd
#endif





/********************************************************************\
*																							*
*										Class												*
*																							*
\********************************************************************/
CFwFile::CFwFile(STRING path, FILE_TYPE type)
{
	STR_SET(my_path, FilePath(path, type));
}
CFwFile::CFwFile(FILE_TYPE type)
{
	STR_SET(my_path, FilePath(FwDirectoryCurrent(), type));
}

CFwFile::~CFwFile()
{
}




/********************************************************************\
*																							*
*									File Methods										*
*																							*
\********************************************************************/
FW_RESULT	CFwFile::Show()
{
	RES_DECLR(result);
//	SINC_LOCK(my_lock);

	char buffer [100];
	PTR_DECLR_INIT(FILE, pFile, fopen(my_path.c_str(), "r"));
	RES_CHECK(result, PTR_NOT_NULL(pFile));

	bool clear = false;
	if(PTR_NOT_NULL(pFile))	
	{
		while ( ! feof (pFile) )
		{
			for(int i=0x00; i<80; i++)
			{
				if (fgets (buffer , 100 , pFile) != NULL ){
					RES_CHECK(result, EOF != fputs(buffer , stdout));
				}
			}

			printf("\n press 'n' for next or 'c' to clear or any other key to exit\n");
#ifdef VS_BUILD
			int key = _getch();
#else
			int key = getch();
#endif
			if(('c' == key) || ('C' == key)) {
				clear = true;;
			}

			if(('n' != key) && ('N' != key)) {
				CONSOL_CLEAR;
				break;
			}
		}
		RES_CHECK(result, EOF != fclose(pFile));
	}

	if(true == clear){
		RES_CHECK(result, Clear());
	}
//	SINC_UNLOCK(my_lock);
	RES_RETURN(result);
}

FW_RESULT	CFwFile::Read(STRING path, STRING& content)
{
	RES_DECLR(result);
//	SINC_LOCK(my_lock);

	try{
//		std::fstream fs;
//		fs.open(path, std::fstream::in);
//		fs.read(content, fs.tellg());// fs >> content;
//		fs.close();


		std::ifstream ioFile(path);
		std::string strBuffer;

		ioFile.seekg(0, std::ios::end);   
		strBuffer.reserve(ioFile.tellg());
		ioFile.seekg(0, std::ios::beg);

		strBuffer.assign((std::istreambuf_iterator<char>(ioFile)),  std::istreambuf_iterator<char>());	
		STR_SET(content, strBuffer);
	}
	catch(...){
		RES_FAILE(result);	
	}

//	SINC_UNLOCK(my_lock);
	RES_RETURN(result);
}

FW_RESULT	CFwFile::Write(STRING content)
{
	RES_DECLR(result);

//	SINC_LOCK(my_lock);

	std::lock_guard<std::mutex> my_lock_lock(my_lock_mutex);

//	std::unique_lock<std::mutex> my_lock_lock(my_lock_mutex, std::defer_lock );	\
//	if(true != my_lock_lock.try_lock()){								\
//		my_lock_flag.wait(my_lock_lock);								\
//	}																			\


	try{
		std::fstream fs;

		fs.open(my_path, std::fstream::out | std::fstream::app);
		fs << content.c_str();
		fs.close();
	}
	catch(...){
		RES_FAILE(result);
	}

//	SINC_UNLOCK(my_lock);

//	my_lock_lock.unlock();			\
//	my_lock_flag.notify_one();		\

	RES_RETURN(result);
}

FW_RESULT	CFwFile::Clear()
{
	RES_DECLR(result);
	PTR_DECLR_INIT(FILE, pFile, fopen(my_path.c_str(), "r"));
	if(PTR_NOT_NULL(pFile))	{
		RES_CHECK(result, EOF != fclose(pFile));
		remove(my_path.c_str());
	}
	RES_CHECK(result, Write(""));
	RES_RETURN(result);
}




/********************************************************************\
*																							*
*									Public Functions									*
*																							*
\********************************************************************/
STRING	FwDirectoryCurrent()
{
	char path[_MAX_PATH] = {'\0'};
	RES_ALERT(GET_CURR_WORK_DIR(path, sizeof(path)));

	STR_DECLR_INIT(str_ret, path);
	STR_RETURN(str_ret);
}
