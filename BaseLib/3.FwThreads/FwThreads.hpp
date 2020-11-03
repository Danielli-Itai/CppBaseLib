#ifndef FW_THREADS_HPP
#define	FW_THREADS_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"
	/**************************************************************************\
	*																									*
	*										Inbclude Files											*
	*																									*
	\**************************************************************************/
	#include <thread>         // std::thread
	#include	HDR_FW_SINC
	#include	HDR_FW_ENUMS



	
	/********************************************************************\
	*																							*
	*										Definitions										*
	*																							*
	\********************************************************************/
//	#define		THREAD_HNDLE				std::thread
//
//	#define		THREAD_DECLR(NAME)		std::thread*	p##NAME
//
//	#define		THREAD_DESTROY(NAME)		\
//			p##NAME->join();					\
//			PTR_DESTROY(p##NAME);			\
//
//	#define		THREAD_INTERVAL			10
//
	#define	THREAD_STATE_FIELDS			\
		THREAD_STATE_TERMINATE = 0xFFF	\
		,THREAD_STATE_ACTIVE					\
		,THREAD_STATE_PAUSE					\
		,THREAD_STATE_CONTINUE				\
	/*THREAD_STATE_FIELDS*/
	#define	THREAD_STATE_NAMES			\
		"THREAD_STATE_TERMINATE"			\
		,"THREAD_STATE_ACTIVE"				\
		,"THREAD_STATE_PAUSE"				\
		,"THREAD_STATE_CONTINUE"			\
	/*THREAD_STATE_NAMES*/
	ENUM_DEFINE(THREAD_STATE,THREAD_STATE_FIELDS);
//
//
//
//		#define	THREAD_EVENT_FIELDS		\
//			THREAD_EVENT_TASK_NEW			\
//			,THREAD_EVENT_SESS_COMPLETED	\
//			/*COMP_TYPE_FIELDS*/
//		#define	COMP_EVENT_NAMES			\
//			"New Task"							\
//			,"Session compleated"			\
//			/*COMP_TYPE_NAMES*/
//		ENUM_DEFINE(THREAD_EVENT, THREAD_EVENT_FIELDS);
//
//
//
//
//
//
//
//
//	/********************************************************************\
//	*																							*
//	*										Class												*
//	*																							*
//	\********************************************************************/
//	class CMicThread
//	{
//		private:		MUTEX_DECLR(ThreadLock);
//
//		private:		FW_RESULT	Init(void);
//		public:		FW_RESULT	Init(void* pFunction, void* newParent);
//	//	private:		FW_RESULT	Clear(void);
//		public:		CMicThread();
//		public:		CMicThread(void* pFunction, void* newParent);
//		public:		virtual ~CMicThread();
//
//		//	VPort worker thread.
//		private:		void*	Parent;
//		private:		THREAD_HNDLE	ThreadRoutine;
//		private:		HANDLE			my_handle;
//		public:		HANDLE			Handle()			{	return(my_handle);	}
//		private:		DWORD				my_id;
//		public:		DWORD				ID()				{	return(my_id);			}
//
//		//	The port statues is a multi threading resource.
//		private:		THREAD_STATE	my_state;
//		public:		THREAD_STATE	State(void);
//		public:		FW_RESULT			State(THREAD_STATE state);
//		public:		STRING			StateName(void);
//		public:		bool				StateCheck(THREAD_STATE state);
//		private:		FW_RESULT			StateWait(THREAD_STATE state, int timeout);
//
//
//		public:		FW_RESULT			Activate(int timeout);
//		protected:	FW_RESULT			Pause();
//		protected:	FW_RESULT			Continue();
//		public:		FW_RESULT			Terminate(int timeout);
//		public:		FW_RESULT			Kill();
//		public:		FW_RESULT			SetPriorityMedium();
//		public:		FW_RESULT			SetPriorityHigh();
//		public:		FW_RESULT			PostMessage(FW_UINT Msg, FW_UINT  wParam, FW_UINT  lParam);
//		public:		FW_RESULT			PostMessage(FW_UINT Msg);
//	};
//
//
//
//
//
//
//
//
//	/********************************************************************\
//	*																							*
//	*											API											*
//	*																							*
//	\********************************************************************/
//	#define	THREAD_START_TIMEOUT			100
//
//	/*C++ THREAD creation template*/
//	STRING	ThreadStateName(THREAD_STATE state);
//	FW_RESULT	ThreadCreate(CMicThread** pointer, void* function, void* parent, int timeout);
//	FW_RESULT	ThreadTerminate(CMicThread** pointer, int timeout);
//	#define	THREAD_CREATE(P_HNDLR, FUNC, PRNT, TIMEOUT)		ThreadCreate(&P_HNDLR, (void*)FUNC, PRNT, TIMEOUT)
//	#define	THREAD_DESTROY(P_HNDLR, TIMEOUT)		ThreadTerminate(&P_HNDLR, TIMEOUT)
//
#endif // !FW_THREADS
