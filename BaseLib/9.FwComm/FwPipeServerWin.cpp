/***********************************************************************\
*																								*
*									P I P E   S E R V E R								*
*																								*
\***********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLib/0.Config/IncludesMs.h"





/***********************************************************************\
*																								*
*										Include Files										*
*																								*
\***********************************************************************/
#include	HDR_FW_PIPE_SRV




/***********************************************************************\
*																								*
*										Connections											*
*																								*
\***********************************************************************/

// This function creates a pipe instance and connects to the client. 
// It returns TRUE if the connect operation is pending, and FALSE if 
// the connection has been completed. 
bool CreateAndConnectInstance(char* lpszPipename, HANDLE& hPipe,LPOVERLAPPED lpoOverlap) 
{
	bool fConnected = true;

   hPipe = CreateNamedPipe( 
      lpszPipename,             // pipe name 
      PIPE_ACCESS_DUPLEX |      // read/write access 
      FILE_FLAG_OVERLAPPED,     // overlapped mode 
      PIPE_TYPE_MESSAGE |       // message-type pipe 
      PIPE_READMODE_MESSAGE |   // message read mode 
      PIPE_WAIT,                // blocking mode 
      PIPE_UNLIMITED_INSTANCES, // unlimited instances 
      BUFSIZE*sizeof(char),    // output buffer size 
      BUFSIZE*sizeof(char),    // input buffer size 
      PIPE_TIMEOUT,             // client time-out 
      NULL);                    // default security attributes

   if (hPipe == INVALID_HANDLE_VALUE) {
      printf("CreateNamedPipe failed with %d.\n", GetLastError()); 
      fConnected = false;
   }
	else
	{
		// Start an overlapped connection for this pipe instance. 
		fConnected &= (TRUE == ConnectNamedPipe(hPipe, lpoOverlap)); 
		if (fConnected)  {// Overlapped ConnectNamedPipe should return zero. 
			printf("ConnectNamedPipe failed with %d.\n", GetLastError()); 
		}
		else switch (GetLastError()) 
		{ 
			// The overlapped connection in progress. 
			case ERROR_IO_PENDING: 
				fConnected = TRUE;
				break; 
 
			// Client is already connected, so signal an event. 
			case ERROR_PIPE_CONNECTED: 
				if (SetEvent(lpoOverlap->hEvent))
					fConnected = TRUE;
					break; 
 
			// If an error occurs during the connect operation... 
			default: 
			{
				printf("ConnectNamedPipe failed with %d.\n", GetLastError());
				fConnected = FALSE;
			}
		}
	}
	return(fConnected);
}



// This routine is called when an error occurs or the client closes 
// its handle to the pipe. 
void DisconnectAndClose(SPipeIntrf* lpPipeInst) 
{ 
	// Disconnect the pipe instance. 
   if (! DisconnectNamedPipe(lpPipeInst->hPipeInst) )   {
      printf("DisconnectNamedPipe failed with %d.\n", GetLastError());
   }
 
	// Close the handle to the pipe instance. 
   CloseHandle(lpPipeInst->hPipeInst); 
 
	// Release the storage for the pipe instance. 
   if (lpPipeInst != NULL){
		delete lpPipeInst->ReadBuff;
      GlobalFree(lpPipeInst); 
	}
}





/***********************************************************************\
*																								*
*									Data Transfer											*
*																								*
\***********************************************************************/
// It starts another read operation.
void  ReadCompleteCb(unsigned long, unsigned long, LPOVERLAPPED); 
bool CPipeServer::ReadBuffer(SPipeIntrf* lpPipeInst) 
{
	// The write operation has finished, so read the next request (if there is no error). 
 	bool 	fRead = (TRUE == ReadFileEx(lpPipeInst->hPipeInst, lpPipeInst->ReadBuff,lpPipeInst->ReadSize, (LPOVERLAPPED) lpPipeInst, (LPOVERLAPPED_COMPLETION_ROUTINE) ReadCompleteCb));
   if (! fRead) {	// Disconnect if an error occurred. 
      DisconnectAndClose(lpPipeInst);
	}
	return(fRead);
} 
 

void  WritCompleteCb(unsigned long, unsigned long, LPOVERLAPPED); 
//It gets data and writes it to the pipe. 
bool	 CPipeServer::WritdBuffer(SPipeIntrf* lpPipeInst, char WriteBuffer[BUFSIZE], unsigned long WriteSize) 
{ 
	// The read operation has finished, so write a response (if no error occurred). 
	lpPipeInst->WriteSize = WriteSize;
	bool	fWrite = (TRUE == WriteFileEx(lpPipeInst->hPipeInst, WriteBuffer, WriteSize, (LPOVERLAPPED) lpPipeInst, (LPOVERLAPPED_COMPLETION_ROUTINE) WritCompleteCb));
	// Disconnect if an error occurred. 
	if (! fWrite){ 
		DisconnectAndClose(lpPipeInst); 
	}
	return(fWrite);
}  




/***********************************************************************\
*																								*
*										Callbacks											*
*																								*
\***********************************************************************/

// This routine is called as an I/O completion routine after reading 
// a request from the client. 
void  ReadCompleteCb(unsigned long dwErr, unsigned long cbBytesRead, LPOVERLAPPED lpOverLap) 
{ 
	// lpOverlap points to storage for this instance. 
   SPipeIntrf* lpPipeInst = (SPipeIntrf*) lpOverLap; 
   printf( "[%d] %s\n", lpPipeInst->hPipeInst, lpPipeInst->ReadBuff);

	// The read operation has finished, so write a response (if no error occurred). 
   if ((dwErr == 0) && (cbBytesRead != 0)) {
		lpPipeInst->pServer->MsgReceived(lpPipeInst, lpPipeInst->ReadBuff, lpPipeInst->ReadSize);
	} 
 } 
 
// This routine is called as a completion routine after writing to 
// the pipe, or when a new client has connected to a pipe instance.
void  WritCompleteCb(unsigned long dwErr, unsigned long cbWritten, LPOVERLAPPED lpOverLap) 
{
	// lpOverlap points to storage for this instance. 
	SPipeIntrf* lpPipeInst = (SPipeIntrf*) lpOverLap; 

	// The write operation has finished, so read the next request (if there is no error). 
   if ((dwErr == 0) && (cbWritten == lpPipeInst->WriteSize)) {
		//bool fRead = ReadBuffer(lpPipeInst);
		lpPipeInst->pServer->MsgSent(lpPipeInst);
	}
} 





/***********************************************************************\
*																								*
*										Server Class										*
*																								*
\***********************************************************************/

bool	CPipeServer::Init(char* pName)
{
	bool fPendingIO = FALSE;

	// Create one event object for the connect operation. 
   oConnect.hEvent = CreateEvent( NULL, TRUE, TRUE, NULL);
	if (NULL == oConnect.hEvent)  {
      printf("CreateEvent failed with %d.\n", GetLastError());
   }
	else
	{
		// Call a subroutine to create one instance, and wait for the client to connect.
		my_pName = pName; 
		fPendingIO = CreateAndConnectInstance(pName, hPipe, &oConnect);
	}
	return(fPendingIO);
}

bool	CPipeServer::RunNext()
{
	// Wait for a client to connect, or for a read or write operation to be completed,
	//	which causes a completion routine to be queued for execution. 
	switch (WaitForSingleObjectEx(oConnect.hEvent, INFINITE, TRUE)) 
	{	// The wait conditions are satisfied by a completed connect operation. 
		case 0:
		{
			// If an operation is pending, get the result of the connect operation. 
			if (my_result) 
			{ 
				unsigned long  cbRet; 
				if (!GetOverlappedResult(hPipe, &oConnect, &cbRet, FALSE)) {
					printf("ConnectNamedPipe (%d)\n", GetLastError()); 
					return(FALSE);
				}
			} 
 
			// Allocate storage for this instance.
			SPipeIntrf* lpPipeInst = (SPipeIntrf*) GlobalAlloc(GPTR, sizeof(SPipeIntrf)); 
         if (lpPipeInst == NULL) {
				printf("GlobalAlloc failed (%d)\n", GetLastError()); 
				return(FALSE);
			}
			else
			{
				// Start the read operation for this client. 
				// Note that this same routine is later used as a completion routine after a write operation.
				//lpPipeInst->WriteSize = 0;
				lpPipeInst->hPipeInst = hPipe;
				lpPipeInst->pServer = (CSreverIntrf*)this;
				lpPipeInst->ReadSize = BUFSIZE * sizeof(char);
				lpPipeInst->ReadBuff = new char[lpPipeInst->ReadSize];
				ReadBuffer(lpPipeInst);
 
				// Create new pipe instance for the next client. 
				my_result = CreateAndConnectInstance(my_pName, hPipe, & oConnect); 
			}
		}	break; 
 
		// The wait is satisfied by a completed read or write operation.
		//	This allows the system to execute the completion routine. 
      case WAIT_IO_COMPLETION: 
         break; 
 

      default: {      // An error occurred in the wait function.  
         printf("WaitForSingleObjectEx (%d)\n", GetLastError()); 
         return(FALSE);
      }
   }
	return(TRUE);
}

bool	CPipeServer::MsgSent(SPipeInfo* lpPipeInst)
{
	bool fRead = ReadBuffer((SPipeIntrf*)lpPipeInst);
	return(fRead);
}

bool	CPipeServer::MsgReceived(SPipeInfo* lpPipeInst, char* pBuff, unsigned long size)
{
	unsigned long			WriteSize;
	char			WriteBuffer[BUFSIZE]; 
	strcpy(WriteBuffer, "Default answer from server");
   WriteSize = (strlen(WriteBuffer)+1)*sizeof(char);

	bool fWrite = 	WritdBuffer((SPipeIntrf*)lpPipeInst, WriteBuffer, WriteSize);
	return(fWrite);
}