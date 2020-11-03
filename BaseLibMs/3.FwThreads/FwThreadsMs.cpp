/********************************************************************\
*																							*
*										Thread Handler									*
*																							*
\********************************************************************/
#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





/********************************************************************\
*																							*
*									Include files.										*
*																							*
\********************************************************************/
#include HDR_FW_THREAD
#include	HDR_FW_POINTERS





/********************************************************************\
*																							*
*										Globals											*
*																							*
\********************************************************************/
/*Enumerators creation.*/
ENUM_NAMES_CREATE(THREAD_STATE,THREAD_STATE_NAMES);





/********************************************************************\
*																							*
*											API											*
*																							*
\********************************************************************/
/*C++ THREAD creation template*/
FW_RESULT	ThreadCreate(CMicThread** pointer, void* function, void* parent, int timeout)
{
	RES_DECLR(result);
	if(NULL == (*pointer))
	{
		(*pointer) = new CMicThread(function,(void*)parent);
		if(NULL != (*pointer)){
			RES_CHECK(result,(*pointer)->Activate(timeout));	
		}
		else{
			RES_FAILE(result);
		}
	}
	else{
		RES_FAILE(result);
	}
	RES_RETURN(result);
}

FW_RESULT	ThreadTerminate(CMicThread** pointer, int timeout)
{
	RES_DECLR(result);

	if(NULL != (*pointer))
	{
		RES_CHECK(result,(*pointer)->Terminate(timeout));

		delete	(*pointer);
		(*pointer) = NULL;
	}
	RES_RETURN(result);
}

STRING	ThreadStateName(THREAD_STATE state)
{
	STR_DECLR(state_Name);

	STR_SET(state_Name,ENUM_NAME(THREAD_STATE,state));

	STR_RETURN(state_Name);
}









/********************************************************************\
*																							*
*											Class											*
*																							*
\********************************************************************/

FW_RESULT CMicThread::Init(void)
{
	RES_DECLR(result);

	MUTX_INIT(ThreadLock);
	my_state		= THREAD_STATE_TERMINATE;	//	Currently thread is terminated.

	my_id			= 0;								//	No thread ID.
	my_handle	= NULL;							//	No thread handle.
	Parent		= NULL;							//	Transfer parent pointer to the thread.
	
	ThreadRoutine = NULL;						//	Set the thread rutin.

	RES_RETURN(result);
}
//FW_RESULT CMicThread::Clear(void)
//{
//	RES_DECLR(result);
//
//	if(THREAD_STATE_TERMINATE != State()){
//		RES_CHECK(result,Terminate());
//	}
//	RES_CHECK(result,Init());
//
//	RES_RETURN(result);
//}
//----------------------
//	Default constructor.
CMicThread::CMicThread()
{
	RES_ALERT(Init());
}

CMicThread::CMicThread(void* pFunction,void* newParent)
{
	RES_DECLR(result);
	
	RES_CHECK(result,Init());

	Parent = newParent;								//	Transfer parent pointer to the thread.
	RES_CHECK(result,PTR_NOT_NULL(Parent));

	ThreadRoutine = (LPTHREAD_START_ROUTINE) pFunction;	//	Set the thread rutine.
	RES_CHECK(result,PTR_NOT_NULL(ThreadRoutine));

	RES_ALERT(result);
}


FW_RESULT	CMicThread::Init(void* pFunction,void* newParent)
{
	RES_DECLR(result);

//	RES_CHECK(result,Init());								//	First clear local variables.
	if((Parent == NULL)	&&	(ThreadRoutine == NULL))
	{
		Parent = newParent;												//	Transfer parent pointer to the thread.
		ThreadRoutine = (LPTHREAD_START_ROUTINE) pFunction;	//	Set the thread rutine.
	}
	else{
		RES_FAILE(result);
	}

	RES_RETURN(result);
}

CMicThread::~CMicThread()
{
	RES_DECLR(result);

	if(THREAD_STATE_TERMINATE != State())			//	Check if the thread is not terminated.
	{
		RES_CHECK(result,Terminate(0x00));				//	Terminate the thread befor exit.
	}

	RES_ALERT(result);
}

THREAD_STATE	CMicThread::State(void)
{
	THREAD_STATE	state = THREAD_STATE_UNDEF;
	MUTX_LOCK(ThreadLock);

	state = my_state;

	MUTX_UNLOCK(ThreadLock);						//	Release the port for othr threads.
	return(state);
}

FW_RESULT	CMicThread::State(THREAD_STATE	state)
{
	MUTX_LOCK(ThreadLock);

	my_state = state;

	MUTX_UNLOCK(ThreadLock);						//	Release the port for othr threads.
	return(true);
}
STRING	CMicThread::StateName(void)
{
	STR_DECLR(state_Name);
	MUTX_LOCK(ThreadLock);

	state_Name = ENUM_NAME(THREAD_STATE,my_state);

	MUTX_UNLOCK(ThreadLock);						//	Release the port for othr threads.
	STR_RETURN(state_Name);
}

//-------------------------------------------------------------------
//		This function is used for Command Validation befor Execution.
bool CMicThread::StateCheck(THREAD_STATE state)
{
	bool enable = false;

	switch(State())
	{
	case	THREAD_STATE_ACTIVE:
		if(	(THREAD_STATE_PAUSE		== state)	||
				(THREAD_STATE_TERMINATE == state)	){
			enable = true;
		}
		break;
	case	THREAD_STATE_PAUSE:
		if(	(THREAD_STATE_CONTINUE	== state)	||
				(THREAD_STATE_TERMINATE == state)	){
			enable = true;
		}
		break;
	case	THREAD_STATE_CONTINUE:
		if(	(THREAD_STATE_PAUSE		== state)	||
				(THREAD_STATE_TERMINATE	== state)	){
			enable = true;
		}
		break;
	case	THREAD_STATE_TERMINATE:
		if( THREAD_STATE_ACTIVE			== state){
			enable=true;
		}
		break;
	}

	return(enable);
}


FW_RESULT CMicThread::StateWait(THREAD_STATE state, int timeout)
{
	RES_DECLR(result);
	for(int	ExitCount = 0x00; ExitCount <timeout; ExitCount++)	{
		if(State() != state){				//	Thread did not arrive to state.
			Sleep(THREAD_INTERVAL);
			RES_FAILE(result);
		}
		else{
			RES_SUCCESS(result);
			break;
		}
	}
	RES_RETURN(result);
}







/********************************************************************\
*																							*
*					I n t e r f a c e   c o m m a n d s.						*
*																							*
\********************************************************************/


//---------------------------------------------
//	Activate the Thread.
FW_RESULT CMicThread::Activate(int timeout)
{
	RES_DECLR(result);

	if(my_handle == NULL)
	{
		my_handle = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE) ThreadRoutine, (LPVOID)Parent, CREATE_SUSPENDED , &my_id);
		RES_CHECK(result,PTR_NOT_NULL(my_handle));
//		if(result)	result = (SetThreadPriority(my_handle,THREAD_PRIORITY_BELOW_NORMAL)==TRUE);
		if(result)	result = (SetThreadPriority(my_handle,THREAD_PRIORITY_NORMAL)==TRUE);
//		if(result)	result = (SetThreadPriority(my_handle,THREAD_PRIORITY_HIGHEST)==TRUE);
//		if(result)	result = (SetThreadPriority(my_handle,THREAD_PRIORITY_TIME_CRITICAL)==TRUE);
	}
	RES_CHECK(result, ResumeThread(my_handle) != -1);
	RES_CHECK(result, StateWait(THREAD_STATE_ACTIVE, timeout));

	RES_RETURN(result);
}

//	Raise the thread priority.
FW_RESULT	CMicThread::SetPriorityMedium()
{
	RES_DECLR(result);

	if(my_handle!= NULL)	{
		RES_CHECK(result,SetThreadPriority(my_handle,THREAD_PRIORITY_ABOVE_NORMAL)==TRUE);
	}

	RES_RETURN(result);
}

FW_RESULT	CMicThread::SetPriorityHigh()
{
	RES_DECLR(result);

	if(my_handle!= NULL)	{
		RES_CHECK(result,SetThreadPriority(my_handle,THREAD_PRIORITY_HIGHEST)==TRUE);
	}

	RES_RETURN(result);
}

//	Send a user message to the thread.
FW_RESULT	CMicThread::MessagePost(FW_UINT Msg,WPARAM wParam, LPARAM lParam)
{
	RES_DECLR(result);

	if(my_id != 0x00){
		RES_CHECK(result,FALSE != PostThreadMessage(my_id,WM_USER + Msg, wParam, lParam));		//	Palce message in the thread que and return without waiting for processing.
	}

	RES_RETURN(result);		
}
//	Send a user message to the thread.
FW_RESULT	CMicThread::MessagePost(FW_UINT Msg)
{
	RES_DECLR(result);

	RES_CHECK(result, MessagePost(Msg, Msg, 0x00));		//	Palce message in the thread que and return without waiting for processing.

	RES_RETURN(result);		
}

//------------------------
//	Pause the port Thread.
FW_RESULT CMicThread::Pause()
{
	RES_DECLR(result);

	if(SuspendThread(my_handle) == -1){
		RES_FAILE(result);						//	Suspend thread and check result.
	}
	else{
		RES_CHECK(result,State(THREAD_STATE_PAUSE));					//	Set new satatues.
	}

	RES_RETURN(true);
}
//-------------------------------------
//	Continue the port thread execution.
FW_RESULT CMicThread::Continue()
{
	RES_DECLR(result);

 	RES_CHECK(result,ResumeThread(my_handle) != -1);	//	Resume thread execution and check result.
	RES_CHECK(result,State(THREAD_STATE_CONTINUE));				//	Set new statues.

	RES_RETURN(result);
}


//----------------------------
//	Terminate the port thread.
FW_RESULT CMicThread::Kill()
{
	RES_DECLR(result);
	DWORD ExitCode = 0x00;										// address to receive the thread termination status

//	if(FALSE == GetExitCodeThread(my_handle,&ExitCode))					//	Get thread termination statues.
//	{
		TerminateThread(my_handle, ExitCode);	//	Terminate the thread and check result.
		CloseHandle(my_handle);

//	}
//	RES_CHECK(result,State(THREAD_STATE_TERMINATE));		//	Set new statues.
	my_handle = NULL;
	my_state = THREAD_STATE_TERMINATE;
	
	RES_RETURN(true);
}

//----------------------------
//	Terminate the port thread.
FW_RESULT CMicThread::Terminate(int timeout)
{
 	RES_DECLR(result);
	DWORD ExitCode = 0x00;										// address to receive the thread termination status

	RES_CHECK(result, FALSE != MessagePost(THREAD_STATE_TERMINATE));	//	Send termination message.
	RES_CHECK(result, StateWait(THREAD_STATE_TERMINATE, timeout));

	if(FALSE == GetExitCodeThread(my_handle,&ExitCode))					//	Get thread termination statues.
	{
		RES_CHECK(result, Kill());
//		RES_CHECK(result, FALSE != TerminateThread(my_handle,ExitCode));	//	Terminate the thread and check result.
//		RES_CHECK(result, FALSE != CloseHandle(my_handle));
		RES_CHECK(result,State(THREAD_STATE_TERMINATE));		//	Set new statues.
	}
	my_handle = NULL;

	RES_RETURN(true);
}


