/***********************************************************************\
*																								*
*											File Handler									*
*																								*
\***********************************************************************/
#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





/***********************************************************************\
*																								*
*										Include files										*
*																								*
\***********************************************************************/
#include	<direct.h>
#include	HDR_FW_POINTERS
#include	HDR_FW_SINC
#include	HDR_FW_TEXT_STR
#include HDR_FW_FILES






/***********************************************************************\
*																								*
*											Global											*
*																								*
\***********************************************************************/
ENUM_NAMES_CREATE(FILE_TYPE,FILE_TYPE_NAMES);


namespace MicFile
{
	STRING	FileExtNameGet(FILE_TYPE type)
	{
		STR_RETURN(ENUM_NAME(FILE_TYPE,type));
	}
	STRING	FilePathFullGet(STRING path, STRING name, FILE_TYPE code)
	{
		STR_DECLR(full_path);

		STR_SET(full_path,path);
		STR_ADD(full_path,name);
		STR_ADD(full_path,MicFile::FileExtNameGet(code));

		STR_RETURN(full_path);
	}

	STRING	FilePathFParentGet(STRING	full_path)
	{
		STR_DECLR(path);
		CMicString StrHandler;

		STR_SET(path, StrHandler.TokenLeftGet(full_path, FILE_PATH_TAG));
		STR_SET(path, StrHandler.TokenLeftGet(path, FILE_PATH_TAG));
		STR_ADD(path, FILE_PATH_TAG);

		STR_RETURN(path);
	};

	PTR_DECLR(STRING,pName);
	STRING	WorkingName() {
		STR_RETURN(*pName);
	}
	void		WorkingName(STRING newName) {
		if(PTR_IS_NULL(pName)){
			PTR_CREATE(STRING,pName);
		}
		(*pName) = newName;
	}


	STR_DECLR(Directory);
	STRING	WorkingDirectory() {
		STR_RETURN(Directory);
	}
	FW_RESULT  WorkingDirectory(STRING newDir)
	{
		RES_DECLR(result)
		STR_SET(Directory,newDir);
		RES_RETURN(result);
	}

	STRING	GetWorkingDirectory()
	{
		STR_DECLR_INIT(dir, _getcwd( NULL, 0 ));

//		STR_ADD(dir, FILE_PATH_TAG);
//		STR_SET(dir, FilePathFParentGet(dir));
		WorkingDirectory(dir);

		STR_RETURN(dir);
	}
}










/***********************************************************************\
*																								*
*											C l a s s										*
*																								*
\***********************************************************************/

FW_RESULT	CFileHandler::Clear(void)
{
	RES_DECLR(result);

	CFwBuffer::BufferClear();

	RES_RETURN(result);
}

FW_RESULT	CFileHandler::Init(void)
{
	RES_DECLR(result);

	ENUM_INIT(FILE_TYPE, my_Type);

	STR_INIT(my_Path);
	STR_INIT(my_Name);
	STR_SET(my_Ext, ENUM_NAME(FILE_TYPE, my_Type));

	my_file = INVALID_HANDLE_VALUE;
	my_file_size =	0x00;

	block_size	= 0x00;
	block_index	= 0x00;

	RES_RETURN(result);
}

FW_RESULT	CFileHandler::InitCounters(void)
{
	RES_DECLR(result);

	my_file_size	=	0x00;

	RES_RETURN(result);
}

CFileHandler::CFileHandler()
{
	RES_DECLR(result);

	RES_CHECK(result,Init());

	RES_ALERT(result);
}
CFileHandler::CFileHandler(STRING path, STRING name, FILE_TYPE type)
{
	RES_DECLR(result);

	RES_CHECK(result, Init());

	RES_CHECK(result, PathLet(path));
	RES_CHECK(result, NameLet(name));
	RES_CHECK(result, TypeCode(type));

	RES_ALERT(result);
	return;
}
CFileHandler::~CFileHandler()
{
	RES_DECLR(result);

	if(INVALID_HANDLE_VALUE != my_file){
		RES_CHECK(result, Close());
	}
	RES_CHECK(result, Clear());

	RES_ALERT(result);
}










/***********************************************************************\
*																								*
*										P r o p e r t i e s								*
*																								*
\***********************************************************************/
FILE_TYPE	CFileHandler::TypeCode(void)
{
	return(my_Type);
}
FW_RESULT	CFileHandler::TypeCode(FILE_TYPE type)
{
	RES_DECLR(result);

	RES_CHECK(result, ENUM_SET(FILE_TYPE, my_Type, type));
	STR_SET(my_Ext, ENUM_NAME(FILE_TYPE, type));
	
	RES_RETURN(result);
}

//	File extension.
STRING	CFileHandler::ExtCalc(STRING	full_path)
{
	return(CMicString::TokenRightGet(full_path,FILE_EXT_TAG));
}
FW_RESULT	CFileHandler::ExtLet(STRING ext)
{
	bool	result = true;

	my_Ext = ExtCalc(ext);
	result = (my_Ext != STR_EMPTY);

	ASSERT(result);
	return(result);
}
STRING	CFileHandler::ExtGet(void)
{
	return(my_Ext);
}


//	File name.
STRING	CFileHandler::NameCalc(STRING	full_path)
{
	STR_DECLR(name);

	STR_SET(name, CMicString::TokenRightGet(full_path, FILE_PATH_TAG));
	STR_SET(name, CMicString::TokenLeftGet(name, FILE_EXT_TAG));

	STR_RETURN(name);
}
FW_RESULT		CFileHandler::NameLet(STRING name)
{
	RES_DECLR(result);

	STR_SET(my_Name, name);
	RES_CHECK(result,STR_NOT_EMPTY(my_Name));

	RES_RETURN(result);
};

STRING	CFileHandler::NameGet(void)
{
	return(my_Name);
};

//	File path.
STRING	CFileHandler::PathCalc(STRING	full_path)
{
	STR_DECLR(path);

	STR_SET(path, CMicString::TokenLeftGet(full_path,FILE_PATH_TAG));
	if(path != STR_EMPTY){
		STR_ADD(path,FILE_PATH_TAG);
	}
	STR_RETURN(path);
}

FW_RESULT		CFileHandler::PathLet(STRING path)
{
	RES_DECLR(result);

	my_Path = PathCalc(path);
	RES_CHECK(result,STR_NOT_EMPTY(my_Path));

	RES_RETURN(result);
}
STRING	CFileHandler::PathGet(void)
{
	STR_RETURN(my_Path);
}

//	File path and name.
STRING	CFileHandler::PathAndNameGet(void)
{
	STR_RETURN(STR_ADD(my_Path, my_Name));
};
FW_RESULT	CFileHandler::PathAndNameLet(STRING path)
{
	RES_DECLR(result);

	RES_CHECK(result, NameLet(path));
	RES_CHECK(result, PathLet(path));

	RES_RETURN(result);
};
//	Return the name of the file from a full path.
STRING	CFileHandler::PathAndNameCalc(STRING	full_path)
{
	STR_RETURN(CMicString::TokenLeftGet(full_path,FILE_EXT_TAG));
}


STRING	CFileHandler::FullPathGet(void)
{
	STR_DECLR(full_path);
	
	STR_ADD(full_path, my_Path);
	STR_ADD(full_path, my_Name);
	STR_ADD(full_path, FILE_EXT_TAG);
	STR_ADD(full_path, ExtGet());

	STR_RETURN(full_path);
}
FW_RESULT		CFileHandler::FullPathLet(STRING path)
{
	RES_DECLR(result);

	RES_CHECK(result,NameLet(path));
	RES_CHECK(result,PathLet(path));
	RES_CHECK(result,ExtLet(path));

	RES_RETURN(result);
}
STRING	CFileHandler::FullPathGet(FILE_TYPE type)
{
	STR_DECLR(full_path);

	STR_ADD(full_path, my_Path);
	STR_ADD(full_path, my_Name);
	STR_ADD(full_path, FILE_EXT_TAG);
	STR_ADD(full_path,  ENUM_NAME(FILE_TYPE, type));

	STR_RETURN(full_path);
}










/***********************************************************************\
*																								*
*									F i n d   F i l e										*
*																								*
\***********************************************************************/

//	Search if file exists.
FW_RESULT	CFileHandler::Find(STRING path, FILE_TYPE type_code)
{
	RES_DECLR(result);
	STR_DECLR(full_path);
	WIN32_FIND_DATA	FindFileData;
	HANDLE				hFind;

	STR_SET(full_path, MicFile::FilePathFullGet(path, STR_EMPTY, type_code));

	hFind = FindFirstFile(STR_PBUFF(full_path), &FindFileData);
	if (INVALID_HANDLE_VALUE != hFind)	{
		RES_CHECK(result,FALSE != FindClose(hFind));
	}
	else	{
		RES_FAILE(result);
	}

	RETURN(result);
}

//	Open a file search dialog.
STRING	CFileHandler::Dialog(STRING path, FILE_TYPE type_code)
{
	STR_DECLR(full_path);

	STR_ADD(path, FILE_ALL_TAG);
	STR_ADD(path, FILE_EXT_TAG);
	STR_ADD(path, ENUM_NAME(FILE_TYPE,type_code));

	CFileDialog	dlgFile(TRUE, NULL, path);//(TRUE, NULL, path, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, MicFile::FileExtNameGet(type_code), NULL);	//	A pointer to the file dialog-box object’s parent or owner window.
	if(dlgFile.DoModal() == IDOK)	{					//	Activate and check the file dialog.If a file was selected.
		STR_SET(full_path, dlgFile.GetPathName());//.GetFileName());	//	Get the file full path.
	}

	STR_RETURN(full_path);
}










/***********************************************************************\
*																								*
*						P r i v a t e   O p e r a t i o n s							*
*																								*
\***********************************************************************/
//	Open the file and keep a file handle.
FW_RESULT	CFileHandler::Open(FILE_TYPE type)
{
	RES_DECLR(result);
	STR_DECLR(full_path);
	
	RES_CHECK(result,InitCounters());

	STR_SET(full_path,FullPathGet(type));
	if(STR_NOT_EMPTY(full_path))
	{	
		//	Open for reading.
		my_file = CreateFile(STR_PBUFF(full_path), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL, 0);
		if(INVALID_HANDLE_VALUE == my_file)
		{																//	Try creation when unsucsessful.
			my_file = CreateFile(STR_PBUFF(full_path), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS , FILE_ATTRIBUTE_NORMAL, 0);
		}

		if(INVALID_HANDLE_VALUE != my_file){				//	Prepare for using.
			//RES_CHECK(result,LockFile(my_file,0,0,FILE_END,0) != FALSE);
			my_file_size = GetFileSize(my_file, NULL);
		}
		else{
			RES_FAILE(result);
		}
	}
	else{
		RES_FAILE(result);
	}

	RETURN(result);
}
FW_RESULT	CFileHandler::Open(void)
{
	RETURN(Open(my_Type));
}

FW_RESULT	CFileHandler::Open(STRING path, STRING name, FILE_TYPE type)
{
	RES_DECLR(result);

	RES_CHECK(result, ENUM_SET(FILE_TYPE, my_Type, type));

	STR_SET(my_Path, path);
	STR_SET(my_Name, name);
	STR_SET(my_Ext, ENUM_NAME(FILE_TYPE, type));

	my_file = INVALID_HANDLE_VALUE;
	my_file_size =	0x00;

	block_size	= 0x00;
	block_index	= 0x00;

	RES_CHECK(result, Open());

	RES_RETURN(result);
}

ULong	CFileHandler::Size()
{
	ULong size = {	0x00	};
	size.val = (my_file_size > FILE_MAX_SIZE) ? FILE_MAX_SIZE : my_file_size;
	return(size);
}

//--------------------------------------'
//	Write a string to the end of the file.
FW_RESULT	CFileHandler::Append(const void* p_buffer, FW_UINT nCount)
{
	RES_DECLR(result);

	CFile	file(my_file);
	file.SeekToEnd();
	file.Write(p_buffer, nCount);
	file.Flush();

	my_file_size = GetFileSize(my_file, NULL);

	RES_RETURN(result);
}


//----------------------------'
//	Close the current file.
FW_RESULT	CFileHandler::Close(void)
{
	RES_DECLR(result);

//	RES_CHECK(result, FALSE != UnlockFile(my_file, 0, 0, FILE_END, 0));
//	RES_CHECK(result, FALSE != CancelIo(my_file));		// file handle for which to cancel I/O
//	RES_CHECK(result, FALSE != CloseHandle(my_file));	// handle to object to close

	CFile	file(my_file);
	file.Close();

	my_file = INVALID_HANDLE_VALUE;

	RES_RETURN(result);
}

//------------------------------------------'
//	Delete a file
FW_RESULT	CFileHandler::Delete(void)
{
	RES_DECLR(result);
	bool reopen = false;

	if(INVALID_HANDLE_VALUE != my_file)	{
		reopen = true;
		RES_CHECK(result, Close());		//	Close the file if still open.
	}
	if(STR_NOT_EMPTY(FullPathGet()))	{					//	The file has a valid path.
		RES_CHECK(result,DeleteFile(STR_PBUFF(FullPathGet())));  // Delete the file.
	}

	if(true == reopen){
		RES_CHECK(result, Open());
	}

	RES_RETURN(result);
}










/***********************************************************************\
*																								*
*									Buffer   F i l e										*
*																								*
\***********************************************************************/
//	Load the file contents in to memory buffer.
FW_RESULT	CFileHandler::BuffLoad(void)
{
	RES_DECLR(result);
	DWORD		NumberOfBytesRead = 0x00;
	LPVOID	lpBuffer				= NULL;
	
	CFwBuffer::BufferClear();
	if(my_file_size > 0x00)
	{
		lpBuffer = new unsigned char [my_file_size];

		if(PTR_NOT_NULL(lpBuffer))
		{
			RES_CHECK(result, INVALID_SET_FILE_POINTER != SetFilePointer(my_file, 0, 0, FILE_BEGIN));
			RES_CHECK(result, FALSE != ReadFile(my_file, lpBuffer, my_file_size,  &NumberOfBytesRead, NULL));
			if(my_file_size == NumberOfBytesRead)							//	Check the bytes read match the expected size.
			{																			//	Unsuccessful reading.
				RES_CHECK(result,CFwBuffer::Buffer(lpBuffer,NumberOfBytesRead));	//	Allocate a buffer container.
			}
			PTR_DESTROY(lpBuffer);
		}
	}

	RES_RETURN(result);
}

//	Get a specific block of prdefined size from file all ready loaded to memory.
FW_RESULT	CFileHandler::BuffSet(unsigned char buff[], int size, int index)
{
	RES_DECLR(result);

	block_size = size;
	block_index = index;
	
	RES_CHECK(result,BufferSet(&buff[0x00],size,(block_size * block_index)));

	RES_RETURN(result);
}

//------------------------------------------------------
//	Xor or Sum checksum of the message information.
//	not including the code places of STX,CHK,TRM.
unsigned char	CFileHandler::BuffChecksum(bool xor)
{
	unsigned	int		index = 0x00,	size = 0x00;
	unsigned	char		sum = 0x00;

	size = (block_size * block_index);
	if(CFwBuffer::Length () > 0x00)
	{
		if(CFwBuffer::Length () > 0x00)
		{
			for(index = 0x00; index < size; index++)
			{
				if(xor)
					sum ^= CFwBuffer::Buffer(index);
				else
					sum += CFwBuffer::Buffer(index);
			}
		}
	}
	return(sum);
}

//--------------------------------------'
//	Write a string to the end of the file.
FW_RESULT	CFileHandler::BuffAppend(const void* p_buffer, FW_UINT nCount)
{
	RES_DECLR(result);

	DWORD	dwPtr = SetFilePointer (my_file, 0, NULL, FILE_END);	// Try to move hFile's file pointer some distance. 
	if (GetLastError() == NO_ERROR)								// Test for failure
	{ 
		DWORD	NumberOfBytesWritten = 0x00;
		RES_CHECK(result,CFwBuffer::Buffer((unsigned char*)p_buffer,nCount));
		RES_CHECK(result,FALSE != WriteFile(my_file,CFwBuffer::Buffer (),CFwBuffer::Length(),&NumberOfBytesWritten,NULL));
		RES_CHECK(result, NumberOfBytesWritten == (DWORD)CFwBuffer::Length ());
	}

	RES_RETURN(result);
}



//-------------------------'
FW_RESULT CFileHandler::BuffUnLoad()
{
	RES_DECLR(result);

	CFwBuffer::BufferClear();
	RES_CHECK(result, CFwBuffer::IsEmpty());

	RES_RETURN(result);

}











/***********************************************************************\
*																								*
*									T e x t   F i l e										*
*																								*
\***********************************************************************/

//	Read string from file and return to caller.
STRING	CFileHandler::StringRead(void)	
{
	RES_DECLR(result);
	STR_DECLR(file_string);

	RES_CHECK(result, BuffLoad());
	STR_SET(file_string, CFwBuffer::BufferGet());

	RES_ALERT(result);
	STR_RETURN(file_string);
}

//	Read string from file and return to caller.
STRING	CFileHandler::StringRemove(void)	
{
	RES_DECLR(result);
	STR_DECLR(file_string);

	STR_SET(file_string, StringRead());
	RES_CHECK(result,Delete());

	STR_RETURN(file_string);
}


//----------------------------------------
//	Write a string to the end of the file.
FW_RESULT	CFileHandler::StringAppend(STRING str)
{
	RES_DECLR(result);
	STR_DECLR(full_path);
	
	if(STR_LEN(str) > 0x00)
	{
		STR_SET(full_path,FullPathGet());
		if(STR_LEN(full_path) > 0x00)
		{				
			RES_CHECK(result, Append(str.GetBuffer(), STR_LEN(str)));
		}
		else{
			RES_FAILE(result);
		}
	}
	RES_RETURN(result);
}










/***********************************************************************\
*																								*
*										Syncronized   										*
*																								*
\***********************************************************************/


//	Write a string as file contents.
FW_RESULT	CFileHandler::StringWrite(STRING string)
{
	RES_DECLR(result);

	RES_CHECK(result,Delete());	//	Delete te old file if it exists.

	if(STR_LEN(string) > 0x00)	{
		RES_CHECK(result,BuffAppend(STR_PBUFF(string), STR_LEN(string)));	//	Write the contents to the file.
	}

	RES_RETURN(result);
}
//	Read string from file and return to caller.
STRING	CFileHandler::StringReadSinc(FILE_TYPE type)	
{
	RES_DECLR(result);
	MUTX_LOCK(FileLock);

	STR_DECLR(file_string);
	RES_CHECK(result, Open(type));
	STR_SET(file_string, StringRead());
	RES_CHECK(result, Close());

	MUTX_UNLOCK(FileLock);
	STR_RETURN(file_string);
}
STRING	CFileHandler::StringReadSinc(void)	
{
	RETURN(StringReadSinc(TypeCode()));
}
STRING	CFileHandler::StringRemoveSinc(void)	
{
	RES_DECLR(result);
	MUTX_LOCK(FileLock);

	STR_DECLR(file_string);
	RES_CHECK(result, Open());
	STR_SET(file_string,StringRemove());
	RES_CHECK(result, Close());

	MUTX_UNLOCK(FileLock);
	STR_RETURN(file_string);
}
FW_RESULT	CFileHandler::StringAppendSinc(STRING str)
{
	RES_DECLR(result);
	MUTX_LOCK(FileLock);

	RES_CHECK(result, Open());
	RES_CHECK(result, StringAppend(str));
	RES_CHECK(result, Close());

	MUTX_UNLOCK(FileLock);
	RES_RETURN(result);
}
FW_RESULT	CFileHandler::StringWriteSinc(STRING string)
{
	RES_DECLR(result);
	MUTX_LOCK(FileLock);

	RES_CHECK(result, Open());
	RES_CHECK(result, StringWrite(string));
	RES_CHECK(result, Close());

	MUTX_UNLOCK(FileLock);
	RES_RETURN(result);
}

