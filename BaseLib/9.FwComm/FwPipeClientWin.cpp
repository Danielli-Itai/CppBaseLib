/***********************************************************************\
*																								*
*									P I P E   C L I E N T								*
*																								*
\***********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLib/0.Config/IncludesMs.h"





/***********************************************************************\
*																								*
*										Include Files										*
*																								*
\***********************************************************************/
#include <stdio.h>
#include <conio.h>
#include	HDR_FW_PIPE_CLI




/***********************************************************************\
*																								*
*											Class												*
*																								*
\***********************************************************************/
CPipeClient::CPipeClient():
		hPipe(nullptr)
	,	dwMode(0x00)
{
}
CPipeClient::~CPipeClient()
{
}




/***********************************************************************\
*																								*
*										Connection											*
*																								*
\***********************************************************************/
bool	CPipeClient::Connect(char* lpszPipename)
{
	bool result = true;

	// Try to open a named pipe; wait for it, if necessary. 
   while (result) 
   { 
      hPipe = CreateFile(lpszPipename, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
      if (hPipe != INVALID_HANDLE_VALUE) 
         break; 
 
      // Exit if an error other than ERROR_PIPE_BUSY occurs. 
      if (GetLastError() != ERROR_PIPE_BUSY) 
      {
         printf("Could not open pipe. GLE=%d\n", GetLastError() ); 
         result = false;
      }
 
      // All pipe instances are busy, so wait for 20 seconds. 
      if ( ! WaitNamedPipe(lpszPipename, 20000)) 
      { 
         printf("Could not open pipe: 20 second wait timed out."); 
         result = false;
      } 
   }
	return(result);
}


bool	CPipeClient::Write(unsigned long cbToWrite, char* lpvMessage, unsigned long& cbWritten)
{
	bool	result = true;

	// The pipe connected; change to message-read mode. 
   dwMode = PIPE_READMODE_MESSAGE; 
   if ( !SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL)) {
      result = false;
   }
	else
	{	// Send a message to the pipe server. 
		if (!WriteFile( hPipe, lpvMessage, cbToWrite, &cbWritten, NULL)) { 
			result = false;
		}
	}
	return(result);
}

bool	CPipeClient::Read(unsigned long  cbSize, char chBuf[BUFSIZE], unsigned long&  cbRead)
{
	bool	result = true;
   do 
   {	// Read from the pipe.
      BOOL fSuccess = ReadFile(hPipe, chBuf, sizeof(char) * cbSize, &cbRead, NULL);    // not overlapped 
      if ( ! fSuccess && GetLastError() != ERROR_MORE_DATA ){
         result = false;
		}
   } while ( ! result);  // repeat loop if ERROR_MORE_DATA

	if(result){
		printf( "\"%s\"\n", chBuf); 
	}else{
		printf("ReadFile from pipe failed. GLE=%d\n", GetLastError() );
	}

	return(result);
}



bool	CPipeClient::Close()
{
	bool	result = (TRUE == CloseHandle(hPipe)); 
	return(result);
}
