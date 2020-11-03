#ifndef FW_SINC_MS_H
#define	FW_SINC_MS_H
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





	/***********************************************************************\
	*																								*
	*											Include Files									*
	*																								*
	\***********************************************************************/
	//#include	HDR_STDAFX





	/***********************************************************************\
	*																								*
	*								S y n c h r o n i z a t i o n							*
	*																								*
	\***********************************************************************/

	#define	MUTX_DECLR(OBJ)		\
		CMutex 	OBJ					\
		/*SYNC CSemaphore	OBJ*/

	#define	MUTX_INIT(OBJ)			\
		OBJ.Unlock()					\
		/*MUTX_INIT*/

	#define	MUTX_LOCK(OBJ)					\
		CSingleLock Sl##OBJ(&##OBJ##);	\
		_ASSERT(Sl##OBJ.Lock())				\
		/*MUTX_LOCK*/

	#define	MUTX_LOCK_TIMEOUT(OBJ,TIMEOUT)\
		CSingleLock Sl##OBJ(&##OBJ##);					\
		Sl##OBJ.Lock(TIMEOUT);								\
		/*MUTX_LOCK*/
	
	#define	MUTX_UNLOCK(OBJ)		\
		Sl##OBJ.Unlock(); 			\
		bool	Sll##OBJ = false;		\
		/*MUTX_UNLOCK*/

	#define	MUTX_LOCKED(OBJ)		\
		(Sl##OBJ.IsLocked())			\
		/*MUTX_UNLOCK*/

	#define	MUTX_UNLOCKED(OBJ)		\
		(TRUE != Sl##OBJ.IsLocked())	\
		/*MUTX_UNLOCK*/
		




	//#define	EVENT_DECLR(EVNT)		\
	//	HANDLE	EVNT;					\
	//	DWORD		EVNT##Res;			\
	//	/*EVENT_DECLR*/
	#define	EVENT_DECLR(EVNT)		\
		OVERLAPPED	EVNT;				\
		BOOL			EVNT##Res;		\
		/*EVENT_DECLR*/
		

	#define	EVENT_INIT(EVNT)					\
		memset(&EVNT, 0x00,sizeof(EVNT));	\
		EVNT.hEvent = NULL;				\
		/*EVENT_INIT*/

	#define	EVENT_CREATE(EVNT)										\
		EVNT.hEvent = CreateEvent( 0, FALSE, FALSE, 0);	\
		RES_ALERT(NULL != EVNT.hEvent);						\
		/*EVENT_CREATE*/

	#define	EVENT_WAIT(EVNT,TIMEOUT)													\
		EVNT##Res = WaitForSingleObject(EVNT.hEvent, TIMEOUT);					\
		RES_ALERT((WAIT_FAILED!=EVNT##Res) || (WAIT_ABANDONED!=EVNT##Res));	\
		/*EVENT_SET*/
	#define	EVENT_TOUT_CHK(EVNT)	\
		(WAIT_TIMEOUT==EVNT##Res)	\
			/*EVENT_ERROR_CHK*/

	#define	EVENT_SET(EVNT)					\
		EVNT##Res = SetEvent(EVNT.hEvent)	\
		/*EVENT_SET*/

	#define	EVENT_CLR(EVNT)					\
		EVNT##Res = ResetEvent(EVNT.hEvent)	\
		/*EVENT_SET*/

	#define	EVENT_DESTROY(EVNT)				\
		(S_OK == CloseHandle(EVNT.hEvent))	\
		/*EVENT_DESTROY*/



#endif // !FW_SINC_MS_H